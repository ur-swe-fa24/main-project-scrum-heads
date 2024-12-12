#include "robot_manager.hpp"
#include "robot_do_task.hpp"
#include <catch2/catch_all.hpp>
#include <thread>
#include <chrono>
#include <iostream>

using namespace robots;
using namespace robot_tasks;

TEST_CASE("RobotManager Comprehensive Test") {
    // Setup Real Rooms
    Room small_room(101, "Small", "Tile", "Available");
    Room medium_room(102, "Medium", "Carpet", "Available");

    // Initialize Robots with Empty Rooms
    Room empty_room(0, "", "", "");

    Robots robot1(1, "Small", 100, 100, "", "Available", empty_room, "Scrub", 0);
    Robots robot2(2, "Medium", 50, 50, "", "Ongoing", empty_room, "Scrub", 30);
    Robots robot3(3, "Small", 10, 10, "Motor Failure", "Cancelled", empty_room, "Scrub", 0);
    Robots robot4(4, "Medium", 0, 0, "", "Available", empty_room, "Scrub", 0); // Robot needs refilling
    Robots robot5(5, "Large", 100, 100, "", "Available", empty_room, "Scrub", 0); // Large robot

    // Initialize RobotManager and add robots
    RobotManager robot_manager;
    robot_manager.add_robot(robot1);
    robot_manager.add_robot(robot2);
    robot_manager.add_robot(robot3);
    robot_manager.add_robot(robot4);
    robot_manager.add_robot(robot5);

    // Assign tasks to available robots
    for (auto& robot : robot_manager.get_list()) {
        if (robot.get_task_status() == "Available" && robot.get_water_level() == 100 && robot.get_battery_level() == 100) {
            robot.update_task_status("Ongoing");

            // Assign the real room based on robot size
            if (robot.get_size() == "Small") {
                robot.update_task_room(small_room);
            } else if (robot.get_size() == "Medium") {
                robot.update_task_room(medium_room);
            }

            std::cout << "Robot ID: " << robot.get_id() << " assigned a new task and status set to Ongoing." << std::endl;
        } else {
            std::cout << "Robot ID: " << robot.get_id() << " did not meet criteria for task assignment." << std::endl;
        }
    }

    // Start the task execution loop in a separate thread
    start_execute_thread(robot_manager.get_list());

    // Allow some time for tasks to progress
    std::this_thread::sleep_for(std::chrono::seconds(10));

    // Stop the task execution loop
    stop_execute_thread();

    // Verify the outcomes for each robot
    for (int robot_id = 1; robot_id <= robot_manager.get_robot_count(); ++robot_id) {
        robots::Robots& robot = robot_manager.find_robot_by_id(robot_id);

        if (robot.get_id() == 1) {
            REQUIRE((robot.get_task_status() == "Ongoing" || robot.get_task_status() == "Complete"));
            REQUIRE(robot.get_task_percent() >= 0);
        } else if (robot.get_id() == 2) {
            REQUIRE((robot.get_task_status() == "Ongoing" || robot.get_task_status() == "Complete" || robot.get_task_status() == "Cancelled"));
            REQUIRE(robot.get_task_percent() >= 30);
        } else if (robot.get_id() == 3) {
            REQUIRE(robot.get_task_status() == "Cancelled");
            REQUIRE(robot.get_error_status() == "Motor Failure");
        } else if (robot.get_id() == 4) {
            REQUIRE((robot.get_task_status() == "Cancelled" || robot.get_task_status() == "Available"));
            REQUIRE(robot.get_water_level() >= 0);
            REQUIRE(robot.get_battery_level() >= 0);
        } else if (robot.get_id() == 5) {
            REQUIRE((robot.get_task_status() == "Ongoing" || robot.get_task_status() == "Available"));
            REQUIRE(robot.get_task_percent() >= 0);
        }
    }

    SECTION("Cancel Ongoing Task for Robot 2") {
        robots::Robots& robot = robot_manager.find_robot_by_id(2);
        robot.update_task_status("Cancelled");
        robot.update_task_percent(0);

        REQUIRE(robot.get_task_status() == "Cancelled");
        REQUIRE(robot.get_task_percent() == 0);
    }

    SECTION("Gradual Refill of Robot 4") {
        robots::Robots& robot = robot_manager.find_robot_by_id(4);
        for (int i = 0; i < 10; ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            REQUIRE(robot.get_water_level() >= 0);
            REQUIRE(robot.get_battery_level() >= 0);
        }
    }

    SECTION("Verify Large Robot (Robot 5) Behavior") {
        robots::Robots& robot = robot_manager.find_robot_by_id(5);
        if (robot.get_task_status() == "Ongoing") {
            REQUIRE(robot.get_task_percent() >= 0);
            REQUIRE(robot.get_water_level() <= 100);
            REQUIRE(robot.get_battery_level() <= 100);
        } else {
            REQUIRE(robot.get_task_status() == "Available");
        }
    }

    SECTION("Fix Robot with Error (Robot 3)") {
        robots::Robots& robot = robot_manager.find_robot_by_id(3);
        REQUIRE(robot.get_task_status() == "Cancelled");
        REQUIRE(robot.get_error_status() == "Motor Failure");

        fix(robot);

        REQUIRE(robot.get_task_status() == "Available");
        REQUIRE(robot.get_error_status().empty());
        REQUIRE(robot.get_task_percent() == 0);
        REQUIRE(robot.get_water_level() == 100);
        REQUIRE(robot.get_battery_level() == 100);
    }

    SECTION("Random Error Generation Test") {
        int error_count = 0;
        for (int i = 0; i < 100; ++i) {
            Robots test_robot(999, "Small", 100, 100, "", "Ongoing", empty_room, "Scrub", 50);
            calculate_error_status(test_robot);
            if (!test_robot.get_error_status().empty()) {
                error_count++;
            }
        }
        REQUIRE(error_count > 0);
        REQUIRE(error_count < 10);
    }
}
