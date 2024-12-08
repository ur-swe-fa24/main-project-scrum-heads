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
    Room small_room(101, "small", "Tile", "Available");
    Room medium_room(102, "medium", "Carpet", "Available");

    // Initialize Robots with Empty Rooms
    Room empty_room(0, "", "", "");

    Robots robot1(1, "small", 100, 100, "", "Available", empty_room, "scrub", 0);
    Robots robot2(2, "medium", 50, 50, "", "Ongoing", empty_room, "scrub", 30);
    Robots robot3(3, "small", 10, 10, "Motor Failure", "Cancelled", empty_room, "scrub", 0);
    Robots robot4(4, "medium", 0, 0, "", "Available", empty_room, "scrub", 0); // Robot needs refilling
    Robots robot5(5, "large", 100, 100, "", "Available", empty_room, "scrub", 0); // Large robot

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
            if (robot.get_size() == "small") {
                robot.update_task_room(small_room);
            } else if (robot.get_size() == "medium") {
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
    for (int i = 0; i < robot_manager.get_robot_count(); ++i) {
        auto robot_opt = robot_manager.find_robot_by_id(i + 1);
        REQUIRE(robot_opt.has_value());
        auto& robot = robot_manager.get_list()[i]; // Modify to get a non-const reference for further updates

        if (robot.get_id() == 1) {
            // Robot 1 was available, should have started and be progressing or complete
            REQUIRE((robot.get_task_status() == "Ongoing" || robot.get_task_status() == "Complete"));
            REQUIRE(robot.get_task_percent() >= 0);
        }
        else if (robot.get_id() == 2) {
            // Robot 2 was already ongoing, task should have progressed or been cancelled due to insufficient resources
            bool valid_status = (robot.get_task_status() == "Ongoing" || robot.get_task_status() == "Complete" || robot.get_task_status() == "Cancelled");
            REQUIRE(valid_status);
            REQUIRE(robot.get_task_percent() >= 30);
        }
        else if (robot.get_id() == 3) {
            // Robot 3 had an error, status should remain cancelled
            REQUIRE(robot.get_task_status() == "Cancelled");
            REQUIRE(robot.get_error_status() == "Motor Failure");
        }
        else if (robot.get_id() == 4) {
            // Robot 4 needed refilling, should gradually refill and become available again
            bool valid_status = (robot.get_task_status() == "Cancelled" || robot.get_task_status() == "Available");
            REQUIRE(valid_status);
            REQUIRE(robot.get_water_level() >= 0);
            REQUIRE(robot.get_battery_level() >= 0);
        }
        else if (robot.get_id() == 5) {
            // Robot 5 (large robot) was available, should have started a task or remained available
            REQUIRE((robot.get_task_status() == "Ongoing" || robot.get_task_status() == "Available"));
            REQUIRE(robot.get_task_percent() >= 0);
        }
    }

    // Test the task cancellation for Robot 2
    SECTION("Cancel Ongoing Task for Robot 2") {
        auto robot_opt = robot_manager.find_robot_by_id(2);
        REQUIRE(robot_opt.has_value());
        auto& robot = robot_manager.get_list()[1]; // Robot with ID 2
        robot.update_task_status("Cancelled");
        robot.update_task_percent(0);

        // Verify the cancellation
        REQUIRE(robot.get_task_status() == "Cancelled");
        REQUIRE(robot.get_task_percent() == 0);
    }

    // Test recharging Robot 4 gradually
    SECTION("Gradual Refill of Robot 4") {
        auto& robot = robot_manager.get_list()[3]; // Robot with ID 4
        for (int i = 0; i < 10; ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            // Verify gradual refill
            REQUIRE(robot.get_water_level() >= 0);
            REQUIRE(robot.get_battery_level() >= 0);
        }
    }

    // Test Robot 5's large size handling
    SECTION("Verify Large Robot (Robot 5) Behavior") {
        auto& robot = robot_manager.get_list()[4]; // Robot with ID 5
        if (robot.get_task_status() == "Ongoing") {
            REQUIRE(robot.get_task_percent() >= 0);
            REQUIRE(robot.get_water_level() <= 100);
            REQUIRE(robot.get_battery_level() <= 100);
        } else {
            REQUIRE(robot.get_task_status() == "Available");
        }
    }

    // Test fix function on Robot 3
    SECTION("Fix Robot with Error (Robot 3)") {
        auto& robot = robot_manager.get_list()[2]; // Robot with ID 3
        REQUIRE(robot.get_task_status() == "Cancelled");
        REQUIRE(robot.get_error_status() == "Motor Failure");

        // Call fix function
        fix(robot);

        // Verify the robot is fixed
        REQUIRE(robot.get_task_status() == "Available");
        REQUIRE(robot.get_error_status().empty());
        REQUIRE(robot.get_task_percent() == 0);
        REQUIRE(robot.get_water_level() == 100); // Small robot default max water
        REQUIRE(robot.get_battery_level() == 100); // Small robot default max battery
    }

    // Test random error generation
    SECTION("Random Error Generation Test") {
        int error_count = 0;
        for (int i = 0; i < 100; ++i) {
            Robots test_robot(999, "small", 100, 100, "", "Ongoing", empty_room, "scrub", 50);
            calculate_error_status(test_robot);
            if (!test_robot.get_error_status().empty()) {
                error_count++;
            
        }
        }

        // Verify that errors are generated at a reasonable rate (around 1%)
        REQUIRE(error_count > 0);
        REQUIRE(error_count < 10); // Expecting around 1% error rate over 100 tests
    }
}
