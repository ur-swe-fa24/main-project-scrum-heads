#include "robot_do_task.hpp"
#include "robot_manager.hpp"
#include <random>
#include <thread>
#include <chrono>
#include <atomic>
#include <vector>
#include <map>
#include <mutex>
#include <iostream>
#include <cassert>

namespace robot_tasks {

// Function to calculate task duration based on room size
int calculate_task_duration(const std::string& room_size) {
    if (room_size == "Small") return 2;
    if (room_size == "Medium") return 4;
    if (room_size == "Large") return 6;
    return 0;
}

// Function to calculate resource usage based on room size
int get_resource_usage(const std::string& room_size) {
    if (room_size == "Small") return 1;
    if (room_size == "Medium") return 4;
    if (room_size == "Large") return 9;
    return 0;
}

// Function to check if a robot has enough water and battery to finish its task
bool check_robot(robots::Robots& robot) {
    int water = robot.get_water_level();
    int battery = robot.get_battery_level();
    int percent = robot.get_task_percent();
    int left = (100 - percent) / 10; // Remaining task chunks
    int usage = get_resource_usage(robot.get_task_room().getRoomSize());
    return !(usage * left > battery || usage * left > water);
}

// Function to fix a robot's error status and reset it to be ready for tasks
void fix(robots::Robots& robot) {
    if (!robot.get_error_status().empty()) {
        robot.update_task_status("Available");
        robot.update_error_status("");
        robot.update_task_percent(0);
        robot.update_water_level(100);
        robot.update_battery_level(100);
    }
}

// Function to calculate the error status for a robot (randomly assigning errors)
void calculate_error_status(robots::Robots& robot) {
    // Define potential failure types (probability does not need to be specified here as 5% applies overall)
    struct Failure {
        std::string name;
    };

    std::vector<Failure> failures = {
        {"Overheat"},
        {"Motor Failure"},
        {"Sensor Failure"}
    };

    // Ensure the failures vector is not empty
    assert(!failures.empty() && "Failures vector should not be empty.");

    // Initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> error_chance(1, 100);

    // 5% chance for an error to occur
    if (error_chance(gen) <= 5) {
        // Randomly select one of the failure types
        std::uniform_int_distribution<> failure_selector(0, failures.size() - 1);
        const auto& selected_failure = failures[failure_selector(gen)];

        // Update the robot's status
        robot.update_error_status(selected_failure.name);
        robot.update_task_status("Cancelled");
    }
}


std::atomic<bool> is_canceled = true;
std::mutex robot_mutex;

// Function to execute the robot task loop
void execute(std::vector<robots::Robots>& robot_list_) {
    const auto loop_interval = std::chrono::milliseconds(10000);
    std::map<int, std::thread> active_tasks;

    while (is_canceled) {
        auto start_time = std::chrono::steady_clock::now();

        {
            std::lock_guard<std::mutex> lock(robot_mutex);
            for (robots::Robots& robot : robot_list_) {
                // std::cout << "Robot ID: " << robot.get_id() 
                // << ", Task Status: " << robot.get_task_status() 
                // << ", Error Status: " << robot.get_error_status()
                // << ", Task Percent: " << robot.get_task_percent() 
                // << ", Water Level: " << robot.get_water_level()
                // << ", Battery Level: " << robot.get_battery_level() << std::endl;


                if (robot.get_task_status() == "Cancelled" && robot.get_error_status().empty()) {
                    robot.update_task_status("Available");
                    robot.update_task_percent(0);
                    robot.get_task_room().setAvailability("Available");
                    continue;
                }

                if (robot.get_task_status() == "Complete" && robot.get_error_status().empty()) {
                    robot.update_task_status("Available");
                    robot.update_task_percent(0);
                    robot.get_task_room().setAvailability("Available");
                    // std::cout << "room Availability: " << robot.get_task_room().getAvailability()
                    // << "room Number: " << robot.get_task_room().getRoomNumber() << std::endl;
                    continue;
                }

                if (!check_robot(robot) && robot.get_task_status() == "Ongoing") {
                    robot.update_task_status("Cancelled");
                    continue;
                }
                
                if (robot.get_task_status() == "Available" && robot.get_error_status().empty() && robot.get_task_percent() == 0) {
                    int current_water = robot.get_water_level();
                    int current_battery = robot.get_battery_level();
                    int max_water, max_battery;

                    if (robot.get_size() == "Small") {
                        max_water = 100;
                        max_battery = 100;
                    } else if (robot.get_size() == "Medium") {
                        max_water = 120;
                        max_battery = 120;
                    } else {
                        max_water = 140;
                        max_battery = 140;
                    }  

                    // std::cout << "Refilling Robot ID: " << robot.get_id()
                    //     << ", Current Water: " << current_water
                    //     << ", Current Battery: " << current_battery
                    //     << ", Max Water: " << max_water
                    //     << ", Max Battery: " << max_battery << std::endl;

                    robot.update_water_level(std::min(current_water + 10, max_water));
                    robot.update_battery_level(std::min(current_battery + 10, max_battery));

                    // std::cout << "After Refill - Water: " << robot.get_water_level()
                    //         << ", Battery: " << robot.get_battery_level() << std::endl;


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
                                        calculate_error_status(r);
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

// Start the task execution loop in a separate thread
void start_execute_thread(std::vector<robots::Robots>& robot_list_) {
    execute_thread = std::thread([&]() { execute(robot_list_); });
}

// Stop the task execution loop and join the thread
void stop_execute_thread() {
    is_canceled = false;
    if (execute_thread.joinable()) {
        execute_thread.join();
    }
}

} // namespace robot_tasks
