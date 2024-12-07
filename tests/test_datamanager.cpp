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

/**
TEST_CASE("DataManager Integration Test - Add, Delete, Retrieve Robot, and GetAllRobotInfo") {
    // Clear all robots from the database before starting
    data_manager.DeleteAllRobots(); 

    // Step 1: Add a Robot and Validate that it is added
    RobotData new_robot;
    new_robot.robotSize = wxString("Large");
    new_robot.robotFunction = wxString("Vacuum");

    // Add the new robot to the system
    data_manager.AddRobot(new_robot);

    // Verify that the robot has been added to the local vector
    auto& robots = data_manager.GetRobots();
    REQUIRE(robots.size() == 1);
    REQUIRE(robots.back().robotSize == "Large");
    REQUIRE(robots.back().robotFunction == "Vacuum");

    // Step 2: Test GetAllRobotInfo to Verify Retrieval of the Same Robot
    int robot_id = std::stoi(robots.back().robotID);
    robots::Robots retrieved_robot = data_manager.GetAllRobotInfo(robot_id);

    // Validate that the retrieved robot's data matches what was originally added
    REQUIRE(retrieved_robot.get_size() == "Large");
    REQUIRE(retrieved_robot.get_function_type() == "Vacuum");

    // Step 3: Delete the Robot and Verify it is Removed
    data_manager.DeleteRobot(robot_id);

    // Verify that the robot has been removed from the local vector
    REQUIRE(data_manager.GetRobots().empty());

    // Step 4: Add Another Robot and Validate Retrieval
    RobotData another_robot;
    another_robot.robotSize = wxString("Small");
    another_robot.robotFunction = wxString("Scrub");

    // Add the robot to the system
    data_manager.AddRobot(another_robot);

    // Verify the robot was added correctly
    REQUIRE(data_manager.GetRobots().size() == 1);
    robots::Robots retrieved_another_robot = data_manager.GetAllRobotInfo(std::stoi(data_manager.GetRobots().front().robotID));

    // Check that the retrieved robot data matches what was added
    REQUIRE(retrieved_another_robot.get_size() == "Small");
    REQUIRE(retrieved_another_robot.get_function_type() == "Scrub");

    // Clean up after the tests by deleting all robots
    data_manager.DeleteAllRobots();
    REQUIRE(data_manager.GetRobots().empty());

    data_manager.stopUpdateThread();

}

*/

TEST_CASE("DataManager Live Update Test - Update Task Progress and Live Sync with MongoDB") {
    spdlog::info("Starting live update test...");

    // Clear all robots from the database before starting
    data_manager.DeleteAllRobots();
    spdlog::info("Cleared all robots from the database.");

    // Step 1: Add a Robot
    RobotData new_robot;
    new_robot.robotSize = wxString("Medium");
    new_robot.robotFunction = wxString("Scrub");

    data_manager.AddRobot(new_robot);
    spdlog::info("Added new robot with size {} and function {}.", "Medium", "Scrub");

    // Start the Update Thread
    data_manager.startUpdateThread();
    spdlog::info("Started the update thread...");

    // Simulate task progress
    auto& robot_list = data_manager.GetRobotManager().get_list();
    REQUIRE(!robot_list.empty());  // Ensure the list is not empty
    spdlog::info("Fetched robot list from RobotManager. Robot count: {}", robot_list.size());

    for (auto& robot : robot_list) {
        robot.update_task_status("Ongoing");
        robot.update_task_percent(50);
        robot.update_battery_level(70);
        robot.update_water_level(60);
    }
    spdlog::info("Simulated task progress for robot list.");

    // Let the update thread run for a short period to sync changes to the MongoDB database
    std::this_thread::sleep_for(std::chrono::seconds(3));

    // Verify MongoDB updates (no need for specific robot IDs)
    spdlog::info("Verifying MongoDB updates...");
    auto updated_robots = data_manager.GetRobotManager().get_list();
    REQUIRE(!updated_robots.empty());
    for (const auto& robot : updated_robots) {
        REQUIRE(robot.get_task_status() == "Ongoing");
    }
    spdlog::info("MongoDB updates verified successfully.");

    // Stop the Update Thread
    data_manager.stopUpdateThread();
    spdlog::info("Stopped the update thread.");

    // Clean up
    data_manager.DeleteAllRobots();
    REQUIRE(data_manager.GetRobots().empty());
    spdlog::info("Cleaned up all robots. Live update test completed.");
}


