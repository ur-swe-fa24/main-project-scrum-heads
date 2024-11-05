#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "room_task.hpp"
#include "robot.hpp"
#include "spdlog/spdlog.h"
using namespace tasks;
using namespace robots;

TEST_CASE("Robot Initialization") {
    SECTION("Default Initialization") {
        Robots robot(1, "Medium", 100, 100, "No Error", "Idle", 0, Robots::robotFunction::SCRUB, 0, 0);
        REQUIRE(robot.get_id() == 1);
        REQUIRE(robot.get_water_level() == 100);
        REQUIRE(robot.get_battery_level() == 100);
        REQUIRE(robot.get_task_status() == "Idle");
    }
}

TEST_CASE("Room Task Functionality") {
    Robots robot(1, "Small", 100, 100, "No Error", "Idle", 0, Robots::robotFunction::SCRUB, 0, 0);
    RoomTask task(RoomTask::RoomSize::SMALL);

    SECTION("Task Performance for Small Room") {
        task.perform_task(robot);
        REQUIRE(robot.get_battery_level() <= 90);  // Expect battery level decrease
        REQUIRE(robot.get_water_level() <= 90);    // Expect water level decrease
    }

    SECTION("Task Performance for Medium Room") {
        robot = Robots(2, "Medium", 100, 100, "No Error", "Idle", 0, Robots::robotFunction::VACUUM, 0, 0);
        RoomTask mediumTask(RoomTask::RoomSize::MEDIUM);
        mediumTask.perform_task(robot);
        REQUIRE(robot.get_battery_level() <= 60);  // Expect battery level decrease
        REQUIRE(robot.get_water_level() <= 60);    // Expect water level decrease
    }

    SECTION("Task Performance for Large Room") {
        robot = Robots(3, "Large", 100, 100, "No Error", "Idle", 0, Robots::robotFunction::SHAMPOO, 0, 0);
        RoomTask largeTask(RoomTask::RoomSize::LARGE);
        largeTask.perform_task(robot);
        REQUIRE(robot.get_battery_level() <= 10);  // Expect battery level decrease
        REQUIRE(robot.get_water_level() <= 10);    // Expect water level decrease
    }
}

TEST_CASE("Error Handling in Task") {
    Robots robot(4, "Medium", 50, 50, "No Error", "Idle", 0, Robots::robotFunction::VACUUM, 0, 0);
    RoomTask task(RoomTask::RoomSize::MEDIUM);

    SECTION("Perform task with low battery") {
        robot = Robots(4, "Medium", 50, 5, "Low Battery", "Idle", 0, Robots::robotFunction::VACUUM, 0, 0);
        task.perform_task(robot);
        REQUIRE(robot.get_battery_level() == 5);  // Expect battery level no decrease
        REQUIRE(robot.get_water_level() == 50);  // Expect water level no decrease
    }

    SECTION("Perform task with normal battery") {
        robot = Robots(5, "Medium", 50, 100, "No Error", "Idle", 0, Robots::robotFunction::SCRUB, 0, 0);
        task.perform_task(robot);
        REQUIRE(robot.get_battery_level() == 60);  // Expect battery level decrease
        REQUIRE(robot.get_water_level() == 10);  // Expect water level decrease
    }
}
