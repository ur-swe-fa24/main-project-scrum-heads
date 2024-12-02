#include "DataManager.h"
#include <algorithm>  // Include for std::find
#include <wx/string.h>
#include <chrono>  // For std::chrono_literals

DataManager::DataManager() {
    // Initialize the MongoDB client and update the list of IDs
    UpdateIds();
    StartTaskUpdateThread();  // Start the thread to update task progress
}

DataManager::~DataManager() {
    StopTaskUpdateThread();  // Ensure the thread is stopped when the DataManager is destroyed
}

// Thread to keep checking and updating robot task progress every second
void DataManager::StartTaskUpdateThread() {
    running_ = true;
    task_update_thread_ = std::thread(&DataManager::TaskUpdateLoop, this);
}

// Method to stop the task update thread safely
void DataManager::StopTaskUpdateThread() {
    running_ = false;
    if (task_update_thread_.joinable()) {
        task_update_thread_.join();
    }
}

// Main loop for the task update thread
void DataManager::TaskUpdateLoop() {
    while (running_) {
        // Get all ongoing tasks from the database
        std::vector<robots::Robots> ongoing_tasks = mongo_database.read__all_ongoing_tasks();

        // Update tasks in the database
        for (auto& robot : ongoing_tasks) {
            // Simulate task progress update here
            int current_progress = robot.get_task_percent();
            if (current_progress < 100) {
                current_progress += 10;  // Simulate 10% progress
                robot.update_task_status("Ongoing");
                robot.set_task_percent(current_progress);
                if (current_progress >= 100) {
                    robot.update_task_status("Complete");
                }
            }

            // Update the task and robot in the database
            mongo_database.update_task_status({robot});
        }

        // Wait for 1 second before the next update
        std::this_thread::sleep_for(std::chrono::seconds(1));
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

    // Create a new robot instance with the new ID and the provided robot data
    robots::Robots new_robot(new_id, size_str, 100, 100, "None", "Available", 0, function_str, 0);
    
    // Write the new robot to the MongoDB database
    mongo_database.write_robot(new_robot);

    //update the RobotData of the added robot with its assigned ID
    robot.robotID = std::to_string(new_id);
    // Add the new robot data to the local list of robots
    robots.push_back(robot);

    // Append the new ID to the list of IDs
    ids.push_back(new_id);
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
    //temporary placeholder that just creates a robot pre-database integration
    // robots::Robots clicked_robot(robotId, "Large", 100, 50, "", "Vacuum", 3, "Scrub", 10, 15);
    robots::Robots clicked_robot = mongo_database.read_robot(robotId);
    return clicked_robot;
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
}

// Method to add a new robot to the system, taking the abbreviated RobotData of a robot as input
void DataManager::AddTask(TaskData& task) {
    // Convert wxString to std::string for task room selection and task robot selection
    std::string room_str = std::string(task.taskRoom.mb_str());
    std::string robot_str = task.taskRobot.robotID;

    tasks.push_back(task); //adds task to vector of TaskData

    //getallrobotinfo for input robot ID (retrived from struct)
    //then manually update stuff
    
    // // Write the new robot to the MongoDB database (not literally a new robot, but database treats it as one)
    // mongo_database.write_task(task_assigned_robot);
}

//gets all robots from database, then filters for available robots
//this part should be fully functional, but right now read_all_robots doesn't include task status string
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