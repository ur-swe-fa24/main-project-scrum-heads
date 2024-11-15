#define CATCH_CONFIG_MAIN
#include "adapters/mongo_adapter.hpp"
#include "robot.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <catch2/catch_approx.hpp>

using namespace robots;
using namespace adapters;
Mongo_Adapter mongo_other{};
TEST_CASE("Mongo Adapter Write and Read Robot") {

    //Create a new Robot
    robots::Robots temp_robot(9009, "Large", 100, 50, "", "Vacuum", 3, "scrub", 10, 15);

    //Write said robot
    mongo_other.write_robot(temp_robot);

    //Collect the string that read robot will produce and the expected string
    std::string information = mongo_other.read_robot(temp_robot.get_id());
    std::string robot = "{ \"_id\" : 9009, \"size\" : \"Large\", \"water_level\" : 100, \"battery level\" : 50, \"Error Status\" : \"\", \"Task Status\" : \"Vacuum\", \"Task Room\" : 3, \"Function Type\" : \"scrub\", \"Location x\" : 10, \"Location y\" : 15 }";

    //Check that the strings match
    REQUIRE_THAT( information, Catch::Matchers::Equals(robot ) );  
    mongo_other.delete_all_robots(); 
}

TEST_CASE("Mongo Adapter Write A Robot with a Duplicate ID") {

    //Create new Robot
    robots::Robots temp_robot(379, "Large", 100, 50, "", "Vacuum", 3, "Scrub", 10, 15);

    //Write said robot
    mongo_other.write_robot(temp_robot);

    //Create a robot with a duplicate id
    robots::Robots temp_robot2(379, "Small", 60, 50, "", "Scrubber", 6, "Scrub", 10, 15);

    //Check that the function will throw an exception because no exception keys are allowed
    REQUIRE_THROWS( mongo_other.write_robot(temp_robot2) );  
    mongo_other.delete_all_robots(); 
}

TEST_CASE("Mongo Adapter Delete Robot Test") {


    robots::Robots temp_robot(884, "Large", 100, 50, "", "Vacuum", 3, "Scrub", 10, 15);
    
    //Write said robot
    mongo_other.write_robot(temp_robot);

    //Delete Robot and get the information output when we read for a robot that is not there
    mongo_other.delete_robot(884);
    std::string robot = mongo_other.read_robot(884);

    //Check that the correct string is outputted
    REQUIRE_THAT( robot, Catch::Matchers::Equals("No instance of robot with id 884") ); 
    mongo_other.delete_all_robots(); 
}

TEST_CASE("Mongo Adapter Delete Nonexistent Robot Test") {
    //Delete Robot and get the information output when we read for a robot that is not there
    std::string robot = mongo_other.delete_robot(884);

    //Check that the correct string is outputted
    REQUIRE_THAT( robot, Catch::Matchers::Equals("No instance of robot with id 884") ); 
    mongo_other.delete_all_robots(); 
}

TEST_CASE("Mongo Adapter Update Robot Test") {

    //Create a new Robot
    robots::Robots temp_robot(9009, "Large", 50, 100, "", "Vacuum", 3, "Scrub", 10, 15);

    //Write said robot
    mongo_other.write_robot(temp_robot);

    //Update the robots water level and battery level
    mongo_other.update_robot(9009, 100, 50);

    //Get the information from the read robot and expected output
    std::string information = mongo_other.read_robot(9009);
    std::string robot = "{ \"_id\" : 9009, \"size\" : \"Large\", \"water_level\" : 100, \"battery level\" : 50, \"Error Status\" : \"\", \"Task Status\" : \"Vacuum\", \"Task Room\" : 3, \"Function Type\" : \"scrub\", \"Location x\" : 10, \"Location y\" : 15 }";
    
    //Check that the output matches the expected output
    REQUIRE_THAT( information, Catch::Matchers::Equals(robot ) );  
    mongo_other.delete_all_robots(); 
}
