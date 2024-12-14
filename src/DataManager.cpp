#include "DataManager.h"
#include <algorithm>  // Include for std::find
#include <wx/string.h>
#include <fstream>
#include <sstream>
#include <chrono>
#include "spdlog/spdlog.h"
#include "robot_do_task.hpp"

using namespace robot_tasks;

#include <iostream>



DataManager::DataManager() 
{
    //wipe database clean
    mongo_database.delete_all_robots();
    mongo_database.delete_all_tasks();
    mongo_database.delete_rooms();
    mongo_database.delete_error_log();
    
    // Initialize the MongoDB client and update the list of IDs
    UpdateIds();

    // Add rooms from the text file
    AddRooms();

    startUpdateThread();
}

// Destructor: Handles cleanup, if necessary.
DataManager::~DataManager() {
    stopUpdateThread();
}

void DataManager::startUpdateThread() {
    update_thread_ = std::thread([this]() {
        // Start the robot task execution loop
        robot_tasks::start_execute_thread(robot_manager_.get_list());

        while (keep_updating_) {
            {
                std::lock_guard<std::mutex> lock(data_mutex_); // Ensure thread-safe access
                auto robot_list = robot_manager_.get_list();
                // spdlog::info("Fetched robot list from RobotManager. Robot count: {}", robot_list.size());

                // Simulate MongoDB update
                mongo_database.update_task_status(robot_list);
                // spdlog::info("Updated task status in MongoDB successfully.");
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(3000)); // Sleep for 0.5 seconds
        }

        // Stop the robot task execution loop when the update thread stops
        robot_tasks::stop_execute_thread();
    });
}



void DataManager::stopUpdateThread() {
    keep_updating_ = false; // Stop the update thread
    if (update_thread_.joinable()) {
        update_thread_.join();
    }
    robot_tasks::stop_execute_thread(); // Stop the robot task execution loop
}


// Method to receive and process robots data
// void DataManager::SendRobotsData(const std::vector<RobotData>& robots) {
//     // Process each robot and prepare for database insertion or other actions
//     for (const auto& robot : robots) {
//         std::cout << "Size: " + robot.robotSize + ", Function: " + robot.robotFunction << std::endl;
//     }

//     // You can then call the database model to save or update robot data here
// }

void DataManager::UpdateTaskData()
{
    tasks.clear(); //empties TaskData vector

    std::vector<robots::Robots> taskVector = mongo_database.read_all_ongoing_tasks(); //reads ongoing tasks from database

    //for each ongoing task
    for (robots::Robots task : taskVector) 
    {
        //get all the necessary info for TaskData
        wxString taskRoom = std::to_string(task.get_task_room().getRoomNumber());
        std::string robotID = std::to_string(task.get_id());
        wxString robotSize = task.get_size();
        wxString robotFunction = task.get_function_type();
        RobotData robot = {robotID, robotSize, robotFunction};
        TaskData updatedTask = {taskRoom, robot};
        //add the new TaskData
        tasks.push_back(updatedTask);
    }
}

void DataManager::AddRooms()
{
    // Open the file
    std::ifstream file("../include/rooms.txt");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file!" << std::endl;
    }

    // Read file line by line
    std::string line;
    while (std::getline(file, line)) {

        //ignore empty lines or lines starting with comments
        if (line.empty() || line[0] == '#') {
            continue;
        }

        //used for parsing string
        std::stringstream ss(line);

        //room id, size, type, and availability
        int roomID;
        std::string roomSize, floorType, roomAvailability;

        // Read the room ID
        std::string temp;
        std::getline(ss, temp, ','); // Extract up to the first comma
        roomID = std::stoi(temp);        // Convert to an integer

        // Read the strings
        std::getline(ss, roomSize, ',');  // Extract the second field
        std::getline(ss, floorType, ',');  // Extract the third field
        std::getline(ss, roomAvailability, '.'); // Extract the fourth field

        // std::cout << roomID << std::endl;
        // std::cout << roomSize << std::endl;
        // std::cout << floorType << std::endl;
        // std::cout << roomAvailability << std::endl;

        //make room with 4 parameters here, append to vector of rooms
        Room room (roomID, roomSize, floorType, roomAvailability);
        roomVector.push_back(room);
    }

    // Close the file
    file.close();

    //write vector of rooms to database 
    mongo_database.write_rooms(roomVector);
}


// Getter method for vector of RobotData (just ID, size, and function)
std::vector<RobotData>& DataManager::GetRobots() {
    return robots;
}

// Getter method for vector of RobotData (just ID, size, and function)
std::vector<TaskData>& DataManager::GetTasks() {
    return tasks;
}

// Method to add a new robot to the system, taking the abbreviated RobotData of a robot as input
void DataManager::AddRobot(RobotData& robot) {
    std::lock_guard<std::mutex> lock(data_mutex_);
    int new_id = GetNextAvailableRobotId();  // Get a new unique ID, assigned by data manager to avoid user error

    // robot.robotID = new_id;
    // std::cout << robot.robotID << std::endl;

    // Convert wxString to std::string for robotSize and robotFunction
    std::string size_str = std::string(robot.robotSize.mb_str());
    std::string function_str = std::string(robot.robotFunction.mb_str());

    //temporary room placeholder
    Room room(0, "", "", "");

    //default robot as small, then change to large or medium if necessary
    robots::Robots new_robot(new_id, size_str, 100, 100, "", "Available", room, function_str, 0);

    //create robot instance with varying water and battery levels dependent on its size
    if (size_str == "Large")
    {
        new_robot = robots::Robots(new_id, size_str, 140, 140, "", "Available", room, function_str, 0);
    }
    else if (size_str == "Medium")
    {
        new_robot = robots::Robots(new_id, size_str, 120, 120, "", "Available", room, function_str, 0);
    }
    // else
    // {
    //     new_robot = robots::Robots(new_id, size_str, 100, 100, "None", "Available", room, function_str, 0);
    // }
    // // Create a new robot instance with the new ID and the provided robot data
    // robots::Robots new_robot(new_id, size_str, 100, 100, "None", "Available", room, function_str, 0);
    
    // Write the new robot to the MongoDB database
    mongo_database.write_robot(new_robot);

    //update the RobotData of the added robot with its assigned ID
    robot.robotID = std::to_string(new_id);
    // Add the new robot data to the local list of robots
    robots.push_back(robot);

    // Append the new ID to the list of IDs
    ids.push_back(new_id);

    // Add to RobotManager
    robot_manager_.add_robot(new_robot);
}

// Method to update the list of robot IDs from the MongoDB database
void DataManager::UpdateIds() {
    ids = mongo_database.get_all_ids();
}

// Method to find the next available robot ID
int DataManager::GetNextAvailableRobotId() {
    id = 1;  // Start from ID 1

    // Find the next available ID that is not already used
    while (std::find(ids.begin(), ids.end(), id) != ids.end()) {
        ++id;  // Increment the ID until an available one is found
    }

    return id;
}

// Returns current ID as string for easy UI use
std::string DataManager::GetIDString() {
    std::string IDString = std::to_string(id);
    return IDString;
}

//gets all robot info (i.e., all of the info specified in robot class) for a specified ID
//used to display necessary information to the user in GUI
robots::Robots DataManager::GetAllRobotInfo(int robotId)
{
    //gets the complete info for clicked robot
    robots::Robots clicked_robot = mongo_database.read_robot(robotId);
    //gets the updated task status for that robot
    robots::Robots taskUpdatedRobot = mongo_database.read_ongoing_task(robotId);
    //determines the room from the updated task status
    Room room = taskUpdatedRobot.get_task_room();
    //sets the room for the clicked robot
    clicked_robot.update_task_room(room);

    int taskPercent = taskUpdatedRobot.get_task_percent();
    clicked_robot.update_task_percent(taskPercent);
    //returns updated robot
    return taskUpdatedRobot;
}

//gets all robot info (i.e., all of the info specified in robot class) for a specified ID
//used to display necessary information to the user in GUI
std::vector<robots::Robots> DataManager::GetTasksTable()
{
    //temporary placeholder that just creates a robot pre-database integration
    // robots::Robots clicked_robot(robotId, "Large", 100, 50, "", "Vacuum", 3, "Scrub", 10, 15);
    //use read_all_tasks instead if you want non-ongoing (complete and cancelled) tasks
    std::vector<robots::Robots> tasks = mongo_database.read_all_ongoing_tasks();
    
    return tasks;
}

void DataManager::DeleteRobot(int robotId)
{
    std::lock_guard<std::mutex> lock(data_mutex_); // Thread-safe access
    //first remove the robot from the database
    mongo_database.delete_robot(robotId);
    
    //then remove the robot from the vector of RobotData
    //convert id to string (same type as in RobotData struct)
    std::string robotIdStr = std::to_string(robotId);
    //auto allows compiler to take care of type
    for (auto iterator = robots.begin(); iterator != robots.end(); ++iterator) {
        if (iterator->robotID == robotIdStr) {
            robots.erase(iterator);  // Remove the robot from the vector
            break;  // Exit the loop after removal
        }
    }

    // Remove the robot from the RobotManager
    robot_manager_.remove_robot_by_id(robotId);
}


// Method to add a new robot to the system, taking the abbreviated RobotData of a robot as input
// Add task
void DataManager::AddTask(TaskData& task) {
    // Convert wxString attributes to std::string
    std::string room_str = std::string(task.taskRoom.mb_str());
    std::string robot_str = task.taskRobot.robotID;
    tasks.push_back(task);         // Add to the task vector

    // Convert the strings to integers
    int robot_id = std::stoi(robot_str);
    int room_num = std::stoi(room_str);
    // std::cout << "room number: " << room_num << std::endl;

    // Write the task to the database (MongoDB)
    mongo_database.write_task(robot_id, room_num);

    // Find the robot by ID
    robots::Robots& robot = robot_manager_.find_robot_by_id(robot_id);
    // Update the task status to "Ongoing"
    robot.update_task_status("Ongoing");
    // std::cout << "robot number: " << robot.get_id() << std::endl;
    // std::cout << "robot status: " << robot.get_task_status() << std::endl;
    for (auto& room : roomVector) { // Use non-const reference to avoid const issues
        if (room.getRoomNumber() == room_num) {
            // Assign the room to the robot
            robot.update_task_room(room);
            // std::cout << "Assigned room number: " << room.getRoomNumber() << std::endl;
            return; // Exit the loop after assigning the room
        }
    }
}


//gets all robots from database, then filters for available robots
std::vector<robots::Robots> DataManager::GetAvailableRobots()
{
    //holds all robots
    std::vector <robots::Robots> robotVector = mongo_database.read_all_robots();

    //holds available robots
    std::vector <robots::Robots> availableRobotVector;

    //iterate through robot vector to find available robots
    for (robots::Robots robot : robotVector) {
        // std::cout << robot.get_id() << std::endl;
        // std::cout << robot.get_task_status() << std::endl;
        if (robot.get_task_status() == "Available")
        {
            // std::cout << "added" << std::endl;
            availableRobotVector.push_back(robot);
        }
    }

    return availableRobotVector;
}

//gets all rooms from database, then filters for available rooms
std::vector<Room> DataManager::GetRooms()
{
    //gets all rooms from the database
    std::vector<Room> databaseRoomVector = mongo_database.read_all_rooms();

    //returns all rooms
    return databaseRoomVector;
    // return roomVector; //temporailty just returning the local room vector
}

//gets all rooms from database, then filters for available rooms
std::vector<Room> DataManager::GetAvailableRooms()
{
    //holds all robots
    std::vector<Room> databaseRoomVector = mongo_database.read_all_rooms();

    //holds available robots
    std::vector<Room> availableRoomVector;

    //iterate through robot vector to find available robots
    for (Room room : databaseRoomVector) {
        if (room.getAvailability() == "Available")
        {
            availableRoomVector.push_back(room);
        }
    }

    return availableRoomVector;
}

robots::RobotManager& DataManager::GetRobotManager() {
    return robot_manager_;
}


// Method to delete all robots from MongoDB and local vector
void DataManager::DeleteAllRobots() {
    stopUpdateThread(); // Stop the update thread before modifying the list

    std::lock_guard<std::mutex> lock(data_mutex_); // Thread-safe access
    // Delete all robots from the MongoDB database
    mongo_database.delete_all_robots();

    // Clear the local list of RobotData
    robots.clear();
}

//gets error log from database
std::vector<std::string> DataManager::getErrorLog(int robotID)
{
    std::vector<std::string> errorLog = mongo_database.get_error_log(robotID);
    return errorLog;
}

//fixes robot (FE)
void DataManager::FixRobot(int robotID)
{
    robots::Robots& robot = robot_manager_.find_robot_by_id(robotID);
    fix(robot);
}

//changes room availability (BM)
void DataManager::ChangeRoomAvailability(int roomID, bool isAvailable)
{
    std::string availabilityString;
    //change to opposite
    if (isAvailable)
    {
        availabilityString = "Unavailable";
    }
    else
    {
        availabilityString = "Available";
    }
    //update in database
    mongo_database.update_room_availability(roomID, availabilityString);
}