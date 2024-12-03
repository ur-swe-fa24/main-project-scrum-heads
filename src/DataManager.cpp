#include "DataManager.h"
#include <algorithm>
#include <wx/string.h>
#include <chrono>

DataManager::DataManager() : keep_running_(false) {
    // Initialize the MongoDB client and update the list of IDs
    UpdateIds();
}

DataManager::~DataManager() {
    // Stop the task update thread if running
    stopTaskUpdateThread();
}

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

void DataManager::AddRobot(RobotData& robot) {
    int new_id = GetNextAvailableRobotId();  // Get a new unique ID

    // Convert wxString to std::string for robotSize and robotFunction
    std::string size_str = std::string(robot.robotSize.mb_str());
    std::string function_str = std::string(robot.robotFunction.mb_str());

    // Create a new robot instance with the new ID and the provided robot data
    robots::Robots new_robot(new_id, size_str, 100, 100, "None", "Available", Room(), function_str, 0);
//     robots::Robots new_robot(new_id, size_str, 100, 100, "None", "Available", 0, function_str, 0);

    
    // Write the new robot to the MongoDB database
    mongo_database.write_robot(new_robot);

    // Update the RobotData with its assigned ID and add to local vectors
    robot.robotID = std::to_string(new_id);
    robots.push_back(robot);
    robot_manager_.add_robot(new_robot);

    // Append the new ID to the list of IDs
    ids.push_back(new_id);
}

void DataManager::UpdateIds() {
    ids = mongo_database.get_all_ids();
}

int DataManager::GetNextAvailableRobotId() {
    id = 1;  // Start from ID 1

    // Find the next available ID that is not already used
    while (std::find(ids.begin(), ids.end(), id) != ids.end()) {
        ++id;
    }

    return id;
}

std::string DataManager::GetIDString() {
    std::string IDString = std::to_string(id);
    return IDString;
}

robots::Robots DataManager::GetAllRobotInfo(int robotId) {
    robots::Robots clicked_robot = mongo_database.read_robot(robotId);
    return clicked_robot;
}

void DataManager::DeleteRobot(int robotId) {
    mongo_database.delete_robot(robotId);

    // Remove the robot from the vector of RobotData
    std::string robotIdStr = std::to_string(robotId);
    for (auto iterator = robots.begin(); iterator != robots.end(); ++iterator) {
        if (iterator->robotID == robotIdStr) {
            robots.erase(iterator);
            break;
        }
    }

    // Remove the robot from the RobotManager
    robot_manager_.remove_robot_by_id(robotId);
}

void DataManager::AddTask(TaskData& task) {
    // Add task to task vector
    tasks.push_back(task);

    // Retrieve and update robot data
    int robot_id = std::stoi(task.taskRobot.robotID);
    robots::Robots task_robot = GetAllRobotInfo(robot_id);
    task_robot.update_task_status("Ongoing");

    // Convert task room (wxString) to Room object and assign it to the robot
    Room task_room(task.taskRoom.mb_str());
    task_robot.update_task_room(task_room);

    // Write task to the MongoDB and update robot status
    mongo_database.write_task(task_robot);
}

std::vector<robots::Robots> DataManager::GetAvailableRobots() {
    std::vector<robots::Robots> all_robots = mongo_database.read_all_robots();
    std::vector<robots::Robots> available_robots;

    for (auto& robot : all_robots) {
        if (robot.get_task_status() == "Available") {
            available_robots.push_back(robot);
        }
    }

    return available_robots;
}

// Start the thread that updates task progress
void DataManager::startTaskUpdateThread() {
    keep_running_ = true;
    task_update_thread_ = std::thread(&DataManager::taskUpdateLoop, this);
}

// Stop the task update thread safely
void DataManager::stopTaskUpdateThread() {
    keep_running_ = false;
    if (task_update_thread_.joinable()) {
        task_update_thread_.join();
    }
}

// The task update loop runs in a separate thread
void DataManager::taskUpdateLoop() {
    using namespace std::chrono_literals;
    while (keep_running_) {
        {
            std::lock_guard<std::mutex> lock(robot_mutex_);

            // Fetch all ongoing tasks and update progress
            std::vector<robots::Robots> ongoing_tasks = mongo_database.read__all_ongoing_tasks();
            for (auto& robot : ongoing_tasks) {
                if (robot.get_task_status() == "Ongoing") {
                    int progress = robot.get_task_percent();
                    if (progress < 100) {
                        robot.update_task_percent(progress + 10); // Increase progress by 10% for each loop
                        calculate_error_status(robot); // Randomly update error status

                        if (robot.get_task_percent() >= 100) {
                            robot.update_task_status("Complete");
                            mongo_database.update_task_status({robot});
                            robot_manager_.remove_robot_by_id(robot.get_id());
                            robot_manager_.add_robot(robot);
                        }

                        // Update MongoDB with the new robot status
                        mongo_database.update_task_status({robot});
                    } else if (progress >= 100 && robot.get_task_status() == "Complete") {
                        // Update status to available after task completion
                        robot.update_task_status("Available");
                        mongo_database.update_task_status({robot});
                        robot_manager_.remove_robot_by_id(robot.get_id());
                        robot_manager_.add_robot(robot);
                    } else if (robot.get_task_status() == "Cancelled") {
                        // If cancelled, make the robot available again
                        robot.update_task_status("Available");
                        robot.update_task_percent(0);
                        mongo_database.update_task_status({robot});
                        robot_manager_.remove_robot_by_id(robot.get_id());
                        robot_manager_.add_robot(robot);
                    }
                }
            }
        }

        // Sleep for 1 second before the next update
        std::this_thread::sleep_for(1s);
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
