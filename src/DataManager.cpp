#include "DataManager.h"
#include <algorithm>
#include <wx/string.h>
#include <chrono>

DataManager::DataManager() {
    // Initialize the MongoDB client and update the list of IDs
    UpdateIds();
    startUpdateThread();
}

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

            // Sleep for 0.5 second before the next update
            std::this_thread::sleep_for(std::chrono::seconds(0.5));
        }
    });
}

void DataManager::stopUpdateThread() {
    keep_updating_ = false;
    if (update_thread_.joinable()) {
        update_thread_.join();
    }
}

// Getter method for vector of RobotData (just ID, size, and function)
std::vector<RobotData>& DataManager::GetRobots() {
    return robots;
}

// Getter method for vector of TaskData
std::vector<TaskData>& DataManager::GetTasks() {
    return tasks;
}

// Method to add a new robot to the system, taking the abbreviated RobotData of a robot as input
void DataManager::AddRobot(RobotData& robot) {
    int new_id = GetNextAvailableRobotId();  // Get a new unique ID

    // Convert wxString to std::string for robotSize and robotFunction
    std::string size_str = std::string(robot.robotSize.mb_str());
    std::string function_str = std::string(robot.robotFunction.mb_str());

    // Create a new robot instance
    robots::Robots new_robot(new_id, size_str, 100, 100, "None", "Available", 0, function_str, 0);
    
    // Write the new robot to the MongoDB database
    mongo_database.write_robot(new_robot);

    // Update the RobotData of the added robot with its assigned ID
    robot.robotID = std::to_string(new_id);
    robots.push_back(robot);
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
        ++id;
    }

    return id;
}

// Returns current ID as string for easy UI use
std::string DataManager::GetIDString() {
    return std::to_string(id);
}

// Gets all robot info for a specified ID
robots::Robots DataManager::GetAllRobotInfo(int robotId) {
    robots::Robots clicked_robot = mongo_database.read_robot(robotId);
    return clicked_robot;
}

void DataManager::DeleteRobot(int robotId) {
    // Remove the robot from the database
    mongo_database.delete_robot(robotId);
    
    // Remove the robot from the local vector of RobotData
    std::string robotIdStr = std::to_string(robotId);
    auto iterator = std::remove_if(robots.begin(), robots.end(),
                                   [robotIdStr](const RobotData& robot) {
                                       return robot.robotID == robotIdStr;
                                   });
    robots.erase(iterator, robots.end());

    // Remove the robot from the RobotManager
    robot_manager_.remove_robot_by_id(robotId);
}

// Method to add a new task to the system
void DataManager::AddTask(TaskData& task) {
    // Convert wxString to std::string for task room selection and task robot selection
    std::string room_str = std::string(task.taskRoom.mb_str());
    std::string robot_str = task.taskRobot.robotID;

    tasks.push_back(task);

    int robot_id = std::stoi(robot_str);
    int room_num = std::stoi(room_str);

    // Write task to the database
    mongo_database.write_task(robot_id, room_num);
}

// Get available robots for task allocation
std::vector<robots::Robots> DataManager::GetAvailableRobots() {
    std::vector<robots::Robots> robotVector = mongo_database.read_all_robots();
    std::vector<robots::Robots> availableRobotVector;

    for (robots::Robots& robot : robotVector) {
        if (robot.get_task_status() == "Available") {
            availableRobotVector.push_back(robot);
        }
    }

    return availableRobotVector;
}
