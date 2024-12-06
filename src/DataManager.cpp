#include "DataManager.h"
#include <algorithm>  // Include for std::find
#include <wx/string.h>
#include <fstream>
#include <sstream>
#include <chrono>

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
        while (keep_updating_) {
            {
                std::lock_guard<std::mutex> lock(data_mutex_);

                // Get the current list of robots from the robot manager
                auto robot_list = robot_manager_.get_list();

                // Update the MongoDB database with the latest robot statuses
                mongo_database.update_task_status(robot_list);
            }

            // Sleep for 0.5 seconds before the next update
            std::this_thread::sleep_for(std::chrono::milliseconds(500));

        }
    });
}

void DataManager::stopUpdateThread() {
    keep_updating_ = false;
    if (update_thread_.joinable()) {
        update_thread_.join();
    }
}

// Method to receive and process robots data
// void DataManager::SendRobotsData(const std::vector<RobotData>& robots) {
//     // Process each robot and prepare for database insertion or other actions
//     for (const auto& robot : robots) {
//         std::cout << "Size: " + robot.robotSize + ", Function: " + robot.robotFunction << std::endl;
//     }

//     // You can then call the database model to save or update robot data here
// }

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

    //write vector of rooms to database and simulation
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
    int new_id = GetNextAvailableRobotId();  // Get a new unique ID, assigned by data manager to avoid user error

    // robot.robotID = new_id;
    // std::cout << robot.robotID << std::endl;

    // Convert wxString to std::string for robotSize and robotFunction
    std::string size_str = std::string(robot.robotSize.mb_str());
    std::string function_str = std::string(robot.robotFunction.mb_str());

    //temporary room placeholder
    Room room(0, "", "", "");

    // Create a new robot instance with the new ID and the provided robot data
    robots::Robots new_robot(new_id, size_str, 100, 100, "None", "Available", room, function_str, 0);
    
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
    //returns updated robot
    return clicked_robot;
}

//gets all robot info (i.e., all of the info specified in robot class) for a specified ID
//used to display necessary information to the user in GUI
std::vector<robots::Robots> DataManager::GetTasksTable()
{
    //temporary placeholder that just creates a robot pre-database integration
    // robots::Robots clicked_robot(robotId, "Large", 100, 50, "", "Vacuum", 3, "Scrub", 10, 15);
    std::vector<robots::Robots> tasks = mongo_database.read_all_tasks();
    return tasks;
}

void DataManager::DeleteRobot(int robotId)
{
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
void DataManager::AddTask(TaskData& task) {
    // Convert wxString to std::string for task room selection and task robot selection
    std::string room_str = std::string(task.taskRoom.mb_str());
    std::string robot_str = task.taskRobot.robotID;

    tasks.push_back(task); //adds task to vector of TaskData

    //getallrobotinfo for input robot ID (retrived from struct)
    //then manually update stuff

    int robot_id = std::stoi(robot_str);
    int room_num = std::stoi(room_str);
    
    // Write task to the database
    mongo_database.write_task(robot_id, room_num);
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
