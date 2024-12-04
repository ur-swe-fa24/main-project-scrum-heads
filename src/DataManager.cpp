#include "DataManager.h"
#include <algorithm>
#include <wx/string.h>
#include <thread>
#include <chrono>
#include <mutex>

std::atomic<bool> stop_thread = false;
std::mutex data_manager_mutex;

DataManager::DataManager() 
{
    // Initialize the MongoDB client and update the list of IDs
    UpdateIds();
    // Start the thread for updating robot task progress
    start_update_thread();
}

// Destructor: Handles cleanup, if necessary.
DataManager::~DataManager() {
    stop_update_thread();
}

// Method to start the update thread
void DataManager::start_update_thread() {
    update_thread_ = std::thread([this]() { update_task_progress(); });
}

// Method to stop the update thread
void DataManager::stop_update_thread() {
    stop_thread = true;
    if (update_thread_.joinable()) {
        update_thread_.join();
    }
}

// Method to update the task progress in the database
void DataManager::update_task_progress() {
    while (!stop_thread) {
        {
            std::lock_guard<std::mutex> lock(data_manager_mutex);
            auto& robot_list = robot_manager_.get_list();

            for (auto& robot : robot_list) {
                if (robot.get_task_status() == "Ongoing") {
                    // Update the MongoDB database with the latest task progress, battery, and water levels
                    mongo_database.update_task_status({robot});
                } else if (robot.get_task_status() == "Complete") {
                    // Update the robot status to "Available" when the task is complete
                    robot.update_task_status("Available");
                    mongo_database.update_task_status({robot});
                } else if (robot.get_task_status() == "Cancelled" && robot.get_error_status().empty()) {
                    // If a task is cancelled with no error, make the robot available
                    robot.update_task_status("Available");
                    mongo_database.update_task_status({robot});
                }
            }
        }

        // Sleep for 1 second before the next iteration
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

// Getter method for vector of RobotData (just ID, size, and function)
std::vector<RobotData>& DataManager::GetRobots() {
    return robots;
}

// Getter method for vector of TaskData (just ID, size, and function)
std::vector<TaskData>& DataManager::GetTasks() {
    return tasks;
}

// Method to add a new robot to the system, taking the abbreviated RobotData of a robot as input
void DataManager::AddRobot(RobotData& robot) {
    int new_id = GetNextAvailableRobotId();

    // Convert wxString to std::string for robotSize and robotFunction
    std::string size_str = std::string(robot.robotSize.mb_str());
    std::string function_str = std::string(robot.robotFunction.mb_str());

    // Create a new robot instance
    robots::Robots new_robot(new_id, size_str, 100, 100, "None", "Available", Room(), function_str, 0);
    
    // Add the new robot to the robot manager
    robot_manager_.add_robot(new_robot);

    // Write the new robot to the MongoDB database
    mongo_database.write_robot(new_robot);

    // Update RobotData of the added robot with its assigned ID
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
    id = 1;

    // Find the next available ID that is not already used
    while (std::find(ids.begin(), ids.end(), id) != ids.end()) {
        ++id;
    }

    return id;
}

// Gets all robot info for a specified ID
robots::Robots DataManager::GetAllRobotInfo(int robotId)
{
    return mongo_database.read_robot(robotId);
}

// Deletes a robot given ID
void DataManager::DeleteRobot(int robotId)
{
    // Remove the robot from the database
    mongo_database.delete_robot(robotId);
    
    // Remove the robot from the RobotManager
    robot_manager_.remove_robot_by_id(robotId);

    // Remove the robot from the vector of RobotData
    std::string robotIdStr = std::to_string(robotId);
    for (auto iterator = robots.begin(); iterator != robots.end(); ++iterator) {
        if (iterator->robotID == robotIdStr) {
            robots.erase(iterator);
            break;
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

    int robot_id = std::stoi(robot_str);
    int room_num = std::stoi(room_str);
    
    // Write task to the database
    mongo_database.write_task(robot_id, room_num);
}

// Get available robots for task allocation
std::vector<robots::Robots> DataManager::GetAvailableRobots()
{
    std::vector <robots::Robots> robotVector = mongo_database.read_all_robots();
    std::vector <robots::Robots> availableRobotVector;

    for (robots::Robots robot : robotVector) {
        if (robot.get_task_status() == "Available")
        {
            availableRobotVector.push_back(robot);
        }
    }

    return availableRobotVector;
}
