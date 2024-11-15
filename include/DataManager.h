#pragma once

// #include "../wxWidgets/Project_Implementation/feBaseFrame.hpp"  // Assuming DataManager needs access to the base frame
// #include <sstream>
#include <string>
// #include "../wxWidgets/Project_Implementation/baseFrame.hpp"
#include <wx/string.h>
#include "adapters/mongo_adapter.hpp"

// struct RobotData;

struct RobotData {
    std::string robotID;
    wxString robotSize;
    wxString robotFunction;
};


// DataManager class manages data operations between the GUI, simulation, and the MongoDB database.
class DataManager {
public:
    DataManager();
  
    ~DataManager();


    void SendRobotsData(const std::vector<RobotData>& robots);

    //getter function for vector of RobotData
    std::vector<RobotData>& GetRobots();
    void AddRobot(RobotData& robot);
    void UpdateIds();
    std::string GetIDString(); //this is for the UI to access id easily when robot is made

private:
    int GetNextAvailableRobotId();  // New method to find the next available robot ID

    int id;

    std::vector<RobotData> robots;  // Stores robot data in a local vector
    std::vector<int> ids;  // Stores robot IDs currently in the database
    adapters::Mongo_Adapter mongo_database{};  // MongoDB adapter to interact with the database
};
