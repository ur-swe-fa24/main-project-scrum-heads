#pragma once

// #include "../wxWidgets/Project_Implementation/feBaseFrame.hpp"  // Assuming DataManager needs access to the base frame
// #include <sstream>

#include <string>
// #include "../wxWidgets/Project_Implementation/baseFrame.hpp"
#include <wx/string.h>
#include "adapters/mongo_adapter.hpp"

// struct RobotData;

struct RobotData {
    wxString robotSize;
    wxString robotFunction;
};


// DataManager class manages data operations between the GUI, simulation, and the MongoDB database.
class DataManager {
public:
    DataManager();
  
    ~DataManager();

    void SendRobotsData(const std::vector<RobotData>& robots);

    std::vector<RobotData>& GetRobots();
    void AddRobot(const RobotData& robot);
    void UpdateIds();

private:
    int GetNextAvailableRobotId();  // New method to find the next available robot ID

    std::vector<RobotData> robots;  // Stores robot data in a local vector
    std::vector<int> ids;  // Stores robot IDs currently in the database
    adapters::Mongo_Adapter mongo_database{};  // MongoDB adapter to interact with the database
};
