#pragma once

#include <string>
#include <wx/string.h>
#include "adapters/mongo_adapter.hpp"
#include "robot.hpp"
#include <thread>
#include <atomic>  // For atomic flag control
#include <mutex>   // To synchronize access to shared data

// Struct for RobotData - Simplified representation of a robot for UI use.
struct RobotData {
    std::string robotID;
    wxString robotSize;
    wxString robotFunction;
};

// Struct for TaskData - Represents a task to be assigned to a robot.
struct TaskData {
    wxString taskRoom;  // The room where the task needs to be performed.
    RobotData taskRobot;  // The robot assigned to perform the task.
};

// DataManager class manages data operations between the GUI, simulation, and the MongoDB database.
class DataManager {
public:
    DataManager();  // Constructor to initialize MongoDB and update IDs.
    ~DataManager();  // Destructor to stop the thread and clean up.

    void SendRobotsData(const std::vector<RobotData>& robots);  // Placeholder function.

    // Getter functions for RobotData and TaskData vectors.
    std::vector<RobotData>& GetRobots();  // Get a vector of all current robots in the system.
    std::vector<TaskData>& GetTasks();  // Get a vector of all current tasks.

    // Methods for adding robots and tasks to the system.
    void AddRobot(RobotData& robot);  // Add a new robot to the system.
    void AddTask(TaskData& task);  // Add a new task to the system.

    void UpdateIds();  // Update the list of robot IDs from the MongoDB database.
    std::string GetIDString();  // Get the current ID as a string for easy use in UI.

    // Get complete robot information based on robot ID.
    robots::Robots GetAllRobotInfo(int robotId);

    // Delete a robot from the system using its ID.
    void DeleteRobot(int robotId);

    // Get a list of available robots (not currently assigned to a task).
    std::vector<robots::Robots> GetAvailableRobots();

private:
    void UpdateRobotStatusLoop();  // Background loop to update robot statuses in the database.
    int GetNextAvailableRobotId();  // Find the next available robot ID that is not in use.

    int id;  // Tracks the current ID for robots.
    std::vector<RobotData> robots;  // Stores a list of all robots.
    std::vector<TaskData> tasks;  // Stores a list of tasks.
    std::vector<int> ids;  // Stores robot IDs currently in the database.
    adapters::Mongo_Adapter mongo_database{};  // MongoDB adapter to interact with the database.

    // Threading elements
    std::thread update_thread;  // Thread that will update the robots' status.
    std::atomic<bool> running;  // Control flag to stop the thread safely.
    std::mutex data_mutex;  // Mutex to prevent race conditions.
};
