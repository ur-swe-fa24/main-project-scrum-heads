#include "DataManager.h"
#include <sstream>  // Include for std::stringstream used in logging

DataManager::DataManager() 
{
    // Initialize the MongoDB client with the default URI
}

// // Constructor: Initializes the DataManager with a reference to the GUI frame.
// DataManager::DataManager(MyFEBaseFrame* feFrame) : feBaseFrame(feFrame)//: client{mongocxx::uri{}}, feBaseFrame(feFrame) 
// {
//     // Initialize the MongoDB client with the default URI
// }

// Destructor: Handles cleanup, if necessary.
DataManager::~DataManager() {}

// // Updates robot data from GUI, processes it via simulation, and stores the results in the database.
// void DataManager::updateRobotDataFromGUI() {
//     // Ensure we have a valid pointer to the MyFEBaseFrame for accessing robot data.
//     auto myFeBaseFrame = dynamic_cast<MyFEBaseFrame*>(feBaseFrame);
//     if (myFeBaseFrame) {
//         // Access the vector of RobotData from the GUI frame.
//         std::vector<RobotData>& robots = myFeBaseFrame->GetRobots();
//         for (const RobotData& robot : robots) {
//             // Run simulation for each robot and store the results.
//             std::string simulatedData = runSimulation(robot.robotPropertyData.ToStdString());
//             storeSimulationResults(simulatedData);
//         }
//     }
// }

// // Refreshes the GUI with the latest data fetched from the MongoDB database.
// void DataManager::refreshDataInGUI() {
//     // Retrieve the latest simulation results from the database.
//     std::string results = retrieveSimulationResults();
//     auto myFeBaseFrame = dynamic_cast<MyFEBaseFrame*>(feBaseFrame);
//     if (myFeBaseFrame) {
//         // Update the GUI display with the fetched results.
//         myFeBaseFrame->updateRobotDisplay(wxString(results));
//     }
// }

// // Simulates task performance by a robot and returns the outcome as a string.
// std::string DataManager::runSimulation(const std::string& data) {
//     // Simulate a medium room cleaning task using robot data.
//     robots::Robots robot(1, "Medium", 100, 100, "None", "Idle", 0, robots::Robots::robotFunction::SCRUB, 0, 0);
//     tasks::RoomTask medium_room_task(tasks::RoomTask::RoomSize::MEDIUM);
//     medium_room_task.perform_task(robot);

//     // Collect the results into a string using a stringstream.
//     std::stringstream log_output;
//     log_output << "After task - Battery level: " << robot.get_battery_level()
//                << "%, Water level: " << robot.get_water_level() << "%";

//     // Log the results using spdlog.
//     spdlog::info(log_output.str());
//     return log_output.str();
// }

// // Stores the simulation results in the MongoDB database.
// void DataManager::storeSimulationResults(const std::string& results) {
//     // Access the collection for robot simulation results.
//     auto collection = client["database_name"]["robot_simulation"];
//     // Convert the results string into a BSON document.
//     auto document = convertToDocument(results);
//     // Insert the document into the MongoDB collection.
//     collection.insert_one(document.view());
// }

// // Retrieves the latest simulation results from the MongoDB database.
// std::string DataManager::retrieveSimulationResults() {
//     // Access the collection for robot simulation results.
//     auto collection = client["database_name"]["robot_simulation"];
//     auto cursor = collection.find({});
//     // Return the first document found as a JSON string.
//     for (auto&& doc : cursor) {
//         return convertToJson(doc);
//     }
//     return "{}";  // Return an empty JSON object if no results are found.
// }

// // Helper function to convert a JSON string to a BSON document.
// bsoncxx::document::value DataManager::convertToDocument(const std::string& json) {
//     return bsoncxx::from_json(json);
// }

// // Helper function to convert a BSON document to a JSON string.
// std::string DataManager::convertToJson(const bsoncxx::document::value& doc) {
//     return bsoncxx::to_json(doc);
// }

// Method to receive and process robots data
void DataManager::SendRobotsData(const std::vector<RobotData>& robots) {
    // Process each robot and prepare for database insertion or other actions
    for (const auto& robot : robots) {
        std::cout << robot.robotPropertyData << std::endl;
    }

    // You can then call the database model to save or update robot data here
}
