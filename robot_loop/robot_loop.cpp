#include "robot_loop.hpp"
#include "robot_loop_lib.hpp"
#include "robot.hpp"
#include "room_task.hpp"
#include "spdlog/spdlog.h"
#include <future>
#include <random>
#include <iostream>
#include <atomic>

class View {
public:
    void prompt() {
        std::cout << "----" << std::endl;
        std::cout << "Enter your command (start, stop, quit, continue): ";
    }

    Event get_input() {
        std::string command;
        std::cin >> command;
        std::cout << "----" << std::endl;

        // Convert to lowercase to avoid case-sensitivity issues
        std::transform(command.begin(), command.end(), command.begin(), ::tolower);

        if (command == "start") return Event::START;
        if (command == "stop") return Event::STOP;
        if (command == "quit") return Event::QUIT;
        if (command == "continue") return Event::CONTINUE;

        spdlog::warn("Invalid command entered: '{}'", command); // Warn about invalid input
        return Event::UNKNOWN;
    }


    int get_battery_level() {
        int battery;
        std::cout << "Enter initial battery level (0-100): ";
        std::cin >> battery;
        return battery;
    }

    int get_water_level() {
        int water;
        std::cout << "Enter initial water level (0-100): ";
        std::cin >> water;
        return water;
    }

    tasks::RoomTask::RoomSize get_room_size() {
        int size_choice;
        std::cout << "Select room size (1 - Small, 2 - Medium, 3 - Large): ";
        std::cin >> size_choice;

        switch (size_choice) {
            case 1: return tasks::RoomTask::RoomSize::SMALL;
            case 2: return tasks::RoomTask::RoomSize::MEDIUM;
            case 3: return tasks::RoomTask::RoomSize::LARGE;
            default:
                std::cout << "Invalid choice. Defaulting to Medium size." << std::endl;
                return tasks::RoomTask::RoomSize::MEDIUM;
        }
    }
};

int main() {
    std::uniform_int_distribution<int> rand_int{100, 200};

    std::atomic_bool task_cancelled{false};
    std::atomic_bool task_paused{false};

    View ui{};
    spdlog::info("Event loop starting!");

    int battery_level = ui.get_battery_level();
    int water_level = ui.get_water_level();
    tasks::RoomTask::RoomSize room_size = ui.get_room_size();

    // Create robot and room task with selected attributes
    robots::Robots robot(1, "Medium", battery_level, water_level, "None", "Idle", 0, robots::Robots::robotFunction::SCRUB, 0, 0);
    tasks::RoomTask room_task(room_size);

    // Pre-check conditions based on water and battery levels and room size
    if ((battery_level < 10 || water_level < 10) &&
        (room_size == tasks::RoomTask::RoomSize::SMALL || 
         room_size == tasks::RoomTask::RoomSize::MEDIUM || 
         room_size == tasks::RoomTask::RoomSize::LARGE)) {
        spdlog::error("Cannot start task: water or battery level is below 10%");
        return 0; // Exit the program
    }

    if ((battery_level < 40 || water_level < 40) &&
        (room_size == tasks::RoomTask::RoomSize::MEDIUM || 
         room_size == tasks::RoomTask::RoomSize::LARGE)) {
        spdlog::error("Cannot start task: water or battery level is below 40% for medium or large rooms");
        return 0; // Exit the program
    }

    if ((battery_level < 90 || water_level < 90) &&
        (room_size == tasks::RoomTask::RoomSize::LARGE)) {
        spdlog::error("Cannot start task: water or battery level is below 40% for medium or large rooms");
        return 0; // Exit the program
    }

    if (battery_level == 100 && water_level == 100 &&
        (room_size == tasks::RoomTask::RoomSize::SMALL || 
         room_size == tasks::RoomTask::RoomSize::MEDIUM || 
         room_size == tasks::RoomTask::RoomSize::LARGE)) {
        spdlog::info("Starting task with full water and battery levels.");
    }

    std::future<int> task_result;
    bool is_task_started = false;

    while (true) {
        if (is_task_started && task_result.wait_for(std::chrono::milliseconds(1)) == std::future_status::ready) {
            spdlog::info("Task completed, exiting loop.");
            break;
        }
        ui.prompt();
        auto input_event = ui.get_input();
        spdlog::info("User entered {}", event_string(input_event));

        if (input_event == Event::QUIT) {
            if (is_task_started) {
                task_cancelled = true;
                task_result.wait(); // Wait for the task to acknowledge cancellation
            }
            break;
        } else if (input_event == Event::START && !is_task_started) {
            task_cancelled = false;
            task_paused = false;
            int task_length = 100;
            task_result = std::async(
                std::launch::async,
                task,
                std::ref(robot),
                std::ref(room_task),
                std::ref(task_cancelled),
                std::ref(task_paused),
                task_length
            );
            is_task_started = true;
        } else if (input_event == Event::STOP && is_task_started) {
            task_paused = true;
            spdlog::warn("Task paused by user.");
        } else if (input_event == Event::CONTINUE && is_task_started && task_paused) {
            task_paused = false;
            spdlog::info("Task resumed by user.");
        }

        // Check if task is completed
        if (is_task_started && task_result.wait_for(std::chrono::milliseconds(1)) == std::future_status::ready) {
            spdlog::info("Task completed, exiting loop.");
            break;
        }
    }

    return 0;
}
