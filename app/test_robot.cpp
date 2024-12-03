#include "RobotManager.hpp"
#include <iostream> // For demonstration

int main() {
    robots::RobotManager manager;

    // Create some robots
    robots::Robots robot1(1, "Small", 50, 80, "None", "Idle", 0, "Cleaning", 0);
    robots::Robots robot2(2, "Medium", 60, 70, "Low Battery", "In Progress", 101, "Mapping", 50);

    // Add robots to the manager
    manager.add_robot(robot1);
    manager.add_robot(robot2);

    // Get all robot statuses
    auto statuses = manager.get_all_robot_statuses();

    // Display each robot's status
    for (const auto& status : statuses) {
        for (const auto& field : status) {
            std::cout << field << " ";
        }
        std::cout << "\n";
    }

    return 0;
}