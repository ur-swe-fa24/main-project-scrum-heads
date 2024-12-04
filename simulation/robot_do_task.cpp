#include "robot_do_task.hpp"
#include "robot_manager.hpp"
#include "spdlog/spdlog.h"
#include <random>
#include <thread>
#include <chrono>
#include <atomic>
#include <vector> 

namespace robot_tasks {

int calculate_task_duration(const std::string& room_size) {
    if (room_size == "small") return 2;
    if (room_size == "medium") return 4;
    if (room_size == "large") return 6;
    return 0;
}

int get_resource_usage(const std::string& room_size) {
    if (room_size == "small") return 1;
    if (room_size == "medium") return 4;
    if (room_size == "large") return 9;
    return 0;
}

//check if the robot have enough water and battery to finish this task
bool check_robot(robots::Robots& robot) {
    int water = robot.get_water_level();
    int battery = robot.get_battery_level();
    int percent = robot.get_task_percent();
    int left = (100 - percent) / 10; // Remaining task chunks
    int usage = get_resource_usage(robot.get_task_room().getRoomSize());
    return !(usage * left > battery || usage * left > water);
}

void fix(robots::Robots& robot) {
    if (!robot.get_error_status().empty()) {
        robot.update_task_status("Available");
        robot.update_error_status("");
        robot.update_task_percent(0);
        robot.update_water_level(100);
        robot.update_battery_level(100);
    }
}

void calculate_error_status(robots::Robots& robot) {
    std::vector<std::string> failures = {"Overheat", "Motor Failure", "Sensor Failure"};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> error_chance(1, 100);
    if (error_chance(gen) == 1) {
        std::uniform_int_distribution<> dist(0, failures.size() - 1);
        robot.update_error_status(failures[dist(gen)]);
        robot.update_task_status("Cancelled");
    }
}

std::atomic<bool> is_canceled = true;
std::mutex robot_mutex;

void execute() {
    const auto loop_interval = std::chrono::milliseconds(100);
    std::map<int, std::thread> active_tasks;

    while (is_canceled) {
        auto start_time = std::chrono::steady_clock::now();

        {
            std::lock_guard<std::mutex> lock(robot_mutex);
            for (robots::Robots& robot : robot_list_) {
                if (robot.get_task_status() == "Cancelled" && robot.get_error_status() == "") {
                    robot.update_task_status("Available");
                    robot.update_task_percent(0);
                    continue;
                }
                if (!check_robot(robot)) {
                    robot.update_task_status("Cancelled");
                    continue;
                }
                if (robot.get_task_percent() < 100 && robot.get_task_status() == "Ongoing" && robot.get_error_status().empty()) {
                    if (active_tasks.find(robot.get_id()) == active_tasks.end()) {
                        int robot_id = robot.get_id();
                        std::string room_size = robot.get_task_room().getRoomSize();
                        int resource_usage = get_resource_usage(room_size);
                        int task_duration = calculate_task_duration(room_size);

                        active_tasks[robot_id] = std::thread([&, robot_id, room_size, resource_usage, task_duration]() {
                            std::this_thread::sleep_for(std::chrono::seconds(task_duration));
                            {
                                std::lock_guard<std::mutex> lock(robot_mutex);
                                for (auto& r : robot_list_) {
                                    if (r.get_id() == robot_id) {
                                        r.update_water_level(r.get_water_level() - resource_usage);
                                        r.update_battery_level(r.get_battery_level() - resource_usage);
                                        r.update_task_percent(r.get_task_percent() + 10);
                                        if (r.get_task_percent() >= 100) {
                                            r.update_task_status("Complete");
                                        }
                                        break;
                                    }
                                }
                            }
                        });
                    }
                    continue;
                }
                if (robot.get_task_percent() == 100 && robot.get_task_status() == "Ongoing") {
                    robot.update_task_status("Complete");
                }
            }
        }

        for (auto it = active_tasks.begin(); it != active_tasks.end();) {
            if (it->second.joinable()) {
                it->second.join();
            }
            it = active_tasks.erase(it);
        }

        auto elapsed_time = std::chrono::steady_clock::now() - start_time;
        if (elapsed_time < loop_interval) {
            std::this_thread::sleep_for(loop_interval - elapsed_time);
        }
    }

    for (auto& [id, task] : active_tasks) {
        if (task.joinable()) {
            task.join();
        }
    }
}

std::thread execute_thread;

void start_execute_thread() {
    execute_thread = std::thread([]() { execute(); });
}

void stop_execute_thread() {
    is_canceled = false;
    if (execute_thread.joinable()) {
        execute_thread.join();
    }
}

} // namespace robot_tasks