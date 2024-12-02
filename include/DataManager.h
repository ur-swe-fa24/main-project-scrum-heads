#pragma once

#include <string>
#include <thread>  // For threading
#include <atomic>  // For atomic variables to control the thread
#include <wx/string.h>
#include "adapters/mongo_adapter.hpp"
#include "robot.hpp"

// Struct for RobotData
struct RobotData {
    std::string robotID;
    wxString robotSize;
    wxString robotFunction;
};

// Struct for TaskData
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
    std::vector<RobotData>& GetRobots();
    std::vector<TaskData>& GetTasks();
    void AddRobot(RobotData& robot);
    void UpdateIds();
    std::string GetIDString(); // this is for the UI to access ID easily when robot is made
    void AddTask(TaskData& task);
    robots::Robots GetAllRobotInfo(int robotId);
    void DeleteRobot(int robotId);
    std::vector<robots::Robots> GetAvailableRobots();

private:
    int GetNextAvailableRobotId();  // New method to find the next available robot ID

    // Thread control members
    void StartTaskUpdateThread();
    void StopTaskUpdateThread();
    void TaskUpdateLoop(); // Thread loop to update task progress

    int id;
    std::vector<RobotData> robots;  // Stores robot data in a local vector
    std::vector<TaskData> tasks;  // Stores task data in a local vector
    std::vector<int> ids;  // Stores robot IDs currently in the database
    adapters::Mongo_Adapter mongo_database{};  // MongoDB adapter to interact with the database

    std::thread task_update_thread_;  // Thread for task updates
    std::atomic<bool> running_{false};  // Controls the thread execution
};
