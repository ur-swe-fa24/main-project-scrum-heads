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
    robots::Robots temp_robot(1000, "Large", 100, 50, "", "Vacuum", 3, "scrub", 0);

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
    REQUIRE( temp_robot.get_task_status() == information.get_task_status() ); 
    mongo_other.delete_all_robots(); 
}

TEST_CASE("Mongo Adapter Write A Robot with a Duplicate ID") {

    //Create new Robot
    robots::Robots temp_robot(379, "Large", 100, 50, "", "Vacuum", 3, "Scrub", 0);

    //Write said robot
    mongo_other.write_robot(temp_robot);

    //Create a robot with a duplicate id
    robots::Robots temp_robot2(379, "Small", 60, 50, "", "Scrubber", 6, "Scrub", 0);

    //Check that the function will throw an exception because no exception keys are allowed
    REQUIRE_THROWS( mongo_other.write_robot(temp_robot2) );  
    mongo_other.delete_all_robots(); 
}

TEST_CASE("Mongo Adapter Delete Robot Test") {


    robots::Robots temp_robot(884, "Large", 100, 50, "", "Vacuum", 3, "Scrub", 0);
    
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
    robots::Robots temp_robot(9009, "Large", 50, 100, "", "Vacuum", 3, "Scrub", 0);

    //Write said robot
    mongo_other.write_robot(temp_robot);

    //Update the robots water level and battery level
    mongo_other.update_robot(9009, 100, 50);

    //Get the information from the read robot and expected output
    robots::Robots information = mongo_other.read_robot(9009);
    REQUIRE( information.get_id() == 9009);  
    REQUIRE( information.get_water_level() == 100); 
    REQUIRE( information.get_battery_level() == 50); 
    REQUIRE( temp_robot.get_size() == information.get_size() ); 
    REQUIRE( temp_robot.get_function_type() == information.get_function_type() ); 
    REQUIRE( temp_robot.get_error_status() == information.get_error_status() ); 
    REQUIRE( temp_robot.get_task_status() == information.get_task_status() ); 
    
    mongo_other.delete_all_robots(); 
}

TEST_CASE("Mongo Adapter Get all Ids Test") {
    mongo_other.delete_all_robots(); 
    
    //Create a new Robots
    robots::Robots temp_robot1(1, "Large", 50, 100, "", "Vacuum", 3, "Scrub", 0);
    robots::Robots temp_robot2(2, "Large", 50, 100, "", "Vacuum", 3, "Scrub", 0);
    robots::Robots temp_robot3(3, "Large", 50, 100, "", "Vacuum", 3, "Scrub", 0);
    robots::Robots temp_robot4(4, "Large", 50, 100, "", "Vacuum", 3, "Scrub", 0);

    //Write said robots
    mongo_other.write_robot(temp_robot1);
    mongo_other.write_robot(temp_robot2);  
    mongo_other.write_robot(temp_robot3);
    mongo_other.write_robot(temp_robot4);

    //Get the vector of all the robot ids
    std::vector<int> ids = mongo_other.get_all_ids();
    std::vector<int> idsTest = {1, 2, 3, 4};
    
    //Check that the ids returned are correct
    REQUIRE( ids == idsTest );   
}

TEST_CASE("Mongo Adapter Delete all robots test") {
    mongo_other.delete_all_robots(); 
    
    //Get the information from the read robot and empty vector of ids
    std::vector<int> ids = mongo_other.get_all_ids();
    std::vector<int> idsTest = {};
    
    //Check that the lists is indeed empty
    REQUIRE( ids == idsTest );   
}

TEST_CASE("Mongo Adapter Read All Robots test") {
    //Create a new Robots
    robots::Robots temp_robot1(1, "Large", 50, 100, "", "Vacuum", 3, "Scrub", 0);
    robots::Robots temp_robot2(2, "Large", 50, 100, "", "Vacuum", 3, "Scrub", 0);
    robots::Robots temp_robot3(3, "Large", 50, 100, "", "Vacuum", 3, "Scrub", 0);
    robots::Robots temp_robot4(4, "Large", 50, 100, "", "Vacuum", 3, "Scrub", 0);

    //Write said robots
    mongo_other.write_robot(temp_robot1);
    mongo_other.write_robot(temp_robot2);  
    mongo_other.write_robot(temp_robot3);
    mongo_other.write_robot(temp_robot4);
    

    std::vector<robots::Robots> robots = mongo_other.read_all_robots();
    //Check that the lists is indeed empty
    int count = 1;
    for(auto robot : robots){
        REQUIRE( robot.get_id() == count);  
        REQUIRE( temp_robot1.get_size() == robot.get_size() ); 
        REQUIRE( temp_robot1.get_water_level() == robot.get_water_level() ); 
        REQUIRE( temp_robot1.get_battery_level() == robot.get_battery_level() ); 
        REQUIRE( temp_robot1.get_function_type() == robot.get_function_type() ); 
        REQUIRE( temp_robot1.get_error_status() == robot.get_error_status() ); 
        REQUIRE( temp_robot1.get_task_status() == robot.get_task_status() ); 
        count++;
    }  
    mongo_other.delete_all_robots();  
}


// int robot_id, std::string robotSize, int waterLevel, 
//                     int batteryLevel, std::string errorStatus, std::string taskStatus, 
//                     int taskRoom, std::string functionType, int task_percent
TEST_CASE("Mongo Adapter Write Task test") {

    robots::Robots temp_robot2(1, "Large", 50, 100, "", "", 3, "Scrub", 0);
    mongo_other.write_robot(temp_robot2);
    mongo_other.write_task(temp_robot2);


    robots::Robots information = mongo_other.read_ongoing_task(1);
    REQUIRE( information.get_id() == temp_robot2.get_id());  
    // REQUIRE( information.get_size() == temp_robot2.get_size() ); 
    // REQUIRE( information.get_water_level() == temp_robot2.get_water_level() ); 
    // REQUIRE( information.get_battery_level() == temp_robot2.get_battery_level() ); 
    // REQUIRE( information.get_function_type() == temp_robot2.get_function_type() ); 
    REQUIRE( information.get_error_status() == temp_robot2.get_error_status() ); 
    REQUIRE( information.get_task_status() == "Ongoing" ); 
    REQUIRE( information.get_task_percent() == temp_robot2.get_task_percent() ); 
    REQUIRE( information.get_task_room() == temp_robot2.get_task_room() );
    
    robots::Robots information2 = mongo_other.read_robot(1);
    REQUIRE( information2.get_id() == 1);  
    REQUIRE( information2.get_size() == "Large"); 
    REQUIRE( information2.get_water_level() == 50 ); 
    REQUIRE( information2.get_battery_level() == 100 ); 
    REQUIRE( information2.get_function_type() == "Scrub" ); 
    REQUIRE( information2.get_error_status() == "" ); 
    REQUIRE( information2.get_task_status() == "Ongoing" ); 

    mongo_other.delete_all_robots();  
    mongo_other.delete_all_tasks();  
}

// TEST_CASE("Mongo Adapter Attempt to give robot two tasks") {
    
// }

// TEST_CASE("Mongo Adapter Update Status") {
    
// }