#pragma once

#include <string>
#include <vector>
#include <thread>
#include <atomic>
#include <mutex>
#include <wx/string.h>
#include "adapters/mongo_adapter.hpp"
#include "robot.hpp"
#include "robot_manager.hpp"
#include "include/robot_do_task.hpp"

// struct for RobotData
struct RobotData {
    std::string robotID;
    wxString robotSize;
    wxString robotFunction;
};

// struct for TaskData
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

    // Start and stop the thread to update database with task progress
    void StartUpdateThread();
    void StopUpdateThread();

private:
    int GetNextAvailableRobotId();
    void UpdateDatabaseWithTaskProgress();  // Function for the thread to continuously update task progress in MongoDB

    int id;

    std::vector<RobotData> robots;
    std::vector<TaskData> tasks;
    std::vector<int> ids;

    adapters::Mongo_Adapter mongo_database{};
    robots::RobotManager robot_manager_;

    // Thread handling
    std::thread update_thread_;
    std::atomic<bool> running_;
    std::mutex robot_mutex_;  // Protect robot data during thread operations
};

