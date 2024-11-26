#include "DataManager.h"
#include <algorithm>  // Include for std::find
#include <wx/string.h>
#include <chrono>  // For std::chrono_literals

// Constructor: Initializes the MongoDB client, updates the list of robot IDs, and starts the update thread.
DataManager::DataManager() 
    : running(true)  // Set running to true to keep the thread running initially
{
    // Initialize the MongoDB client and update the list of IDs
    UpdateIds();
    // Start the thread that will handle periodic updates of robot status
    update_thread = std::thread(&DataManager::UpdateRobotStatusLoop, this);
}

// Destructor: Handles cleanup, stops the thread safely.
DataManager::~DataManager() {
    running = false;  // Set running to false to signal the thread to stop
    if (update_thread.joinable()) {
        update_thread.join();  // Wait for the thread to finish
    }
}

// Method to receive and process robots data (placeholder for possible future usage).
// void DataManager::SendRobotsData(const std::vector<RobotData>& robots) {
//     // Process each robot and prepare for database insertion or other actions
//     for (const auto& robot : robots) {
//         std::cout << "Size: " + robot.robotSize + ", Function: " + robot.robotFunction << std::endl;
//     }

//     // You can then call the database model to save or update robot data here
// }

// Getter method for vector of RobotData (simplified version for UI use).
std::vector<RobotData>& DataManager::GetRobots() {
    std::lock_guard<std::mutex> lock(data_mutex);  // Lock the mutex to ensure safe access
    return robots;
}

// Getter method for vector of TaskData (used for managing tasks).
std::vector<TaskData>& DataManager::GetTasks() {
    std::lock_guard<std::mutex> lock(data_mutex);  // Lock the mutex to ensure safe access
    return tasks;
}

// Method to add a new robot to the system.
void DataManager::AddRobot(RobotData& robot) {
    int new_id = GetNextAvailableRobotId();  // Get a new unique ID for the robot.

    // Convert wxString to std::string for robotSize and robotFunction.
    std::string size_str = std::string(robot.robotSize.mb_str());
    std::string function_str = std::string(robot.robotFunction.mb_str());

    // Create a new robot instance with the new ID and provided robot data.
    robots::Robots new_robot(new_id, size_str, 100, 100, "None", "Available", 0, function_str, 0);
    
    {
        // Lock the mutex while interacting with shared data.
        std::lock_guard<std::mutex> lock(data_mutex);

        // Write the new robot to the MongoDB database.
        mongo_database.write_robot(new_robot);

        // Update the RobotData of the added robot with its assigned ID.
        robot.robotID = std::to_string(new_id);

        // Add the new robot data to the local list of robots.
        robots.push_back(robot);

        // Append the new ID to the list of IDs.
        ids.push_back(new_id);
    }
}

// Method to update the list of robot IDs from the MongoDB database.
void DataManager::UpdateIds() {
    std::lock_guard<std::mutex> lock(data_mutex);  // Lock the mutex to ensure safe access
    ids = mongo_database.get_all_ids();
}

// Method to find the next available robot ID that is not in use.
int DataManager::GetNextAvailableRobotId() {
    std::lock_guard<std::mutex> lock(data_mutex);  // Lock the mutex to ensure safe access
    id = 1;  // Start ID from 1.

    // Find the next available ID that is not already used.
    while (std::find(ids.begin(), ids.end(), id) != ids.end()) {
        ++id;  // Increment ID until an available one is found.
    }

    return id;
}

// Method to get the current robot ID as a string (used for easy interaction with the UI).
std::string DataManager::GetIDString() {
    std::lock_guard<std::mutex> lock(data_mutex);  // Lock the mutex to ensure safe access
    return std::to_string(id);
}

// Method to get all information of a robot by its ID (used to display details in the GUI).
robots::Robots DataManager::GetAllRobotInfo(int robotId)
{
    std::lock_guard<std::mutex> lock(data_mutex);  // Lock the mutex to ensure safe access
    robots::Robots clicked_robot = mongo_database.read_robot(robotId);
    return clicked_robot;
}

// Method to delete a robot from the system given its ID.
void DataManager::DeleteRobot(int robotId)
{
    {
        std::lock_guard<std::mutex> lock(data_mutex);  // Lock the mutex to ensure safe access

        // First, remove the robot from the MongoDB database.
        mongo_database.delete_robot(robotId);

        // Then, remove the robot from the local vector of RobotData.
        std::string robotIdStr = std::to_string(robotId);
        for (auto iterator = robots.begin(); iterator != robots.end(); ++iterator) {
            if (iterator->robotID == robotIdStr) {
                robots.erase(iterator);  // Remove the robot from the vector.
                break;  // Exit the loop after removal.
            }
        }
    }
}

// Method to add a new task to the system.
void DataManager::AddTask(TaskData& task) {
    std::lock_guard<std::mutex> lock(data_mutex);  // Lock the mutex to ensure safe access

    // Convert wxString to std::string for task room selection and robot ID selection.
    std::string room_str = std::string(task.taskRoom.mb_str());
    std::string robot_str = task.taskRobot.robotID;

    // Add the new task to the local list of tasks.
    tasks.push_back(task); 
}

// Method to get a list of available robots for task assignment.
std::vector<robots::Robots> DataManager::GetAvailableRobots()
{
    std::lock_guard<std::mutex> lock(data_mutex);  // Lock the mutex to ensure safe access

    // Retrieve all robots from the MongoDB database.
    std::vector<robots::Robots> robotVector = mongo_database.read_all_robots();

    // Create a vector to hold available robots.
    std::vector<robots::Robots> availableRobotVector;

    // Iterate through the robot list to find robots with status "Available".
    for (robots::Robots robot : robotVector) {
        if (robot.get_task_status() == "Available") {
            availableRobotVector.push_back(robot);
        }
    }

    return availableRobotVector;  // Return the list of available robots.
}

// Background thread loop that updates robot statuses in the MongoDB database every second.
void DataManager::UpdateRobotStatusLoop() {
    using namespace std::chrono_literals;

    while (running) {
        {
            // Lock the mutex while interacting with shared data.
            std::lock_guard<std::mutex> lock(data_mutex);

            // Iterate through all robots and update their status in the MongoDB database.
            for (auto& robot : robots) {
                int robotId = std::stoi(robot.robotID);
                robots::Robots full_robot_info = mongo_database.read_robot(robotId);

                // Example of modifying battery level to simulate work progress.
                //int updated_battery_level = full_robot_info.get_battery_level() - 1;  // Decrease battery by 1%
                //if (updated_battery_level < 0) updated_battery_level = 0;  // Prevent negative battery levels.

                // Update the robot's battery level in the database.
                //mongo_database.update_robot(robotId, full_robot_info.get_water_level(), updated_battery_level);
            }
        }
        
        std::this_thread::sleep_for(1s);  // Wait for 1 second before the next update.
    }
}
