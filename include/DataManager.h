#pragma once

// #include "../wxWidgets/Project_Implementation/feBaseFrame.hpp"  // Assuming DataManager needs access to the base frame
// #include <sstream>
#include <string>
// #include "../wxWidgets/Project_Implementation/baseFrame.hpp"
#include <wx/string.h>
#include "adapters/mongo_adapter.hpp"
#include "robot.hpp"

// struct for RobotData
struct RobotData {
    std::string robotID;
    wxString robotSize;
    wxString robotFunction;
};

//struct for TaskData
struct TaskData {
    wxString taskRoom;
    RobotData taskRobot;
};


// DataManager class manages data operations between the GUI, simulation, and the MongoDB database.
class DataManager {
public:
    DataManager();
  
    ~DataManager();


    void SendRobotsData(const std::vector<RobotData>& robots);

    //getter function for vector of RobotData
    std::vector<RobotData>& GetRobots();

    //getter function for vector of TaskData
    std::vector<TaskData>& GetTasks();

    //method for adding robot (receiving robotdata from UI)
    void AddRobot(RobotData& robot);
    void UpdateIds();
    std::string GetIDString(); //this is for the UI to access id easily when robot is made

    //method for adding task (after receiving taskdata from UI)
    void AddTask(TaskData& task);

    //gets complete robot info (whole robot of type robots)
    robots::Robots GetAllRobotInfo(int robotId);

    //deletes a robot given ID from UI
    void DeleteRobot(int robotId);

    //gets available robots for task allocation
    std::vector<robots::Robots> GetAvailableRobots();

    //needs implementation!
    //gets available rooms for task allocation
    // std::vector<rooms::Rooms> GetAvailableRooms();

private:
    int GetNextAvailableRobotId();  // New method to find the next available robot ID

    int id;

    std::vector<RobotData> robots;  // Stores robot data in a local vector
    std::vector<TaskData> tasks;  // Stores task data in a local vector
    std::vector<int> ids;  // Stores robot IDs currently in the database
    adapters::Mongo_Adapter mongo_database{};  // MongoDB adapter to interact with the database

    void AddRooms();
    //add vector of rooms here
};
