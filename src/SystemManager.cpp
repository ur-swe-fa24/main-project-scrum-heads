#include "System_Manager/SystemManager.hpp"

// Constructor
SystemManager::SystemManager() {
    simulationEngine = new SimulationEngine();
    databaseManager = new DatabaseManager();
    spdlog::info("System Manager Initialized");
}

// Destructor
SystemManager::~SystemManager() {
    delete simulationEngine;
    delete databaseManager;
    spdlog::info("System Manager Shutdown");
}

// Method to assign cleaning tasks
void SystemManager::assignCleaningTask(const std::string& taskId, const std::string& robotId, const std::string& taskDetails) {
    spdlog::info("Starting task assignment process for task ID: {}, robot ID: {}", taskId, robotId);
    
    bool isSuccessful = simulationEngine->simulateTask(taskId, robotId, taskDetails);
    if (isSuccessful) {
        databaseManager->updateTaskStatus(taskId, "assigned");
        spdlog::info("Task ID: {} successfully assigned to robot ID: {}", taskId, robotId);
    } else {
        spdlog::error("Failed to assign task ID: {} to robot ID: {} due to simulation failure", taskId, robotId);
    }
}

// Method to add robots
void SystemManager::addRobot(const std::string& robotId, const std::string& robotSpecs) {
    spdlog::info("Attempting to add a new robot with ID: {}", robotId);
    
    bool isAdded = databaseManager->addNewRobot(robotId, robotSpecs);
    if (isAdded) {
        spdlog::info("Robot with ID: {} successfully added", robotId);
    } else {
        spdlog::error("Failed to add robot with ID: {}", robotId);
    }
}

// Utility method to log messages using spdlog
void SystemManager::log(const std::string& message) {
    spdlog::info(message);
}