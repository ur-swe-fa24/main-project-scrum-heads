#define CATCH_CONFIG_MAIN
#include "DataManager.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <wx/string.h>
#include <thread>
#include <chrono>
#include "spdlog/spdlog.h"

// Create a global instance of DataManager to ensure only one instance is used in all tests
DataManager data_manager;

TEST_CASE("DataManager Integration Test - Add, Delete, Retrieve Robot, and GetAllRobotInfo") {
    spdlog::info("Starting integration test for DataManager...");

    // Clear all robots from the database before starting
    data_manager.DeleteAllRobots();
    spdlog::info("Cleared all robots from the database.");

    // Step 1: Add a Robot and Validate ID Assignment
    RobotData new_robot;
    new_robot.robotSize = wxString("Large");
    new_robot.robotFunction = wxString("Vacuum");

    data_manager.AddRobot(new_robot);
    spdlog::info("Added new robot with size {} and function {}.", "Large", "Vacuum");

    // Verify that the robot has been added to the local vector
    auto& robots = data_manager.GetRobots();
    REQUIRE(robots.size() == 1);
    REQUIRE(robots.back().robotID == std::to_string(1));
    REQUIRE(robots.back().robotSize == "Large");
    REQUIRE(robots.back().robotFunction == "Vacuum");
    spdlog::info("Robot added successfully with ID: {}", robots.back().robotID);

    // Step 2: Test GetAllRobotInfo to Verify Retrieval of the Same Robot
    int robot_id = std::stoi(robots.back().robotID);
    robots::Robots retrieved_robot = data_manager.GetAllRobotInfo(robot_id);

    REQUIRE(retrieved_robot.get_id() == robot_id);
    REQUIRE(retrieved_robot.get_size() == "Large");
    REQUIRE(retrieved_robot.get_function_type() == "Vacuum");
    spdlog::info("Retrieved robot info matches added robot for ID: {}", robot_id);

    // Step 3: Delete the Robot and Verify it is Removed
    data_manager.DeleteRobot(robot_id);
    REQUIRE(data_manager.GetRobots().empty());
    spdlog::info("Robot with ID: {} deleted successfully.", robot_id);

    // Step 4: Add Another Robot and Validate Retrieval
    RobotData another_robot;
    another_robot.robotSize = wxString("Small");
    another_robot.robotFunction = wxString("Scrub");

    data_manager.AddRobot(another_robot);
    spdlog::info("Added new robot with size {} and function {}.", "Small", "Scrub");

    REQUIRE(data_manager.GetRobots().size() == 1);
    int added_robot_id = std::stoi(data_manager.GetRobots().front().robotID);
    robots::Robots retrieved_another_robot = data_manager.GetAllRobotInfo(added_robot_id);

    REQUIRE(retrieved_another_robot.get_id() == added_robot_id);
    REQUIRE(retrieved_another_robot.get_size() == "Small");
    REQUIRE(retrieved_another_robot.get_function_type() == "Scrub");
    spdlog::info("Robot added and retrieved successfully for ID: {}", added_robot_id);

    // Clean up after the tests by deleting all robots
    data_manager.DeleteAllRobots();
    REQUIRE(data_manager.GetRobots().empty());
    spdlog::info("Integration test completed. All robots deleted.");
}

TEST_CASE("DataManager Live Update Test - Update Task Progress and Live Sync with MongoDB") {
    spdlog::info("Starting live update test...");

    // Phase 1: Clear all robots
    data_manager.DeleteAllRobots();
    spdlog::info("Cleared all robots from the database.");

    // Phase 2: Add Robot
    RobotData new_robot;
    new_robot.robotSize = wxString("Medium");
    new_robot.robotFunction = wxString("Scrub");
    data_manager.AddRobot(new_robot);
    spdlog::info("Added new robot with size Medium and function Scrub.");

    // Start Update Thread
    data_manager.startUpdateThread();
    spdlog::info("Started the update thread.");

    // Fetch and Verify Initial Robot List
    auto& robot_list = data_manager.GetRobotManager().get_list();
    REQUIRE(!robot_list.empty());
    spdlog::info("Fetched robot list from RobotManager. Robot count: {}", robot_list.size());

    // Phase 3: Simulate Task Progress
    spdlog::info("Simulating task progress...");
    for (auto& robot : robot_list) {
        robot.update_task_status("Ongoing");
        robot.update_task_percent(50);
        robot.update_battery_level(70);
        robot.update_water_level(60);
    }

    // Phase 4: Let the Thread Run
    spdlog::info("Waiting for thread to process updates...");
    std::this_thread::sleep_for(std::chrono::seconds(3));

    // Phase 5: Verify Updated State
    spdlog::info("Verifying robot states...");
    for (const auto& robot : robot_list) {
        REQUIRE(robot.get_task_status() == "Ongoing");
        REQUIRE(robot.get_task_percent() == 50);
        REQUIRE(robot.get_battery_level() == 70);
        REQUIRE(robot.get_water_level() == 60);
        spdlog::info("Robot ID: {}, Status: {}, Percent: {}, Battery: {}, Water: {}",
                     robot.get_id(), robot.get_task_status(), robot.get_task_percent(),
                     robot.get_battery_level(), robot.get_water_level());
    }

    // Phase 6: Stop Update Thread and Clean Up
    data_manager.stopUpdateThread();
    spdlog::info("Stopped the update thread.");

    data_manager.DeleteAllRobots();
    REQUIRE(data_manager.GetRobots().empty());
    spdlog::info("Cleaned up all robots. Live update test completed.");
}
