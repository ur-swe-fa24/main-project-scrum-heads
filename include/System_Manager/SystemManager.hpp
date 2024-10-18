#ifndef SYSTEM_MANAGER_HPP
#define SYSTEM_MANAGER_HPP

#include <string>
#include "spdlog/spdlog.h"

// Forward declarations
class SimulationEngine;
class DatabaseManager;

class SystemManager {
public:
    SystemManager();
    ~SystemManager();

    // Methods for task assignment
    void assignCleaningTask(const std::string& taskId, const std::string& robotId, const std::string& taskDetails);
    
    // Method to add robots
    void addRobot(const std::string& robotId, const std::string& robotSpecs);

private:
    SimulationEngine* simulationEngine;
    DatabaseManager* databaseManager;

    // Utility method to log messages
    void log(const std::string& message);
};

#endif // SYSTEM_MANAGER_HPP
