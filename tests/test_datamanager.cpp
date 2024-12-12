#define CATCH_CONFIG_MAIN
#include "DataManager.h"
#include "robot_manager.hpp"
#include "robot_do_task.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <thread>
#include <chrono>
#include <spdlog/spdlog.h>

// Create a global instance of DataManager to ensure only one instance is used in all tests
DataManager data_manager;

TEST_CASE("DataManager Integration Test - Add, Delete, Retrieve Robot, and GetAllRobotInfo") {
    // spdlog::info("Starting integration test for DataManager...");

    // Clear all robots from the database before starting
    data_manager.DeleteAllRobots();
    // spdlog::info("Cleared all robots from the database.");

    // Step 1: Add a Robot and Validate ID Assignment
    RobotData new_robot;
    new_robot.robotSize = wxString("Large");
    new_robot.robotFunction = wxString("Vacuum");

    data_manager.AddRobot(new_robot);
    // spdlog::info("Added new robot with size {} and function {}.", "Large", "Vacuum");

    // Verify that the robot has been added to the local vector
    auto& robots = data_manager.GetRobots();
    REQUIRE(robots.size() == 1);
    REQUIRE(robots.back().robotID == std::to_string(1));
    REQUIRE(robots.back().robotSize == "Large");
    REQUIRE(robots.back().robotFunction == "Vacuum");
    // spdlog::info("Robot added successfully with ID: {}", robots.back().robotID);

    // Step 2: Test GetAllRobotInfo to Verify Retrieval of the Same Robot
    int robot_id = std::stoi(robots.back().robotID);
    robots::Robots retrieved_robot = data_manager.GetAllRobotInfo(robot_id);

    REQUIRE(retrieved_robot.get_id() == robot_id);
    REQUIRE(retrieved_robot.get_size() == "Large");
    REQUIRE(retrieved_robot.get_function_type() == "Vacuum");
    // spdlog::info("Retrieved robot info matches added robot for ID: {}", robot_id);

    // Step 3: Delete the Robot and Verify it is Removed
    data_manager.DeleteRobot(robot_id);
    REQUIRE(data_manager.GetRobots().empty());
    // spdlog::info("Robot with ID: {} deleted successfully.", robot_id);

    // Step 4: Add Another Robot and Validate Retrieval
    RobotData another_robot;
    another_robot.robotSize = wxString("Small");
    another_robot.robotFunction = wxString("Scrub");

    data_manager.AddRobot(another_robot);
    // spdlog::info("Added new robot with size {} and function {}.", "Small", "Scrub");

    REQUIRE(data_manager.GetRobots().size() == 1);
    int added_robot_id = std::stoi(data_manager.GetRobots().front().robotID);
    robots::Robots retrieved_another_robot = data_manager.GetAllRobotInfo(added_robot_id);

    REQUIRE(retrieved_another_robot.get_id() == added_robot_id);
    REQUIRE(retrieved_another_robot.get_size() == "Small");
    REQUIRE(retrieved_another_robot.get_function_type() == "Scrub");
    // spdlog::info("Robot added and retrieved successfully for ID: {}", added_robot_id);

    // Clean up after the tests by deleting all robots
    data_manager.DeleteAllRobots();
    REQUIRE(data_manager.GetRobots().empty());
    // spdlog::info("Integration test completed. All robots deleted.");
}

TEST_CASE("DataManager - Start Robot Task Execution Thread") {
    // spdlog::info("Starting DataManager thread and task execution test...");

    data_manager.DeleteAllRobots(); // Clear any existing data
    // spdlog::info("Cleared all robots from the database.");

    // Step 2: Add a robot and a task
    RobotData new_robot;
    new_robot.robotSize = wxString("Medium");
    new_robot.robotFunction = wxString("Scrub");
    data_manager.AddRobot(new_robot);

    TaskData new_task;
    new_task.taskRoom = wxString("102"); // Example room number
    new_task.taskRobot = new_robot;
    data_manager.AddTask(new_task);

    // spdlog::info("Added a new robot and assigned a task.");

    // Step 3: Start the DataManager update thread
    data_manager.startUpdateThread();

    // Step 4: Let the thread run for a short period
    // spdlog::info("Allowing the thread to run for task execution...");
    std::this_thread::sleep_for(std::chrono::seconds(5));

    // Step 5: Fetch updated robot information
    auto& robot_manager = data_manager.GetRobotManager();
    auto robot_list = robot_manager.get_list();

    REQUIRE(!robot_list.empty()); // Ensure there is at least one robot

    // Step 6: Verify the task progress and robot state
    for (const auto& robot : robot_list) {
        // spdlog::info("Verifying robot ID: {}", robot.get_id());
        if (robot.get_task_status() == "Ongoing") {
            REQUIRE(robot.get_task_percent() > 0); // Task progress should have started
            REQUIRE(robot.get_battery_level() <= 100); // Battery level should decrease
            REQUIRE(robot.get_water_level() <= 100); // Water level should decrease
            // spdlog::info("Task progress: {}%, Battery: {}, Water: {}",
                        //  robot.get_task_percent(),
                        //  robot.get_battery_level(),
                        //  robot.get_water_level());
        } else if (robot.get_task_status() == "Complete") {
            REQUIRE(robot.get_task_percent() == 100); // Task should be fully completed
            // spdlog::info("Task for Robot ID: {} is complete.", robot.get_id());
        }
    }

    // Step 7: Stop the thread and clean up
    // spdlog::info("Stopping the update thread...");
    data_manager.stopUpdateThread();
    data_manager.DeleteAllRobots();
    REQUIRE(data_manager.GetRobots().empty());
    // spdlog::info("All robots removed. Test complete.");
}