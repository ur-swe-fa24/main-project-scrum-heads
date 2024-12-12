#ifndef ROBOT_MANAGER_HPP
#define ROBOT_MANAGER_HPP

#include "robot.hpp"
#include <vector>
#include <string>
#include <optional>

namespace robots {

class RobotManager {
public:
    // Constructor
    RobotManager() = default;

    // Add a robot to the manager's list
    void add_robot(const Robots& new_robot);

    // Find a robot by its ID (returns std::optional<Robots>)
    Robots& find_robot_by_id(int robot_id);

    // Remove a robot by its ID
    bool remove_robot_by_id(int robot_id);

    // Get the total number of robots
    int get_robot_count() const { return robot_list_.size(); }

    std::vector<Robots>& get_list();

private:
    // List of robots managed by this class
    std::vector<Robots> robot_list_;
};

}  // namespace robots

#endif // ROBOT_MANAGER_HPP
