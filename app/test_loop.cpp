#include "robot.hpp"
#include "room_task.hpp"
#include "spdlog/spdlog.h"

int main() {
    // Create a robot with full battery and water levels
    robots::Robots robot(1, "Medium", 100, 100, "None", "Idle", 0, robots::Robots::robotFunction::SCRUB, 0, 0);

    spdlog::info("Initial battery level: {}%, Initial water level: {}%",
                 robot.get_battery_level(), robot.get_water_level());

    // Assign a medium room task to the robot
    tasks::RoomTask medium_room_task(tasks::RoomTask::RoomSize::MEDIUM);

    // Perform the task
    medium_room_task.perform_task(robot);

    // Display the robot's battery and water levels after the task
    spdlog::info("After task - Battery level: {}%, Water level: {}%",
                 robot.get_battery_level(), robot.get_water_level());

    return 0;
}
