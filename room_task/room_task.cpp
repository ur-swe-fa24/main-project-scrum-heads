#include "room_task.hpp"
#include "spdlog/spdlog.h"
#include <thread>
#include <chrono>

namespace tasks {

int RoomTask::calculate_task_duration() const {
    switch (room_size_) {
        case RoomSize::SMALL: return 3000;    // Shortest task duration (ms)
        case RoomSize::MEDIUM: return 6000;   // Medium task duration (ms)
        case RoomSize::LARGE: return 12000;   // Longest task duration (ms)
    }
    return 0;  // Default case
}

int RoomTask::get_resource_usage() const {
    switch (room_size_) {
        case RoomSize::SMALL: return 10;
        case RoomSize::MEDIUM: return 40;
        case RoomSize::LARGE: return 90;
    }
    return 0;  // Default case
}

void RoomTask::perform_task(robots::Robots& robot) {
    int task_duration = calculate_task_duration();
    int resource_usage = get_resource_usage();
    int progress_steps = 10;  // Display progress in 10% increments
    int step_duration = task_duration / progress_steps;

    spdlog::info("Starting task in room of size: {}", 
                 (room_size_ == RoomSize::SMALL ? "Small" :
                 room_size_ == RoomSize::MEDIUM ? "Medium" : "Large"));

    // Check if the robot has enough resources
    if (robot.get_battery_level() < resource_usage || robot.get_water_level() < resource_usage) {
        spdlog::warn("Insufficient resources to complete the task.");
        return;
    }

    // Display progress in increments
    for (int i = 1; i <= progress_steps; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(step_duration));
        spdlog::info("Task progress: {}%", i * 10);
    }

    // Update the robot's battery and water levels
    robot.update_battery_level(robot.get_battery_level() - resource_usage);
    robot.update_water_level(robot.get_water_level() - resource_usage);

    spdlog::info("Task completed. Remaining battery: {}%, Remaining water: {}%",
                 robot.get_battery_level(), robot.get_water_level());
}

} // namespace tasks
