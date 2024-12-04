#include "RobotManager.hpp"
#include "robot_do_task.hpp"
#include <catch2/catch_all.hpp>
#include <thread>
#include <chrono>

using namespace robots;
using namespace robot_tasks;

TEST_CASE("Execute Function with RobotManager") {
    Room small_room(101, "small", "Tile", "Available");
    Robots robot1(5, "small", 100, 100, "", "Ongoing", small_room, "scrub", 0);
    Robots robot2(6, "small", 100, 100, "", "Ongoing", small_room, "scrub", 0);

    RobotManager robot_manager;
    robot_manager.add_robot(robot1);
    robot_manager.add_robot(robot2);

    SECTION("Tasks Progress and Complete with RobotManager") {
        // Start the execution thread
        start_execute_thread();

        // Allow some time for tasks to progress
        std::this_thread::sleep_for(std::chrono::seconds(1));

        // Stop the execution thread
        stop_execute_thread();

        // Verify the results
        for (int i = 0; i < robot_manager.get_robot_count(); ++i) {
            auto robot_opt = robot_manager.find_robot_by_id(i + 5); // IDs start from 5
            REQUIRE(robot_opt.has_value());
            const auto& robot = robot_opt.value();
            REQUIRE(robot.get_task_percent() == 100); // Task should be complete
            REQUIRE(robot.get_task_status() == "Complete");
        }
    }

    SECTION("Tasks Stop Gracefully with RobotManager") {
        // Start the execution thread
        start_execute_thread();

        // Allow partial progress
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        // Stop the execution thread
        stop_execute_thread();

        // Verify the results
        for (int i = 0; i < robot_manager.get_robot_count(); ++i) {
            auto robot_opt = robot_manager.find_robot_by_id(i + 5); // IDs start from 5
            REQUIRE(robot_opt.has_value());
            const auto& robot = robot_opt.value();
            REQUIRE(robot.get_task_percent() > 0);   // Task should have started
            REQUIRE(robot.get_task_percent() <= 100); // Task might not be complete
        }
    }

    SECTION("No Robots in RobotManager") {
        RobotManager empty_manager;

        start_execute_thread();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        stop_execute_thread();

        REQUIRE(empty_manager.get_robot_count() == 0);
    }

    SECTION("Robot with Insufficient Resources") {
        Room small_room(102, "small", "Tile", "Available");
        Robots insufficient_robot(7, "small", 5, 5, "", "Ongoing", small_room, "scrub", 0);

        robot_manager.add_robot(insufficient_robot);

        start_execute_thread();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        stop_execute_thread();

        auto robot_opt = robot_manager.find_robot_by_id(7);
        REQUIRE(robot_opt.has_value());
        const auto& robot = robot_opt.value();
        REQUIRE(robot.get_task_status() == "Cancelled");
        REQUIRE(robot.get_task_percent() == 0);
    }

    SECTION("Error During Task Execution") {
        Room small_room(103, "small", "Tile", "Available");
        Robots robot_with_error(8, "small", 100, 100, "", "Ongoing", small_room, "scrub", 0);

        robot_manager.add_robot(robot_with_error);

        start_execute_thread();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        stop_execute_thread();

        auto robot_opt = robot_manager.find_robot_by_id(8);
        REQUIRE(robot_opt.has_value());
        const auto& robot = robot_opt.value();

        if (!robot.get_error_status().empty()) {
            REQUIRE(robot.get_task_status() == "Cancelled");
            REQUIRE(robot.get_task_percent() < 100);
        }
    }

    SECTION("Multiple Robots with Mixed States") {
        Room small_room(104, "small", "Tile", "Available");
        Robots completed_robot(9, "small", 100, 100, "", "Complete", small_room, "scrub", 100);
        Robots ongoing_robot(10, "small", 100, 100, "", "Ongoing", small_room, "scrub", 50);
        Robots cancelled_robot(11, "small", 5, 5, "", "Cancelled", small_room, "scrub", 0);

        robot_manager.add_robot(completed_robot);
        robot_manager.add_robot(ongoing_robot);
        robot_manager.add_robot(cancelled_robot);

        start_execute_thread();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        stop_execute_thread();

        auto completed_opt = robot_manager.find_robot_by_id(9);
        auto ongoing_opt = robot_manager.find_robot_by_id(10);
        auto cancelled_opt = robot_manager.find_robot_by_id(11);

        REQUIRE(completed_opt.has_value());
        REQUIRE(completed_opt.value().get_task_percent() == 100);
        REQUIRE(completed_opt.value().get_task_status() == "Complete");

        REQUIRE(ongoing_opt.has_value());
        REQUIRE(ongoing_opt.value().get_task_percent() > 50);
        REQUIRE(ongoing_opt.value().get_task_percent() <= 100);

        REQUIRE(cancelled_opt.has_value());
        REQUIRE(cancelled_opt.value().get_task_status() == "Cancelled");
        REQUIRE(cancelled_opt.value().get_task_percent() == 0);
    }

    SECTION("Setup and Teardown") {
        stop_execute_thread(); // Ensure any previously running threads are stopped
        start_execute_thread(); // Start the execution thread for the current test
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        stop_execute_thread(); // Stop the thread after the test is done
    }

    SECTION("Timeout Mechanism") {
        auto timeout = std::chrono::seconds(2); // Set timeout duration
        auto start_time = std::chrono::steady_clock::now();

        start_execute_thread();
        while (std::chrono::steady_clock::now() - start_time < timeout) {
            // Allow execution to progress
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        stop_execute_thread();
    }


}
