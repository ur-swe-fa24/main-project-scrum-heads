#pragma once

// #include "../wxWidgets/Project_Implementation/feBaseFrame.hpp"  // Assuming DataManager needs access to the base frame
// #include <sstream>
#include <string>
// #include "../wxWidgets/Project_Implementation/baseFrame.hpp"
#include <wx/string.h>
#include "adapters/mongo_adapter.hpp"
#include "robot.hpp"
#include "robot_manager.hpp"
#include <thread>
#include <mutex>
#include <atomic>

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

    //updates TaskData vector from the database
    void UpdateTaskData();

    //getter function for vector of TaskData
    std::vector<TaskData>& GetTasks();

    //getter function for vector of rooms from database
    std::vector<Room> GetRooms();

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

    //gets available rooms for task allocation
    std::vector<Room> GetAvailableRooms();

    //gets all tasks (present and past)
    std::vector<robots::Robots> GetTasksTable();

    void startUpdateThread();
    void stopUpdateThread();

    robots::RobotManager& GetRobotManager();

    // Add the following declaration for deleting all robots (useful for testing)
    void DeleteAllRobots();

    //gets error log from database
    std::vector<std::string> getErrorLog(int robotID);
    robots::Robots update_task_status();
    robots::Robots update_task_room();

    //function to fix robot on FE fix button input
    void FixRobot(int robotID);

    void ChangeRoomAvailability(int roomID, bool isAvailable);

private:
    int GetNextAvailableRobotId();  // New method to find the next available robot ID

    int id;

    std::vector<RobotData> robots;  // Stores robot data in a local vector
    std::vector<TaskData> tasks;  // Stores task data in a local vector
    std::vector<int> ids;  // Stores robot IDs currently in the database
    adapters::Mongo_Adapter mongo_database{};  // MongoDB adapter to interact with the database

    void AddRooms();
    //add vector of rooms here
    std::vector<Room> roomVector;

    robots::RobotManager robot_manager_;

    // Thread components
    std::thread update_thread_;
    std::mutex data_mutex_;
    std::atomic<bool> keep_updating_{true};
};
