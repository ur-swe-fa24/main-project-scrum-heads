#define CATCH_CONFIG_MAIN
#include "adapters/mongo_adapter.hpp"
#include "robot.hpp"
#include "room.hpp"
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
    Room room(0, "", "", "");
    robots::Robots temp_robot(1000, "Large", 100, 50, "", "Vacuum", room, "Scrub", 0);

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
    Room room(0, "", "", "");
    robots::Robots temp_robot(379, "Large", 100, 50, "", "Vacuum", room, "Scrub", 0);

    //Write said robot
    mongo_other.write_robot(temp_robot);

    //Create a robot with a duplicate id
    robots::Robots temp_robot2(379, "Small", 60, 50, "", "Scrubber", room, "Scrub", 0);

    //Check that the function will throw an exception because no exception keys are allowed
    REQUIRE_THROWS( mongo_other.write_robot(temp_robot2) );  
    mongo_other.delete_all_robots(); 
}

TEST_CASE("Mongo Adapter Delete Robot Test") {

    Room room(0, "", "", "");
    robots::Robots temp_robot(884, "Large", 100, 50, "", "Vacuum", room, "Scrub", 0);
    
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
    Room room(0, "", "", "");
    robots::Robots temp_robot(9009, "Large", 50, 100, "", "Vacuum", room, "Scrub", 0);

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
    Room room(0, "", "", "");
    robots::Robots temp_robot1(1, "Large", 50, 100, "", "Vacuum", room, "Scrub", 0);
    robots::Robots temp_robot2(2, "Large", 50, 100, "", "Vacuum", room, "Scrub", 0);
    robots::Robots temp_robot3(3, "Large", 50, 100, "", "Vacuum", room, "Scrub", 0);
    robots::Robots temp_robot4(4, "Large", 50, 100, "", "Vacuum", room, "Scrub", 0);

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
    Room room(0, "", "", "");
    //Create a new Robots
    robots::Robots temp_robot1(1, "Large", 50, 100, "", "Vacuum", room, "Scrub", 0);
    robots::Robots temp_robot2(2, "Large", 50, 100, "", "Vacuum", room, "Scrub", 0);
    robots::Robots temp_robot3(3, "Large", 50, 100, "", "Vacuum", room, "Scrub", 0);
    robots::Robots temp_robot4(4, "Large", 50, 100, "", "Vacuum", room, "Scrub", 0);

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


TEST_CASE("Mongo Adapter Read All Robots test no robots ") {
    mongo_other.delete_all_robots();
    

    std::vector<robots::Robots> robots = mongo_other.read_all_robots();
    std::vector<robots::Robots> robots1;
    for(robots::Robots robot : robots){
        if(robot.get_task_status() == "Avaiiable" ){
            std::cout << 1 << std::endl;
        }
    } 
    mongo_other.delete_all_robots();  
}


    // int room_number_;            // Room number
    // std::string room_size_;      // Room size in a string format (e.g., "small")
    // std::string floor_type_;     // Floor type (e.g., "Carpet", "Tile", "Wood")
    // std::string availability_;   // Availability status (e.g., "Available", "Not Available")
    // int getRoomNumber() const { return room_number_; }
    // std::string getRoomSize() const { return room_size_; }
    // std::string getFloorType() const { return floor_type_; }
    // std::string getAvailability() const { return availability_; }
TEST_CASE("Test Write Rooms"){
    mongo_other.delete_rooms(); 
    mongo_other.delete_all_robots();

    std::vector<Room> rooms;
    Room room1(1, "Small", "Tile", "Available");
    rooms.push_back(room1);
    Room room2(2, "Small", "Tile", "Available");
    rooms.push_back(room2);
    Room room3(3, "Small", "Tile", "Available");
    rooms.push_back(room3);
    Room room4(4, "Small", "Tile", "Available");
    rooms.push_back(room4);
    Room room5(5, "Small", "Tile", "Available");
    rooms.push_back(room5);

    mongo_other.write_rooms(rooms);

    std::vector<Room> read_rooms = mongo_other.read_all_rooms();

    int counter = 1;
    for(Room room : read_rooms){
        REQUIRE(room.getRoomNumber() == counter);
        REQUIRE(room.getRoomSize() == "Small");
        REQUIRE(room.getFloorType() == "Tile");
        REQUIRE(room.getAvailability() == "Available");
        counter++;
    }

    mongo_other.delete_all_robots();
    mongo_other.delete_rooms(); 
}

TEST_CASE("Test Read Rooms"){
    mongo_other.delete_rooms(); 
    mongo_other.delete_all_robots();

    std::vector<Room> rooms;
    Room room1(1, "Small", "Tile", "Available");
    rooms.push_back(room1);
    Room room2(2, "Small", "Tile", "Available");
    rooms.push_back(room2);
    Room room3(3, "Small", "Tile", "Available");
    rooms.push_back(room3);
    Room room4(4, "Medium", "Carpet", "Available");
    rooms.push_back(room4);
    Room room5(5, "Small", "Tile", "Available");
    rooms.push_back(room5);

    mongo_other.write_rooms(rooms);

    Room room = mongo_other.read_room(4);

    REQUIRE(room.getRoomNumber() == 4);
    REQUIRE(room.getRoomSize() == "Medium");
    REQUIRE(room.getFloorType() == "Carpet");
    REQUIRE(room.getAvailability() == "Available");

    mongo_other.delete_all_robots();
    mongo_other.delete_rooms(); 
}

TEST_CASE("Test Update Room Availability"){
    mongo_other.delete_rooms(); 
    mongo_other.delete_all_robots();

    std::vector<Room> rooms;
    Room room1(1, "Small", "Tile", "Available");
    rooms.push_back(room1);
    Room room2(2, "Small", "Tile", "Available");
    rooms.push_back(room2);
    Room room3(3, "Small", "Tile", "Available");
    rooms.push_back(room3);
    Room room4(4, "Medium", "Carpet", "Available");
    rooms.push_back(room4);
    Room room5(5, "Small", "Tile", "Available");
    rooms.push_back(room5);

    mongo_other.write_rooms(rooms);

    mongo_other.update_room_availability(1, "Busy");

    mongo_other.update_room_availability(2, "Unavailable");

    Room room_1 = mongo_other.read_room(1);
    Room room_2 = mongo_other.read_room(2);

    REQUIRE(room_1.getRoomNumber() == 1);
    REQUIRE(room_1.getRoomSize() == "Small");
    REQUIRE(room_1.getFloorType() == "Tile");
    REQUIRE(room_1.getAvailability() == "Busy");

    REQUIRE(room_2.getRoomNumber() == 2);
    REQUIRE(room_2.getRoomSize() == "Small");
    REQUIRE(room_2.getFloorType() == "Tile");
    REQUIRE(room_2.getAvailability() == "Unavailable");

    mongo_other.delete_all_robots();
    mongo_other.delete_rooms(); 
}

// int robot_id, std::string robotSize, int waterLevel, 
// int batteryLevel, std::string errorStatus, std::string taskStatus, 
// int taskRoom, std::string functionType, int task_percent
TEST_CASE("Mongo Adapter Write Task test") {
    mongo_other.delete_all_robots();  
    mongo_other.delete_all_tasks(); 
    mongo_other.delete_rooms(); 

    //Write the rooms
    std::vector<Room> rooms;
    Room room1(1, "Small", "Tile", "Available");
    rooms.push_back(room1);
    Room room2(2, "Small", "Tile", "Available");
    rooms.push_back(room2);
    Room room3(3, "Small", "Tile", "Available");
    rooms.push_back(room3);
    Room room4(4, "Medium", "Carpet", "Available");
    rooms.push_back(room4);
    Room room5(5, "Small", "Tile", "Available");
    rooms.push_back(room5);

    mongo_other.write_rooms(rooms);



    Room room(3, "Small", "Tile", "Available");
    robots::Robots temp_robot2(1, "Large", 50, 100, "", "", room, "Scrub", 0);
    mongo_other.write_robot(temp_robot2);
    mongo_other.write_task(temp_robot2);


    robots::Robots information = mongo_other.read_ongoing_task(1);
    REQUIRE( information.get_id() == temp_robot2.get_id());  
    REQUIRE( information.get_size() == temp_robot2.get_size() ); 
    REQUIRE( information.get_water_level() == temp_robot2.get_water_level() ); 
    REQUIRE( information.get_battery_level() == temp_robot2.get_battery_level() ); 
    REQUIRE( information.get_function_type() == temp_robot2.get_function_type() ); 
    REQUIRE( information.get_error_status() == "" ); 
    REQUIRE( information.get_task_status() == "Ongoing" ); 
    REQUIRE( information.get_task_percent() == temp_robot2.get_task_percent() ); 
    REQUIRE( information.get_task_room().getRoomNumber() == temp_robot2.get_task_room().getRoomNumber());
    REQUIRE( information.get_task_room().getRoomSize() == temp_robot2.get_task_room().getRoomSize());
    REQUIRE( information.get_task_room().getFloorType() == temp_robot2.get_task_room().getFloorType());
    REQUIRE( information.get_task_room().getAvailability() == "Busy");

    robots::Robots information2 = mongo_other.read_robot(1);
    REQUIRE( information2.get_id() == 1);  
    REQUIRE( information2.get_size() == "Large"); 
    REQUIRE( information2.get_water_level() == 50 ); 
    REQUIRE( information2.get_battery_level() == 100 ); 
    REQUIRE( information2.get_function_type() == "Scrub" ); 
    REQUIRE( information2.get_error_status() == "" ); 
    REQUIRE( information2.get_task_status() == "Ongoing" ); 


    Room room_3 = mongo_other.read_room(3);

    REQUIRE(room_3.getRoomNumber() == 3);
    REQUIRE(room_3.getRoomSize() == "Small");
    REQUIRE(room_3.getFloorType() == "Tile");
    REQUIRE(room_3.getAvailability() == "Busy");

    mongo_other.delete_all_robots();  
    mongo_other.delete_all_tasks(); 
    mongo_other.delete_rooms();  
}

TEST_CASE("Mongo Adapter Write Task Test Second Option") {
    mongo_other.delete_all_robots();  
    mongo_other.delete_all_tasks();
    mongo_other.delete_rooms(); 



    //Write the rooms
    std::vector<Room> rooms;
    Room room1(1, "Small", "Tile", "Available");
    rooms.push_back(room1);
    Room room2(2, "Small", "Tile", "Available");
    rooms.push_back(room2);
    Room room3(3, "Small", "Tile", "Available");
    rooms.push_back(room3);
    Room room4(4, "Medium", "Carpet", "Available");
    rooms.push_back(room4);
    Room room5(5, "Small", "Tile", "Available");
    rooms.push_back(room5);

    mongo_other.write_rooms(rooms);

    Room room(0, "", "", "");
    robots::Robots temp_robot2(1, "Large", 50, 100, "", "", room, "Scrub", 0);
    mongo_other.write_robot(temp_robot2);
    mongo_other.write_task(1, 3);


    robots::Robots information = mongo_other.read_ongoing_task(1);
    REQUIRE( information.get_id() == 1);  
    REQUIRE( information.get_size() == "Large" ); 
    REQUIRE( information.get_water_level() == 50 ); 
    REQUIRE( information.get_battery_level() == 100 ); 
    REQUIRE( information.get_function_type() == "Scrub" ); 
    REQUIRE( information.get_error_status() == "" ); 
    REQUIRE( information.get_task_status() == "Ongoing" ); 
    REQUIRE( information.get_task_percent() == 0 ); 
    REQUIRE( information.get_task_room().getRoomNumber() == 3);
    REQUIRE( information.get_task_room().getRoomSize() == "Small");
    REQUIRE( information.get_task_room().getFloorType() == "Tile");
    REQUIRE( information.get_task_room().getAvailability() == "Busy");
    
    robots::Robots information2 = mongo_other.read_robot(1);
    REQUIRE( information2.get_id() == 1);  
    REQUIRE( information2.get_size() == "Large"); 
    REQUIRE( information2.get_water_level() == 50 ); 
    REQUIRE( information2.get_battery_level() == 100 ); 
    REQUIRE( information2.get_function_type() == "Scrub" ); 
    REQUIRE( information2.get_error_status() == "" ); 
    REQUIRE( information2.get_task_status() == "Ongoing" ); 

    Room room_3 = mongo_other.read_room(3);

    REQUIRE(room_3.getRoomNumber() == 3);
    REQUIRE(room_3.getRoomSize() == "Small");
    REQUIRE(room_3.getFloorType() == "Tile");
    REQUIRE(room_3.getAvailability() == "Busy");

    mongo_other.delete_all_robots();  
    mongo_other.delete_all_tasks(); 
    mongo_other.delete_rooms();  
}

TEST_CASE("Mongo Adapter Write Task test 2") {
    mongo_other.delete_all_robots();  
    mongo_other.delete_all_tasks(); 
    mongo_other.delete_rooms();

    //Write the rooms
    std::vector<Room> rooms;
    Room room1(1, "Small", "Tile", "Available");
    rooms.push_back(room1);
    Room room2(2, "Small", "Tile", "Available");
    rooms.push_back(room2);
    Room room3(3, "Small", "Tile", "Available");
    rooms.push_back(room3);
    Room room4(4, "Medium", "Carpet", "Available");
    rooms.push_back(room4);
    Room room5(5, "Small", "Tile", "Available");
    rooms.push_back(room5);

    mongo_other.write_rooms(rooms);


    Room room(0, "", "", "");
    robots::Robots temp_robot1(1, "Large", 50, 100, "", "", room, "Scrub", 0);
    robots::Robots temp_robot2(2, "Small", 75, 90, "", "", room, "Scrub", 0);
    robots::Robots temp_robot3(3, "Medium", 90, 68, "", "", room, "Scrub", 0);
    mongo_other.write_robot(temp_robot1);
    mongo_other.write_robot(temp_robot2);
    mongo_other.write_robot(temp_robot3);

    mongo_other.write_task(2, 2);

    robots::Robots information = mongo_other.read_ongoing_task(2);
    REQUIRE( information.get_id() == temp_robot2.get_id());  
    REQUIRE( information.get_size() == temp_robot2.get_size() ); 
    REQUIRE( information.get_water_level() == temp_robot2.get_water_level() ); 
    REQUIRE( information.get_battery_level() == temp_robot2.get_battery_level() ); 
    REQUIRE( information.get_function_type() == temp_robot2.get_function_type() ); 
    REQUIRE( information.get_error_status() == temp_robot2.get_error_status() ); 
    REQUIRE( information.get_task_status() == "Ongoing" ); 
    REQUIRE( information.get_task_percent() == temp_robot2.get_task_percent() ); 
    REQUIRE( information.get_task_room().getRoomNumber() == 2);
    REQUIRE( information.get_task_room().getRoomSize() == "Small");
    REQUIRE( information.get_task_room().getFloorType() == "Tile");
    REQUIRE( information.get_task_room().getAvailability() == "Busy");
    
    robots::Robots information2 = mongo_other.read_robot(2);
    REQUIRE( information2.get_id() == 2);  
    REQUIRE( information2.get_size() == "Small"); 
    REQUIRE( information2.get_water_level() == 75 ); 
    REQUIRE( information2.get_battery_level() == 90 ); 
    REQUIRE( information2.get_function_type() == "Scrub" ); 
    REQUIRE( information2.get_error_status() == "" ); 
    REQUIRE( information2.get_task_status() == "Ongoing" );


    Room room_2 = mongo_other.read_room(2);

    REQUIRE(room_2.getRoomNumber() == 2);
    REQUIRE(room_2.getRoomSize() == "Small");
    REQUIRE(room_2.getFloorType() == "Tile");
    REQUIRE(room_2.getAvailability() == "Busy");

    mongo_other.delete_all_robots();  
    mongo_other.delete_all_tasks();  
    mongo_other.delete_rooms();
}

TEST_CASE("Mongo Adapter Write Task test error") {
    //Write the rooms
    std::vector<Room> rooms;
    Room room1(1, "Small", "Tile", "Available");
    rooms.push_back(room1);
    Room room2(2, "Small", "Tile", "Available");
    rooms.push_back(room2);
    Room room3(3, "Small", "Tile", "Available");
    rooms.push_back(room3);
    Room room4(4, "Medium", "Carpet", "Available");
    rooms.push_back(room4);
    Room room5(5, "Small", "Tile", "Available");
    rooms.push_back(room5);

    mongo_other.write_rooms(rooms);

    Room room(3, "Small", "Tile", "Available");
    robots::Robots temp_robot1(1, "Large", 50, 100, "", "Available", room, "Scrub", 0);
    mongo_other.write_robot(temp_robot1);
    mongo_other.write_task(temp_robot1);


    robots::Robots temp_robot2(1, "Large", 50, 100, "", "", room, "Scrub", 0);
    REQUIRE_THROWS( mongo_other.write_task(temp_robot2) );  

    mongo_other.delete_all_robots();  
    mongo_other.delete_all_tasks();
    mongo_other.delete_rooms();  
}

TEST_CASE("Mongo Adapter Write Task test error 2") {
    //Write the rooms
    std::vector<Room> rooms;
    Room room1(1, "Small", "Tile", "Available");
    rooms.push_back(room1);
    Room room2(2, "Small", "Tile", "Available");
    rooms.push_back(room2);
    Room room3(3, "Small", "Tile", "Available");
    rooms.push_back(room3);
    Room room4(4, "Medium", "Carpet", "Available");
    rooms.push_back(room4);
    Room room5(5, "Small", "Tile", "Available");
    rooms.push_back(room5);

    mongo_other.write_rooms(rooms);

    Room room(0, "", "", "");
    robots::Robots temp_robot1(1, "Large", 50, 100, "", "Available", room, "Scrub", 0);
    mongo_other.write_robot(temp_robot1);
    mongo_other.write_task(1, 3);


    // robots::Robots temp_robot2(1, "Large", 50, 100, "", "Available", room, "Scrub", 0);
    REQUIRE_THROWS( mongo_other.write_task(1, 2) );  

    mongo_other.delete_all_robots();  
    mongo_other.delete_all_tasks();
    mongo_other.delete_rooms();  
}

TEST_CASE("Mongo Adapter Write Task test error 3") {
    //Write the rooms
    std::vector<Room> rooms;
    Room room1(1, "Small", "Tile", "Available");
    rooms.push_back(room1);
    Room room2(2, "Small", "Tile", "Available");
    rooms.push_back(room2);
    Room room3(3, "Small", "Tile", "Available");
    rooms.push_back(room3);
    Room room4(4, "Medium", "Carpet", "Available");
    rooms.push_back(room4);
    Room room5(5, "Small", "Tile", "Available");
    rooms.push_back(room5);

    mongo_other.write_rooms(rooms);

    Room room(0, "", "", "");
    robots::Robots temp_robot1(1, "Large", 50, 100, "", "Available", room, "Scrub", 0);
    mongo_other.write_robot(temp_robot1);
    mongo_other.write_task(1, 3);

    Room room_2 = mongo_other.read_room(3);

    REQUIRE(room_2.getAvailability() == "Busy");


    robots::Robots temp_robot2(2, "Large", 50, 100, "", "Available", room, "Scrub", 0);
    mongo_other.write_robot(temp_robot2);
    REQUIRE_THROWS( mongo_other.write_task(2, 3) );  

    mongo_other.delete_all_robots();  
    mongo_other.delete_all_tasks();
    mongo_other.delete_rooms();  
}

TEST_CASE("Mongo Adapter Update Status") {
    mongo_other.delete_all_robots();  
    mongo_other.delete_all_tasks();
    mongo_other.delete_rooms(); 

    //Write the rooms
    std::vector<Room> rooms;
    Room room1(1, "Small", "Tile", "Available");
    rooms.push_back(room1);
    Room room2(2, "Small", "Tile", "Available");
    rooms.push_back(room2);
    Room room3(3, "Small", "Tile", "Available");
    rooms.push_back(room3);
    Room room4(4, "Medium", "Carpet", "Available");
    rooms.push_back(room4);
    Room room5(5, "Small", "Tile", "Available");
    rooms.push_back(room5);

    mongo_other.write_rooms(rooms);


    Room room(0, "", "", "");
    robots::Robots temp_robot1(1, "Large", 50, 100, "", "Available", room, "Scrub", 0);
    robots::Robots temp_robot2(2, "Small", 75, 90, "", "Available", room, "Scrub", 0);
    robots::Robots temp_robot3(3, "Medium", 90, 68, "", "Available", room, "Scrub", 0);
    mongo_other.write_robot(temp_robot1);
    mongo_other.write_robot(temp_robot2);
    mongo_other.write_robot(temp_robot3);

    mongo_other.write_task(1, 3);
    mongo_other.write_task(2, 2);
    mongo_other.write_task(3, 1);

    std::vector<robots::Robots> updates;
    Room room_3(3, "Small", "Tile", "Available");
    robots::Robots temp_robot4(1, "Large", 40, 96, "Error", "Available", room_3, "Scrub", 10);
    updates.push_back(temp_robot4);

    Room room_2(2, "Small", "Tile", "Busy");
    robots::Robots temp_robot5(2, "Small", 65, 70, "", "Ongoing", room_2, "Scrub", 20);
    updates.push_back(temp_robot5);

    Room room_1(1, "Small", "Tile", "Busy");
    robots::Robots temp_robot6(3, "Medium", 80, 60, "", "Ongoing", room_1, "Scrub", 30);
    updates.push_back(temp_robot6);

    mongo_other.update_task_status(updates);

    robots::Robots update_1 = mongo_other.read_ongoing_task(1);
    REQUIRE( update_1.get_id() == 1);  
    REQUIRE( update_1.get_size() == "Large" ); 
    REQUIRE( update_1.get_water_level() == 40 ); 
    REQUIRE( update_1.get_battery_level() == 96 ); 
    REQUIRE( update_1.get_function_type() == "Scrub" ); 
    REQUIRE( update_1.get_error_status() == "Error" ); 
    REQUIRE( update_1.get_task_status() == "Available" ); 
    REQUIRE( update_1.get_task_percent() == 0 ); 
    REQUIRE( update_1.get_task_room().getRoomNumber() == 0 );
    REQUIRE( update_1.get_task_room().getAvailability() == "" );


    robots::Robots update_2 = mongo_other.read_ongoing_task(2);
    REQUIRE( update_2.get_id() == 2);  
    REQUIRE( update_2.get_size() == "Small" ); 
    REQUIRE( update_2.get_water_level() == 65 ); 
    REQUIRE( update_2.get_battery_level() == 70 ); 
    REQUIRE( update_2.get_function_type() == "Scrub" ); 
    REQUIRE( update_2.get_error_status() == "" ); 
    REQUIRE( update_2.get_task_status() == "Ongoing" ); 
    REQUIRE( update_2.get_task_percent() == 20 ); 
    REQUIRE( update_2.get_task_room().getRoomNumber() == 2 );
    REQUIRE( update_2.get_task_room().getAvailability() == "Busy" );

    robots::Robots update_3 = mongo_other.read_ongoing_task(3);
    REQUIRE( update_3.get_id() == 3);  
    REQUIRE( update_3.get_size() == "Medium" ); 
    REQUIRE( update_3.get_water_level() == 80 ); 
    REQUIRE( update_3.get_battery_level() == 60 ); 
    REQUIRE( update_3.get_function_type() == "Scrub" ); 
    REQUIRE( update_3.get_error_status() == "" ); 
    REQUIRE( update_3.get_task_status() == "Ongoing" ); 
    REQUIRE( update_3.get_task_percent() == 30 ); 
    REQUIRE( update_3.get_task_room().getRoomNumber() == 1 );
    REQUIRE( update_3.get_task_room().getAvailability() == "Busy" );


    mongo_other.delete_all_robots();  
    mongo_other.delete_all_tasks();
    mongo_other.delete_rooms(); 
}

TEST_CASE("Mongo Adapter Write Task test new task") {
    mongo_other.delete_all_robots();  
    mongo_other.delete_all_tasks();  
    mongo_other.delete_rooms();

    //Write the rooms
    std::vector<Room> rooms;
    Room room1(1, "Small", "Tile", "Available");
    rooms.push_back(room1);
    Room room2(2, "Small", "Tile", "Available");
    rooms.push_back(room2);
    Room room3(3, "Small", "Tile", "Available");
    rooms.push_back(room3);
    Room room4(4, "Medium", "Carpet", "Available");
    rooms.push_back(room4);
    Room room5(5, "Small", "Tile", "Available");
    rooms.push_back(room5);

    mongo_other.write_rooms(rooms);

    Room room(0, "", "", "");
    robots::Robots temp_robot1(1, "Large", 50, 100, "", "", room, "Scrub", 0);
    mongo_other.write_robot(temp_robot1);
    mongo_other.write_task(1, 3);

    Room room_3(3, "Small", "Tile", "Busy");
    robots::Robots temp_robot2(1, "Large", 0, 50, "", "Complete", room_3, "Scrub", 0);
    std::vector<robots::Robots> updates;

    updates.push_back(temp_robot2);

    mongo_other.update_task_status(updates);
    mongo_other.write_task(1, 5);
    
    robots::Robots new_task = mongo_other.read_ongoing_task(1);
    REQUIRE( new_task.get_id() == 1);  
    REQUIRE( new_task.get_size() == "Large" ); 
    REQUIRE( new_task.get_water_level() == 0 ); 
    REQUIRE( new_task.get_battery_level() == 50 ); 
    REQUIRE( new_task.get_function_type() == "Scrub" ); 
    REQUIRE( new_task.get_error_status() == "" ); 
    REQUIRE( new_task.get_task_status() == "Ongoing" ); 
    REQUIRE( new_task.get_task_percent() == 0 ); 
    REQUIRE( new_task.get_task_room().getRoomNumber() == 5 );
    REQUIRE( new_task.get_task_room().getAvailability() == "Busy" );

    std::vector<robots::Robots> total_tasks;
    total_tasks = mongo_other.read_robot_tasks(1);

    REQUIRE( total_tasks.size() == 2 );

    mongo_other.delete_all_robots();  
    mongo_other.delete_all_tasks(); 
    mongo_other.delete_rooms(); 
}

TEST_CASE("Mongo Adapter Write Task test delete task") {
    mongo_other.delete_all_robots();  
    mongo_other.delete_all_tasks();
    mongo_other.delete_rooms();  

    //Write the rooms
    std::vector<Room> rooms;
    Room room1(1, "Small", "Tile", "Available");
    rooms.push_back(room1);
    Room room2(2, "Small", "Tile", "Available");
    rooms.push_back(room2);
    Room room3(3, "Small", "Tile", "Available");
    rooms.push_back(room3);
    Room room4(4, "Medium", "Carpet", "Available");
    rooms.push_back(room4);
    Room room5(5, "Small", "Tile", "Available");
    rooms.push_back(room5);

    mongo_other.write_rooms(rooms);

    Room room(0, "", "", "");
    robots::Robots temp_robot1(1, "Large", 50, 100, "", "", room, "Scrub", 0);
    mongo_other.write_robot(temp_robot1);
    mongo_other.write_task(1, 3);

    robots::Robots new_task(1, "Large", 40, 60, "", "Complete", room3, "Scrub", 100);

    // robots::Robots canceled_task = mongo_other.read_ongoing_task(1);

    std::vector<robots::Robots> tasks;
    tasks.push_back(new_task);
    mongo_other.update_task_status(tasks);

    robots::Robots canceled_task = mongo_other.read_ongoing_task(1);

    // REQUIRE( total_tasks.size() == 2 );
    // REQUIRE( check == "1" );  
    REQUIRE( canceled_task.get_id() == 1 );  
    REQUIRE( canceled_task.get_size() == "Large" ); 
    REQUIRE( canceled_task.get_water_level() == 40 ); 
    REQUIRE( canceled_task.get_battery_level() == 60 ); 
    REQUIRE( canceled_task.get_function_type() == "Scrub" ); 
    REQUIRE( canceled_task.get_error_status() == "" ); 
    REQUIRE( canceled_task.get_task_status() == "Available" ); 
    REQUIRE( canceled_task.get_task_percent() == 0 ); 
    REQUIRE( canceled_task.get_task_room().getRoomNumber() == 0 );
    REQUIRE( canceled_task.get_task_room().getAvailability() == "" );

    Room room_complete = mongo_other.read_room(3);

    REQUIRE(room_complete.getAvailability() == "Available");

    mongo_other.delete_all_robots();  
    mongo_other.delete_all_tasks();
    mongo_other.delete_rooms();  
}

TEST_CASE("Mongo Adapter Read Error log") {
    mongo_other.delete_error_log();  
    mongo_other.delete_all_robots();  
    mongo_other.delete_all_tasks(); 
    mongo_other.delete_rooms();

    //Write the rooms
    std::vector<Room> rooms;
    Room room1(1, "Small", "Tile", "Available");
    rooms.push_back(room1);
    Room room2(2, "Small", "Tile", "Available");
    rooms.push_back(room2);
    Room room3(3, "Small", "Tile", "Available");
    rooms.push_back(room3);
    Room room4(4, "Medium", "Carpet", "Available");
    rooms.push_back(room4);
    Room room5(5, "Small", "Tile", "Available");
    rooms.push_back(room5);

    mongo_other.write_rooms(rooms);

    Room room(0, "", "", "");
    robots::Robots temp_robot1(1, "Large", 50, 100, "", "", room, "Scrub", 0);
    robots::Robots temp_robot2(2, "Small", 75, 90, "", "", room, "Scrub", 0);
    robots::Robots temp_robot3(3, "Medium", 90, 68, "", "", room, "Scrub", 0);
    mongo_other.write_robot(temp_robot1);
    mongo_other.write_robot(temp_robot2);
    mongo_other.write_robot(temp_robot3);

    mongo_other.write_task(1, 3);
    mongo_other.write_task(2, 2);
    mongo_other.write_task(3, 1);

    std::vector<robots::Robots> updates;
    robots::Robots temp_robot4(1, "Large", 40, 96, "Error", "Ongoing", room3, "Scrub", 10);
    updates.push_back(temp_robot4);

    robots::Robots temp_robot5(2, "Small", 65, 70, "", "Ongoing", room, "Scrub", 20);
    updates.push_back(temp_robot5);

    robots::Robots temp_robot6(3, "Medium", 80, 60, "", "Ongoing", room, "Scrub", 30);
    updates.push_back(temp_robot6);

    mongo_other.update_task_status(updates);

    std::vector<robots::Robots> updates2;
    robots::Robots temp_robot7(1, "Large", 40, 96, "", "Available", room3, "Scrub", 10);
    updates.push_back(temp_robot7);
    mongo_other.write_task(1, 4);

    mongo_other.update_task_status(updates2);

    std::vector<robots::Robots> updates3;
    robots::Robots temp_robot8(1, "Large", 40, 96, "Error", "Available", room4, "Scrub", 10);


    updates3.push_back(temp_robot8);

    mongo_other.update_task_status(updates3);

    std::vector<std::string> error_log = mongo_other.get_error_log(1);
    for(std::string error : error_log){
        std::cout << error << std::endl;
    }
    // REQUIRE( error == "Robot Id: 1, Error Status: Error, Task Percent: 10, Function Type: Scrub, Room Number: 3, Room Size: Small, Room Floor Type: Tile\n" ); 
    mongo_other.delete_error_log();  
    mongo_other.delete_all_robots();  
    mongo_other.delete_all_tasks(); 
    mongo_other.delete_rooms();
}


TEST_CASE("Mongo Adapter Update Status with available robot") {
    mongo_other.delete_all_robots();  
    mongo_other.delete_all_tasks(); 
    mongo_other.delete_rooms();

    //Write the rooms
    std::vector<Room> rooms;
    Room room1(1, "Small", "Tile", "Available");
    rooms.push_back(room1);
    Room room2(2, "Small", "Tile", "Available");
    rooms.push_back(room2);
    Room room3(3, "Small", "Tile", "Available");
    rooms.push_back(room3);
    Room room4(4, "Medium", "Carpet", "Available");
    rooms.push_back(room4);
    Room room5(5, "Small", "Tile", "Available");
    rooms.push_back(room5);

    mongo_other.write_rooms(rooms);

    Room room(0, "", "", "");
    robots::Robots temp_robot1(1, "Large", 50, 100, "", "", room, "Scrub", 0);
    robots::Robots temp_robot2(2, "Small", 75, 90, "", "", room, "Scrub", 0);
    robots::Robots temp_robot3(3, "Medium", 90, 68, "", "", room, "Scrub", 0);
    robots::Robots temp_robot7(4, "Large", 30, 20, "", "Available", room, "Scrub", 0);
    mongo_other.write_robot(temp_robot1);
    mongo_other.write_robot(temp_robot2);
    mongo_other.write_robot(temp_robot3);
    mongo_other.write_robot(temp_robot7);

    mongo_other.write_task(1, 3);
    mongo_other.write_task(2, 2);
    mongo_other.write_task(3, 1);

    std::vector<robots::Robots> updates;

    Room room_3(3, "", "", "");
    robots::Robots temp_robot4(1, "Large", 40, 96, "Error", "Available", room_3, "Scrub", 10);
    updates.push_back(temp_robot4);

    robots::Robots temp_robot5(2, "Small", 65, 70, "", "Ongoing", room2, "Scrub", 20);
    updates.push_back(temp_robot5);

    robots::Robots temp_robot6(3, "Medium", 80, 60, "", "Ongoing", room1, "Scrub", 30);
    updates.push_back(temp_robot6);

    robots::Robots temp_robot8(4, "Large", 20, 10, "", "Available", room, "Scrub", 0);
    updates.push_back(temp_robot8);

    mongo_other.update_task_status(updates);

    robots::Robots update_1 = mongo_other.read_ongoing_task(1);
    REQUIRE( update_1.get_id() == 1);  
    REQUIRE( update_1.get_size() == "Large" ); 
    REQUIRE( update_1.get_water_level() == 40 ); 
    REQUIRE( update_1.get_battery_level() == 96 ); 
    REQUIRE( update_1.get_function_type() == "Scrub" ); 
    REQUIRE( update_1.get_error_status() == "Error" ); 
    REQUIRE( update_1.get_task_status() == "Available" ); 
    REQUIRE( update_1.get_task_percent() == 0 ); 
    REQUIRE( update_1.get_task_room().getRoomNumber() == 0 );
    REQUIRE( update_1.get_task_room().getAvailability() == "" );

    robots::Robots update_2 = mongo_other.read_ongoing_task(2);
    REQUIRE( update_2.get_id() == 2);  
    REQUIRE( update_2.get_size() == "Small" ); 
    REQUIRE( update_2.get_water_level() == 65 ); 
    REQUIRE( update_2.get_battery_level() == 70 ); 
    REQUIRE( update_2.get_function_type() == "Scrub" ); 
    REQUIRE( update_2.get_error_status() == "" ); 
    REQUIRE( update_2.get_task_status() == "Ongoing" ); 
    REQUIRE( update_2.get_task_percent() == 20 ); 
    REQUIRE( update_2.get_task_room().getRoomNumber() == 2 );
    REQUIRE( update_2.get_task_room().getAvailability() == "Busy" );

    robots::Robots update_3 = mongo_other.read_ongoing_task(3);
    REQUIRE( update_3.get_id() == 3);  
    REQUIRE( update_3.get_size() == "Medium" ); 
    REQUIRE( update_3.get_water_level() == 80 ); 
    REQUIRE( update_3.get_battery_level() == 60 ); 
    REQUIRE( update_3.get_function_type() == "Scrub" ); 
    REQUIRE( update_3.get_error_status() == "" ); 
    REQUIRE( update_3.get_task_status() == "Ongoing" ); 
    REQUIRE( update_3.get_task_percent() == 30 ); 
    REQUIRE( update_3.get_task_room().getRoomNumber() == 1 );
    REQUIRE( update_3.get_task_room().getAvailability() == "Busy" );

    //robots::Robots temp_robot8(4, "Large", 20, 10, "", "Available", 0, "Scrub", 0);
    robots::Robots update_4 = mongo_other.read_ongoing_task(4);
    REQUIRE( update_4.get_id() == 4 );  
    REQUIRE( update_4.get_size() == "Large" ); 
    REQUIRE( update_4.get_water_level() == 20 ); 
    REQUIRE( update_4.get_battery_level() == 10 ); 
    REQUIRE( update_4.get_function_type() == "Scrub" ); 
    REQUIRE( update_4.get_error_status() == "" ); 
    REQUIRE( update_4.get_task_status() == "Available" ); 
    REQUIRE( update_4.get_task_percent() == 0 ); 
    REQUIRE( update_4.get_task_room().getRoomNumber() == 0 );
    REQUIRE( update_4.get_task_room().getAvailability() == "" );

    mongo_other.delete_all_robots();  
    mongo_other.delete_all_tasks(); 
    mongo_other.delete_rooms();
}