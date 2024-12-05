#include "robot_manager.hpp"
#include "robot_do_task.hpp"
#include <catch2/catch_all.hpp>
#include <thread>
#include <chrono>
#include <iostream> // Added for debugging output

using namespace robots;
using namespace robot_tasks;

TEST_CASE("RobotManager Comprehensive Test") {
    // Setup Room and Robots
    Room small_room(101, "small", "Tile", "Available");
    Room medium_room(102, "medium", "Carpet", "Available");
    
    Robots robot1(1, "small", 100, 100, "", "Available", small_room, "scrub", 0);
    Robots robot2(2, "medium", 50, 50, "", "Ongoing", medium_room, "scrub", 30);
    Robots robot3(3, "small", 10, 10, "Motor Failure", "Cancelled", small_room, "scrub", 0);
    Robots robot4(4, "medium", 0, 100, "", "Available", medium_room, "scrub", 0); // Robot needs refilling

    // Initialize RobotManager and add robots
    RobotManager robot_manager;
    robot_manager.add_robot(robot1);
    robot_manager.add_robot(robot2);
    robot_manager.add_robot(robot3);
    robot_manager.add_robot(robot4);

    // Assign tasks to available robots
    for (auto& robot : robot_manager.get_list()) {
        if (robot.get_task_status() == "Available" && robot.get_water_level() == 100 && robot.get_battery_level() == 100) {
            robot.update_task_status("Ongoing");
            if (robot.get_task_room().getRoomSize() == "small") {
                robot.update_task_room(small_room);
            } else if (robot.get_task_room().getRoomSize() == "medium") {
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
            if (robot.get_water_level() == 100) {
                REQUIRE(robot.get_task_status() == "Available");
            } else {
                bool valid_status = (robot.get_task_status() == "Cancelled" || robot.get_task_status() == "Available");
                REQUIRE(valid_status);
            }
            REQUIRE(robot.get_water_level() <= 100);
            REQUIRE(robot.get_battery_level() == 100);
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
            REQUIRE(robot.get_water_level() <= 100);
            REQUIRE(robot.get_battery_level() == 100);
            if (robot.get_water_level() == 100) {
                REQUIRE(robot.get_task_status() == "Available");
            }
        }
    }
}
