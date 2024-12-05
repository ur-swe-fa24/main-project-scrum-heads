#ifndef ROBOT_DO_TASK_HPP
#define ROBOT_DO_TASK_HPP

#include <string>
#include <vector>
#include "robot.hpp"

namespace robot_tasks {

// Function to check robot readiness based on room size, water level, and battery level
bool check_robot(const std::string& room_size, int water_level, int battery_level);

// Function to perform a task with a robot
int do_task(robots::Robots& robot, const std::string& room_size);

// Function to recharge a list of robots
int robot_charge(std::vector<robots::Robots>& robot_list);

} // namespace robot_tasks

#endif // ROBOT_DO_TASK_HPP
