#include "robot_manager.hpp"
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

// Get the list of all robots
std::vector<Robots>& RobotManager::get_list() {
    return robot_list_;
}



}  // namespace robots