#define CATCH_CONFIG_MAIN
#include "robot.hpp"
#include "robot_do_task.hpp"
#include <catch2/catch_all.hpp>
#include <thread>
#include <thread>
#include <chrono>
#include <vector>

using namespace robots;
using namespace std;

TEST_CASE("Create Robot") {
    Robots temp_robot(0, "small", 100, 100, "", "", 0, "scrub", 0);
    SECTION("Read Robot") {
        REQUIRE( temp_robot.get_id() == 0 );
        REQUIRE( temp_robot.get_size() == "small" );
        REQUIRE( temp_robot.get_water_level() == 100 );
        REQUIRE( temp_robot.get_battery_level() == 100 );
        REQUIRE( temp_robot.get_error_status() == "" );
        REQUIRE( temp_robot.get_task_status() == "" );
        REQUIRE( temp_robot.get_task_percent() == 0 );
    }
    SECTION("Add to List") {
        vector<Robots> robot_list;
        robots::Robots::add_robot(robot_list, temp_robot);
        REQUIRE( robot_list.size() == 1 );
    }
}

TEST_CASE("Robot do task") {

    // Test small robot with sufficient resources for a small room
    SECTION("Small Robot - Small Room - Sufficient Resources") {
        Robots temp_robot(0, "small", 100, 100, "", "", 0, "scrub", 0);
        robot_tasks::do_task(temp_robot, "small");
        REQUIRE(temp_robot.get_task_percent() == 100);
        REQUIRE(temp_robot.get_battery_level() == 90);
        REQUIRE(temp_robot.get_water_level() == 90);
    }

    // Test small robot with insufficient resources for a small room
    SECTION("Small Robot - Small Room - Insufficient Resources") {
        Robots temp_robot(0, "small", 5, 5, "", "", 0, "scrub", 0);
        robot_tasks::do_task(temp_robot, "small");
        REQUIRE(temp_robot.get_task_percent() == 0);
        REQUIRE(temp_robot.get_task_status() == "canceled");
    }

    // Test medium robot with sufficient resources for a medium room
    SECTION("Medium Robot - Medium Room - Sufficient Resources") {
        Robots temp_robot(1, "medium", 120, 120, "", "", 0, "scrub", 0);
        robot_tasks::do_task(temp_robot, "medium");
        REQUIRE(temp_robot.get_task_percent() == 100);
        REQUIRE(temp_robot.get_battery_level() == 80);
        REQUIRE(temp_robot.get_water_level() == 80);
    }

    // Test medium robot with insufficient resources for a medium room
    SECTION("Medium Robot - Medium Room - Insufficient Resources") {
        Robots temp_robot(1, "medium", 30, 30, "", "", 0, "scrub", 0);
        robot_tasks::do_task(temp_robot, "medium");
        REQUIRE(temp_robot.get_task_percent() == 0);
        REQUIRE(temp_robot.get_task_status() == "canceled");
    }

    // Test large robot with sufficient resources for a large room
    SECTION("Large Robot - Large Room - Sufficient Resources") {
        Robots temp_robot(2, "large", 140, 140, "", "", 0, "scrub", 0);
        robot_tasks::do_task(temp_robot, "large");
        REQUIRE(temp_robot.get_task_percent() == 100);
        REQUIRE(temp_robot.get_battery_level() == 50);
        REQUIRE(temp_robot.get_water_level() == 50);
    }

    // Test large robot with insufficient resources for a large room
    SECTION("Large Robot - Large Room - Insufficient Resources") {
        Robots temp_robot(2, "large", 80, 80, "", "", 0, "scrub", 0);
        robot_tasks::do_task(temp_robot, "large");
        REQUIRE(temp_robot.get_task_percent() == 0);
        REQUIRE(temp_robot.get_task_status() == "canceled");
    }

    // Test small robot on a medium room with sufficient resources
    SECTION("Small Robot - Medium Room - Sufficient Resources") {
        Robots temp_robot(3, "small", 100, 100, "", "", 0, "scrub", 0);
        robot_tasks::do_task(temp_robot, "medium");
        REQUIRE(temp_robot.get_task_percent() == 100);
        REQUIRE(temp_robot.get_battery_level() == 60);
        REQUIRE(temp_robot.get_water_level() == 60);
    }

    // Test small robot on a medium room with insufficient resources
    SECTION("Small Robot - Medium Room - Insufficient Resources") {
        Robots temp_robot(3, "small", 30, 30, "", "", 0, "scrub", 0);
        robot_tasks::do_task(temp_robot, "medium");
        REQUIRE(temp_robot.get_task_percent() == 0);
        REQUIRE(temp_robot.get_task_status() == "canceled");
    }
}

TEST_CASE("Check if user intervene") {
    Robots temp_robot(3, "small", 100, 100, "", "", 0, "scrub", 0);
    SECTION("User cancelled the task") {
        auto task_thread = [&]() {
            robot_tasks::do_task(temp_robot, "medium");
        };
        std::thread t(task_thread);

        // Sleep for a bit to let the task start
        std::this_thread::sleep_for(std::chrono::seconds(1));

        // Simulate user cancellation
        temp_robot.update_task_status("cancel");

        // Wait for the task thread to finish
        t.join();

        // Verify the robot's state after cancellation
        REQUIRE(temp_robot.get_task_status() == "cancel");
        REQUIRE(temp_robot.get_task_percent() < 100);
        REQUIRE(temp_robot.get_battery_level() < 100); // Some battery usage before cancellation
        REQUIRE(temp_robot.get_water_level() < 100);   // Some water usage before cancellation
    }
}

TEST_CASE("Robot Charging Function") {

    SECTION("Single Small Robot - Partially Depleted Resources") {
        robots::Robots robot(0, "small", 80, 90, "", "", 0, "scrub", 0);
        std::vector<robots::Robots> robot_list = {robot};

        // Call the robot_charge function
        robot_tasks::robot_charge(robot_list);

        // Check the water and battery levels are at maximum
        REQUIRE(robot_list[0].get_water_level() == 100);
        REQUIRE(robot_list[0].get_battery_level() == 100);
    }

    SECTION("Single Medium Robot - Fully Depleted Resources") {
        robots::Robots robot(1, "medium", 0, 0, "", "", 0, "scrub", 0);
        std::vector<robots::Robots> robot_list = {robot};

        // Call the robot_charge function
        robot_tasks::robot_charge(robot_list);

        // Check the water and battery levels are at maximum for medium robots
        REQUIRE(robot_list[0].get_water_level() == 120);
        REQUIRE(robot_list[0].get_battery_level() == 120);
    }

    SECTION("Single Large Robot - Fully Charged") {
        robots::Robots robot(2, "large", 140, 140, "", "", 0, "scrub", 0);
        std::vector<robots::Robots> robot_list = {robot};

        // Call the robot_charge function
        robot_tasks::robot_charge(robot_list);

        // Check the water and battery levels remain unchanged
        REQUIRE(robot_list[0].get_water_level() == 140);
        REQUIRE(robot_list[0].get_battery_level() == 140);
    }

    // SECTION("Multiple Robots - Mixed Sizes and Resources") {
    //     robots::Robots small_robot(3, "small", 50, 60, "", "", 0, "scrub", 0);
    //     robots::Robots medium_robot(4, "medium", 70, 80, "", "", 0, "scrub", 0);
    //     robots::Robots large_robot(5, "large", 90, 100, "", "", 0, "scrub", 0);

    //     std::vector<robots::Robots> robot_list = {small_robot, medium_robot, large_robot};

    //     // Call the robot_charge function
    //     robot_tasks::robot_charge(robot_list);

    //     // Check the water and battery levels for all robots
    //     REQUIRE(robot_list[0].get_water_level() == 100);
    //     REQUIRE(robot_list[0].get_battery_level() == 100);

    //     REQUIRE(robot_list[1].get_water_level() == 120);
    //     REQUIRE(robot_list[1].get_battery_level() == 120);

    //     REQUIRE(robot_list[2].get_water_level() == 140);
    //     REQUIRE(robot_list[2].get_battery_level() == 140);
    // }
}


// check error