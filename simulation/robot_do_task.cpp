#include "robot_do_task.hpp"
#include "spdlog/spdlog.h"
#include <random>
#include <thread>
#include <chrono>
#include <vector> 

namespace robot_tasks {

bool check_robot(const std::string& room_size, int water_level, int battery_level) {

    // Pre-check conditions based on water and battery levels and room size
    if ((battery_level < 10 || water_level < 10) &&
        (room_size == "small" || 
         room_size == "medium" || 
         room_size == "large")) {
        return false;
    }

    if ((battery_level < 40 || water_level < 40) &&
        (room_size == "medium" || 
         room_size == "large")) {
        return false;
    }

    if ((battery_level < 90 || water_level < 90) &&
        (room_size == "large")) {
        return false;
    }
    return true;
}

int do_task(robots::Robots& robot, const std::string& room_size) {
    bool error_status;
    int task_counter = 0;

    //the duration of time for each 10% of task for different size of room
    int task_duration = tasks::RoomTask::calculate_task_duration(room_size);

    //get water level and battery level
    int wlevel = robot.get_water_level();
    int blevel = robot.get_battery_level();

    //check if the water and battery levels are enough for this task
    bool check_levels = check_robot(room_size, wlevel, blevel);
    if (!check_levels) {
        robot.update_task_status("canceled");
        return 0; //exit the program if  water and battery levels are not enough for this task
    }

    //the amount of battery & water consume for every 10% of task for different size of room
    int resource_usage = tasks::RoomTask::get_resource_usage(room_size);

    while (task_counter < 100) {

        // Check if error
        if (error_status == true) {
            robot.update_error_status("ERROR!");
            return 0;
        }

        // Check if cancel
        if (robot.get_task_status() == "cancel") {
            return 0;
        }

        //Only adding 10% every loop
        task_counter += 10;
        robot.update_task_percent(task_counter);

        //water and battery used for each 10% of the task depends on room size.
        wlevel -= resource_usage;
        blevel -= resource_usage;

        // Update robot attributes
        robot.update_water_level(wlevel);
        robot.update_battery_level(blevel);

        // sleep for 1 second
        std::this_thread::sleep_for(std::chrono::seconds(1));

    }

    //complete!
    robot.update_task_status("complete");
    return 0;
}

// takes a list of robots
int robot_charge(std::vector<robots::Robots>& robot_list) {
    // Helper function to charge a single robot
    auto charge_robot = [](robots::Robots& robot) {
        std::string size = robot.get_size();
        int battery_max, water_max;

        // Determine max levels based on robot size
        if (size == "small") {
            battery_max = 100;
            water_max = 100;
        } else if (size == "medium") {
            battery_max = 120;
            water_max = 120;
        } else {
            battery_max = 140;
            water_max = 140;
        }

        int water = robot.get_water_level();
        int battery = robot.get_battery_level();

        // Charge the robot
        while (water < water_max || battery < battery_max) {
            if (water < water_max) {
                water += 1;
                robot.update_water_level(water);
            }
            if (battery < battery_max) {
                battery += 1;
                robot.update_battery_level(battery);
            }
            std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate charging time
        }
    };

    // Create a vector to store threads
    std::vector<std::thread> threads;

    // Start a thread for each robot
    for (auto& robot : robot_list) {
        threads.emplace_back(charge_robot, std::ref(robot));
    }

    // Join all threads to ensure completion
    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
}