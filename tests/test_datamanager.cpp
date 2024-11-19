#define CATCH_CONFIG_MAIN
#include "DataManager.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <wx/string.h>

// Create a global instance of DataManager to ensure only one instance is used in all tests
DataManager data_manager;

TEST_CASE("DataManager Integration Test - Add, Delete, Retrieve Robot, and GetAllRobotInfo") {
    // Step 1: Add a Robot and Validate ID Assignment
    RobotData new_robot;
    new_robot.robotSize = wxString("Large");
    new_robot.robotFunction = wxString("Vacuum");

    // Add the new robot to the system
    data_manager.AddRobot(new_robot);

    // Verify that the robot has been added to the local vector
    auto& robots = data_manager.GetRobots();
    REQUIRE(robots.size() == 1);
    REQUIRE(robots.back().robotID == std::to_string(1));
    REQUIRE(robots.back().robotSize == "Large");
    REQUIRE(robots.back().robotFunction == "Vacuum");

    // Step 2: Test GetAllRobotInfo to Verify Retrieval of the Same Robot
    int robot_id = std::stoi(robots.back().robotID);
    robots::Robots retrieved_robot = data_manager.GetAllRobotInfo(robot_id);

    // Validate that the retrieved robot's data matches what was originally added
    REQUIRE(retrieved_robot.get_id() == robot_id);
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
    int added_robot_id = std::stoi(data_manager.GetRobots().front().robotID);
    robots::Robots retrieved_another_robot = data_manager.GetAllRobotInfo(added_robot_id);

    // Check that the retrieved robot data matches what was added
    REQUIRE(retrieved_another_robot.get_id() == added_robot_id);
    REQUIRE(retrieved_another_robot.get_size() == "Small");
    REQUIRE(retrieved_another_robot.get_function_type() == "Scrub");

    // Clean up after the tests by deleting all robots
    data_manager.DeleteRobot(added_robot_id);
    REQUIRE(data_manager.GetRobots().empty());
}
