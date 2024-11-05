#include "robot_loop_lib.hpp"
#include "spdlog/spdlog.h"
#include <random>
#include <thread>
#include <chrono>

std::string event_string(Event event) {
    switch (event) {
        case Event::START: return "start";
        case Event::STOP: return "stop";
        case Event::QUIT: return "quit";
        case Event::CONTINUE: return "continue";
        default: return "?";
    }
}

std::string error_string(ErrorType error) {
    switch (error) {
        case ErrorType::OVERHEAT: return "Overheat";
        case ErrorType::LOW_BATTERY: return "Low Battery";
        case ErrorType::MOTOR_FAILURE: return "Motor Failure";
        case ErrorType::SENSOR_FAILURE: return "Sensor Failure";
        case ErrorType::SOFTWARE_CRASH: return "Software Crash";
        default: return "Unknown Error";
    }
}

int task(robots::Robots& robot, tasks::RoomTask& room_task, std::atomic_bool& is_canceled, std::atomic_bool& is_paused, int task_length) {
    spdlog::info("Robot started the task!");

    std::mt19937_64 mt{std::random_device{}()};
    std::uniform_real_distribution<double> error_chance(0.0, 100.0);
    std::uniform_int_distribution<int> error_type_dist(0, 4);

    int task_counter = 0;
    int progress_increment = task_length / 10;
    int resource_usage = room_task.get_resource_usage();

    while (!is_canceled && task_counter < task_length) {
        if (is_paused) {
            spdlog::info("Task paused at progress: {}%", (task_counter * 100) / task_length);
            while (is_paused && !is_canceled) {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
            if (is_canceled) {
                spdlog::warn("Task canceled during pause!");
                break;
            }
            spdlog::info("Task resumed.");
        }

        if (error_chance(mt) < 3.0) {
            ErrorType error = static_cast<ErrorType>(error_type_dist(mt));
            spdlog::error("Task encountered an error: {}", error_string(error));
            is_canceled = true;
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        task_counter += progress_increment;

        // Calculate and log progress only at each 10% increment
        int progress = (task_counter * 100) / task_length;
        if (progress % 10 == 0) { // Only log when progress is 10, 20, 30, etc.
            spdlog::info("Task progress: {}%", progress);

            // Update battery and water levels based on resource usage
            robot.update_battery_level(robot.get_battery_level() - resource_usage);
            robot.update_water_level(robot.get_water_level() - resource_usage);

            // Log remaining battery and water levels at each 10% increment
            spdlog::info("Remaining battery level: {}%", robot.get_battery_level());
            spdlog::info("Remaining water level: {}%", robot.get_water_level());
        }

        if (progress >= 100) {
            spdlog::info("Task completed successfully with progress: 100%");
            break;
        }
    }

    if (is_canceled && task_counter < task_length) {
        spdlog::warn("Task stopped due to an error or cancellation.");
    }

    return task_counter;
}
