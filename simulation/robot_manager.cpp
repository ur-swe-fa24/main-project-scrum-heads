#include "RobotManager.hpp"
#include <vector>

namespace robots {

// Add a robot to the manager's list
void RobotManager::add_robot(const Robots& new_robot) {
    robot_list_.push_back(new_robot);
}

// Find a robot by its ID
std::optional<Robots> RobotManager::find_robot_by_id(int robot_id) const {
    for (const auto& robot : robot_list_) {
        if (robot.get_id() == robot_id) {
            return robot; // Return the found robot wrapped in std::optional
        }
    }
    return std::nullopt; // Return empty optional if not found
}

// Remove a robot by its ID
bool RobotManager::remove_robot_by_id(int robot_id) {
    auto it = std::remove_if(robot_list_.begin(), robot_list_.end(),
                             [robot_id](const Robots& robot) {
                                 return robot.get_id() == robot_id;
                             });
    if (it != robot_list_.end()) {
        robot_list_.erase(it, robot_list_.end());
        return true; // Robot removed successfully
    }
    return false; // Robot with the given ID not found
}

// Get all robots' statuses as a vector of vectors
std::vector<std::vector<std::string>> RobotManager::get_all_robot_statuses() const {
    std::vector<std::vector<std::string>> statuses;

    for (const auto& robot : robot_list_) {
        statuses.push_back({
            std::to_string(robot.get_id()),             // Robot ID
            robot.get_size(),                           // Size
            std::to_string(robot.get_water_level()),    // Water Level
            std::to_string(robot.get_battery_level()),  // Battery Level
            robot.get_error_status(),                  // Error Status
            robot.get_task_status(),                   // Task Status
            std::to_string(robot.get_task_room()),      // Task Room
            robot.get_function_type(),                 // Function Type
            std::to_string(robot.get_task_percent())   // Task Completion
        });
    }

    return statuses;
}

}  // namespace robots
