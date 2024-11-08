#include "robot_loop_lib.hpp"  // Include the library header containing task
#include "robot.hpp"           // Include robot class header
#include "room_task.hpp"       // Include room task class header
#include "spdlog/spdlog.h"     // For logging output
#include <atomic>              // For atomic variables

int main() {
    // Initialize atomic flags for cancellation and pausing
    std::atomic_bool is_canceled(false);
    std::atomic_bool is_paused(false);

    // Create a robot with specific parameters
    robots::Robots robot(1, "Medium", 100, 100, "None", "Idle", 0, robots::Robots::robotFunction::SCRUB, 0, 0);

    // Create a room task with a specified size
    tasks::RoomTask room_task(tasks::RoomTask::RoomSize::MEDIUM);

    // Log initial battery and water levels of the robot
    spdlog::info("Initial battery level: {}%, Initial water level: {}%", robot.get_battery_level(), robot.get_water_level());

    // Call the task function to simulate the task and log progress
    int result = task(robot, room_task, is_canceled, is_paused);

    // Log the final battery and water levels of the robot after the task
    spdlog::info("After task - Battery level: {}%, Water level: {}%", robot.get_battery_level(), robot.get_water_level());

    // Log the result of the task for confirmation
    spdlog::info("Final task result: {}", result);

    return 0;
}
