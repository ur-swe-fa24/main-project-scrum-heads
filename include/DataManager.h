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
    std::vector<robots::Robots> GetAvailableRobots();

    // Start and stop task update thread
    void startTaskUpdateThread();
    void stopTaskUpdateThread();

    //gets available robots for task allocation
    std::vector<robots::Robots> GetAvailableRobots();

    //needs implementation!
    //gets available rooms for task allocation
    // std::vector<rooms::Rooms> GetAvailableRooms();

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
