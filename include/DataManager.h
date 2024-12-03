#pragma once

#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>
#include <wx/string.h>
#include "adapters/mongo_adapter.hpp"
#include "robot.hpp"
#include "robot_manager.hpp"
#include "robot_do_task.hpp"

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
    std::string GetIDString();
    void AddTask(TaskData& task);
    robots::Robots GetAllRobotInfo(int robotId);
    void DeleteRobot(int robotId);
    std::vector<robots::Robots> GetAvailableRobots();

    // Start and stop task update thread
    void startTaskUpdateThread();
    void stopTaskUpdateThread();

private:
    void taskUpdateLoop(); // Loop that runs to update tasks in a thread
    int GetNextAvailableRobotId();

    int id;
    std::vector<RobotData> robots;  // Stores robot data in a local vector
    std::vector<TaskData> tasks;  // Stores task data in a local vector
    std::vector<int> ids;  // Stores robot IDs currently in the database
    adapters::Mongo_Adapter mongo_database{};  // MongoDB adapter to interact with the database
    robots::RobotManager robot_manager_;  // Manages the list of robots

    // Threading related members
    std::thread task_update_thread_;
    std::atomic<bool> keep_running_; // Controls the running state of the thread
    std::mutex robot_mutex_; // Mutex to protect shared resources
};
