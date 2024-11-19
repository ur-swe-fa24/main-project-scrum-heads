#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "robot_loop_lib.hpp"
#include "robot.hpp"
#include "room_task.hpp"
#include <future>
#include <atomic>

// giving weird error as below, so not using it right now.
// Undefined symbols for architecture arm64:
//   "_main", referenced from:
//      implicit entry/start for main executable
// ld: symbol(s) not found for architecture arm64
// clang: error: linker command failed with exit code 1 (use -v to see invocation)
// make[2]: *** [tests/unit_test_loop] Error 1
// make[1]: *** [tests/CMakeFiles/unit_test_loop.dir/all] Error 2
// make: *** [all] Error 2
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

TEST_CASE("Task function completes successfully without errors", "[task]") {
    std::atomic_bool is_canceled(false);
    std::atomic_bool is_paused(false);

    robots::Robots robot(1, "Medium", 100, 100, "None", "Idle", 0, robots::Robots::robotFunction::SCRUB, 0, 0);
    tasks::RoomTask room_task(tasks::RoomTask::RoomSize::MEDIUM);

    // Calculate task length from room task
    int task_length = room_task.calculate_task_duration();
    
    int result = task(robot, room_task, is_canceled, is_paused, task_length);

    REQUIRE(result >= 0); // Ensure task completes with non-negative progress
    REQUIRE(robot.get_battery_level() <= 100); // Battery level should stay within a valid range
    REQUIRE(robot.get_water_level() <= 100); // Water level should stay within a valid range
}

TEST_CASE("Task function cancels mid-way", "[task][cancel]") {
    std::atomic_bool is_canceled(false);
    std::atomic_bool is_paused(false);

    robots::Robots robot(1, "Medium", 100, 100, "None", "Idle", 0, robots::Robots::robotFunction::SCRUB, 0, 0);
    tasks::RoomTask room_task(tasks::RoomTask::RoomSize::LARGE);

    // Calculate task length from room task
    int task_length = room_task.calculate_task_duration();

    std::future<int> task_result = std::async(std::launch::async, task, std::ref(robot), std::ref(room_task), std::ref(is_canceled), std::ref(is_paused), task_length);

    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Allow task to progress a bit
    is_canceled = true;
    task_result.wait(); // Wait for task to finish

    int result = task_result.get();
    REQUIRE(is_canceled == true); // Ensure task was canceled
    REQUIRE(result < task_length); // Task should not reach full duration
}

TEST_CASE("Task function handles different room sizes", "[task][room_size]") {
    std::atomic_bool is_canceled(false);
    std::atomic_bool is_paused(false);

    robots::Robots robot(1, "Medium", 100, 100, "None", "Idle", 0, robots::Robots::robotFunction::SCRUB, 0, 0);

    SECTION("Small room task") {
        tasks::RoomTask small_room_task(tasks::RoomTask::RoomSize::SMALL);
        int task_length = small_room_task.calculate_task_duration();
        int result = task(robot, small_room_task, is_canceled, is_paused, task_length);
        REQUIRE(result == task_length); // Should complete the task
    }

    SECTION("Medium room task") {
        tasks::RoomTask medium_room_task(tasks::RoomTask::RoomSize::MEDIUM);
        int task_length = medium_room_task.calculate_task_duration();
        int result = task(robot, medium_room_task, is_canceled, is_paused, task_length);
        REQUIRE(result == task_length); // Should complete the task
    }

    SECTION("Large room task") {
        tasks::RoomTask large_room_task(tasks::RoomTask::RoomSize::LARGE);
        int task_length = large_room_task.calculate_task_duration();
        int result = task(robot, large_room_task, is_canceled, is_paused, task_length);
        REQUIRE(result == task_length); // Should complete the task
    }
}
