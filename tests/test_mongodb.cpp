#define CATCH_CONFIG_MAIN
#include "adapters/mongo_adapter.hpp"
#include "robot.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <catch2/catch_approx.hpp>
#include <vector>

using namespace robots;
using namespace adapters;
Mongo_Adapter mongo_other{};
TEST_CASE("Mongo Adapter Write and Read Robot") {

    //Create a new Robot
    robots::Robots temp_robot(1000, "Large", 100, 50, "", "Vacuum", 3, "scrub", 10, 15);

    //Write said robot
    mongo_other.write_robot(temp_robot);

    // Collect the string that robot that is produced from reading a row in the database
    robots::Robots information = mongo_other.read_robot(1000);
      
    // Check that all attributes match across the robots
    REQUIRE( temp_robot.get_id() == information.get_id());  
    REQUIRE( temp_robot.get_size() == information.get_size() ); 
    REQUIRE( temp_robot.get_water_level() == information.get_water_level() ); 
    REQUIRE( temp_robot.get_battery_level() == information.get_battery_level() ); 
    REQUIRE( temp_robot.get_function_type() == information.get_function_type() ); 
    REQUIRE( temp_robot.get_error_status() == information.get_error_status() ); 
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
    robots::Robots robot = mongo_other.read_robot(884);

    //Check that the correct string is outputted
    REQUIRE( robot.get_error_status() == "No instance of robot with id" ); 
    REQUIRE( robot.get_id() == 884 ); 
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
    robots::Robots information = mongo_other.read_robot(9009);
    REQUIRE( information.get_id() == 9009);  
    REQUIRE( information.get_water_level() == 100); 
    REQUIRE( information.get_battery_level() == 50); 
    
    mongo_other.delete_all_robots(); 
}

TEST_CASE("Mongo Adapter Get all Ids Test") {
    mongo_other.delete_all_robots(); 
    
    //Create a new Robots
    robots::Robots temp_robot1(1, "Large", 50, 100, "", "Vacuum", 3, "Scrub", 10, 15);
    robots::Robots temp_robot2(2, "Large", 50, 100, "", "Vacuum", 3, "Scrub", 10, 15);
    robots::Robots temp_robot3(3, "Large", 50, 100, "", "Vacuum", 3, "Scrub", 10, 15);
    robots::Robots temp_robot4(4, "Large", 50, 100, "", "Vacuum", 3, "Scrub", 10, 15);

    //Write said robots
    mongo_other.write_robot(temp_robot1);
    mongo_other.write_robot(temp_robot2);  
    mongo_other.write_robot(temp_robot3);
    mongo_other.write_robot(temp_robot4);

    //Get the information from the read robot and expected output
    std::vector<int> ids = mongo_other.get_all_ids();
    std::vector<int> idsTest = {1, 2, 3, 4};
    
    //Check that the output matches the expected output
    REQUIRE( ids == idsTest );   
}

TEST_CASE("Mongo Adapter Delete all robots test") {
    mongo_other.delete_all_robots(); 
    

    //Get the information from the read robot and expected output
    std::vector<int> ids = mongo_other.get_all_ids();
    std::vector<int> idsTest = {};
    
    //Check that the output matches the expected output
    REQUIRE( ids == idsTest );   
}