#include "robot_loop_lib.hpp"
#include "spdlog/spdlog.h"
#include <random>
#include <thread>
#include <chrono>

int check_robot(std::string room_size, int water_level, int battery_level) {

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

}

int do_task(robots::Robots& robot, std ::string room_size) {
    bool cancel = False;
    bool error_status = true;
    int task_counter = 0;

    //the duration of time for each 10% of task for different size of room
    int task_duration = room_task.calculate_task_duration(room_size);

    //get water level and battery level
    int wlevel = robot.get_water_level();
    int blevel = robot.get_battery_level();

    //check if the water and battery levels are enough for this task
    int check_levels;
    check_levels = check_robot(room_size, wlevel, blevel);
    if (check_levels == false) {
        robot.update_task_status("canceled");
        return 0; //exit the program if  water and battery levels are not enough for this task
    }

    //the amount of battery & water consume for every 10% of task for different size of room
    int resource_usage = room_task.get_resource_usage();

    while (cancel = False & task_counter < 100) {
        //Check if complete
        if (task_counter >= 100) {
            robot.update_task_status() = "complete";
            break;
        }

        // Check if error
        if (error_status == true) {
            robot.update_error_status() = "ERROR!"
            break;
        }

        //Only adding 10% every loop
        task_counter += 10;
        robot.update_task_percent(task_counter);

        //water and battery used for each 10% of the task depends on room size.
        wlevel -= resource_usage;
        blevel -= resource_usage;

        // sleep for 1 second
        std::this_thread::sleep_for(std::chrono::seconds(1));

    }
    
    return 0;
}

// takes a list of robots
int robot_charge(std::vector<robots::Robots>& robot_list) {
    for (auto& robot : robot_list) {
        std::string size = robot.get_size()
        if (size  == "small") {
            int battery_max = 100;
            int water_max = 100;
        }
        else if (size  == "medium") {
            int battery_max = 120;
            int water_max = 120;
        }
        else {
            int battery_max = 140;
            int water_max = 140;
        }
        int water = robot.get_water_level();
        int battery = robot.get_battery_level();
        while (water < water_max || battery < battery_max) {
            if (water < water_max) {
                water += 1;
                robot.update_water_level(water);
            }
            if (battery < battery_max) {
                battery += 1;
                robot.update_battery_level(battery);
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    return 0;
}