#include "DataManager.h"
#include <algorithm>  // Include for std::find
#include <wx/string.h>

DataManager::DataManager() 
{
    // Initialize the MongoDB client and update the list of IDs
    UpdateIds();
}

// Destructor: Handles cleanup, if necessary.
DataManager::~DataManager() {}

// Method to receive and process robots data
// void DataManager::SendRobotsData(const std::vector<RobotData>& robots) {
//     // Process each robot and prepare for database insertion or other actions
//     for (const auto& robot : robots) {
//         std::cout << "Size: " + robot.robotSize + ", Function: " + robot.robotFunction << std::endl;
//     }

//     // You can then call the database model to save or update robot data here
// }


// Getter method for vector of robots
std::vector<RobotData>& DataManager::GetRobots() {
    return robots;
}

// Method to add a new robot to the system
void DataManager::AddRobot(RobotData& robot) {
    int new_id = GetNextAvailableRobotId();  // Get a new unique ID

    // robot.robotID = new_id;
    // std::cout << robot.robotID << std::endl;

    // Convert wxString to std::string for robotSize and robotFunction
    std::string size_str = std::string(robot.robotSize.mb_str());
    std::string function_str = std::string(robot.robotFunction.mb_str());

    // Create a new robot instance with the new ID and the provided robot data
    robots::Robots new_robot(new_id, size_str, 100, 100, "None", "Idle", 0, function_str, 0, 0);
    
    // Write the new robot to the MongoDB database
    mongo_database.write_robot(new_robot);

    robot.robotID = std::to_string(new_id);
    // Add the new robot data to the local list of robots
    robots.push_back(robot);

    // Append the new ID to the list of IDs
    ids.push_back(new_id);

    std::cout << mongo_database.read_robot(new_id) << std::endl;
}

// Method to update the list of robot IDs from the MongoDB database
void DataManager::UpdateIds() {
    // ids = mongo_database.get_all_ids();
}

// Method to find the next available robot ID
int DataManager::GetNextAvailableRobotId() {
    id = 21;  // Start from ID 1

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
