#define CATCH_CONFIG_MAIN
#include "adapters/mongo_adapter.hpp"
#include "robot.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <catch2/catch_approx.hpp>

using namespace robots;
using namespace adapters;

TEST_CASE("Mongo Adapter Test") {
    robots::Robots::Start_Time startTime = {9, 0, 0};  // Represents 9:00:00 AM
    robots::Robots::End_Time endTime = {17, 30, 45}; 
    robots::Robots temp_robot(3, "Large", 100, 50, "", "Vacuum", 3, robots::Robots::robotFunction::SCRUB, 10, 15, startTime, endTime);
    adapters::Mongo_Adapter mongo_other{};

    SECTION("Test Write Robot"){
        mongo_other.write_robot(temp_robot);
        std::string information = mongo_other.read_robot(temp_robot.get_id());
        std::string robot = "";
        REQUIRE_THAT( information, Catch::Matchers::Equals(robot ) );
        // REQUIRE( ab.get_collision_threshold() == Catch::Approx(5L));
    }
}