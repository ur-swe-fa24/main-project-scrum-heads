#ifndef ROBOT_MANAGER_HPP
#define ROBOT_MANAGER_HPP

#include "Robot.hpp"
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
    std::optional<Robots> find_robot_by_id(int robot_id) const;

    // Remove a robot by its ID
    bool remove_robot_by_id(int robot_id);

    // Display all robots' statuses (e.g., for a field engineer)
    void display_all_robots_status() const;

    // Get the total number of robots
    int get_robot_count() const { return robot_list_.size(); }

private:
    // List of robots managed by this class
    std::vector<Robots> robot_list_;
};

}  // namespace robots

#endif // ROBOT_MANAGER_HPP