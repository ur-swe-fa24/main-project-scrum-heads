#ifndef ROBOT_DO_TASK_HPP
#define ROBOT_DO_TASK_HPP

#include <string>
#include <vector>
#include <atomic>
#include <thread>
#include <map>
#include <mutex>
#include "robot.hpp"

namespace robot_tasks {

// Function to calculate task duration based on room size
int calculate_task_duration(const std::string& room_size);

// Function to calculate resource usage based on room size
int get_resource_usage(const std::string& room_size);

// Function to check if a robot has enough water and battery to finish its task
bool check_robot(robots::Robots& robot);

// Function to fix a robot's error status and reset it to be ready for tasks
void fix(robots::Robots& robot);

// Function to calculate the error status for a robot (randomly assigning errors)
void calculate_error_status(robots::Robots& robot);

// Function to execute the robot task loop
void execute(std::vector<robots::Robots>& robot_list_);

// Start the task execution loop in a separate thread
void start_execute_thread(std::vector<robots::Robots>& robot_list_);

// Stop the task execution loop and join the thread
void stop_execute_thread();

} // namespace robot_tasks

#endif // ROBOT_DO_TASK_HPP
