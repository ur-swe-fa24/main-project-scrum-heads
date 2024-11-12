#pragma once

// #include <mongocxx/client.hpp>
// #include <mongocxx/instance.hpp>
#include "../wxWidgets/Project_Implementation/feBaseFrame.hpp"  // Assuming DataManager needs access to the base frame
// #include "Simulation.hpp"   // Assuming simulation class 
#include <sstream>
#include <string>

struct RobotData;


// DataManager class manages data operations between the GUI, simulation, and the MongoDB database.
class DataManager {
public:
    DataManager();
    // Constructor initializing DataManager with a pointer to the GUI frame.
    // DataManager(MyFEBaseFrame* feFrame);
    // Destructor to handle cleanup if necessary.
    ~DataManager();

    // // Method to update robot data from GUI, process it via simulation, and store results.
    // void updateRobotDataFromGUI();
    // // Method to refresh GUI components with the latest data from the database.
    // void refreshDataInGUI();

    void SendRobotsData(const std::vector<RobotData>& robots);

    std::vector<RobotData>& GetRobots();
    void AddRobot(const RobotData& robot);

private:
    std::vector<RobotData> robots;
    // mongocxx::instance instance{}; // MongoDB driver instance to manage MongoDB client lifecycle.
    // mongocxx::client client;       // MongoDB client for database operations.
    // feBaseFrame* feBaseFrame;      // Pointer to GUI frame for direct interaction.

    // // Retrieves simulation results from the database to display in the GUI.
    // std::string retrieveSimulationResults();
    // // Stores the results of the simulation into the MongoDB database.
    // void storeSimulationResults(const std::string& results);
    // // Method to simulate task performance by a robot, returning the outcome as a string.
    // std::string runSimulation(const std::string& data);
    // Helper method to convert a JSON string to a BSON document.
    // bsoncxx::document::value convertToDocument(const std::string& json);
    // Helper method to convert a BSON document to a JSON string.
    // std::string convertToJson(const bsoncxx::document::value& doc);
};
