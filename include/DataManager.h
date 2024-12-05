#pragma once

#include <string>
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

    void startUpdateThread();
    void stopUpdateThread();

private:
    int GetNextAvailableRobotId();

    int id;
    std::vector<RobotData> robots;
    std::vector<TaskData> tasks;
    std::vector<int> ids;
    adapters::Mongo_Adapter mongo_database{};
    robots::RobotManager robot_manager_;

    // Thread components
    std::thread update_thread_;
    std::mutex data_mutex_;
    std::atomic<bool> keep_updating_{true};
};
