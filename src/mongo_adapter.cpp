#include "adapters/mongo_adapter.hpp"
#include "robot.hpp"
#include "room.hpp"
#include <memory>
#include <utility>
#include <vector>
#include <string>

#include <bsoncxx/builder/basic/document.hpp>
#include <nlohmann/json.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_array;
using bsoncxx::builder::basic::make_document;
using json = nlohmann::json;

//Store robot and room separately and extract from the robot table
/**
 * Create a Mongo_Adapter instance
 */
adapters::Mongo_Adapter::Mongo_Adapter(){
    // Initialize the instance and mongo db as private variables
}



// Pass by const ref - protects original objects the parameters are the senor or actuator
/**
 * Writes a new robot document to the robot table
 * If the robot table already has a document with that id an exception is thrown
 */
void adapters::Mongo_Adapter::write_robot(const robots::Robots& robot){
    auto result = db_["robot"].find_one(make_document(kvp("_id", robot.get_id())));
    if(result){
        throw std::invalid_argument{ "Duplicate id." };
    }
    // Mongo db will read exampledoc as a rvalue so the doc should be created all in one line 
    // Remove error status, task status and room, and location
    // Write new robot to the "robot" collection
    try{
        db_["robot"].insert_one(make_document(
            kvp("_id", robot.get_id()),
            kvp("size", robot.get_size()),
            kvp("water_level", robot.get_water_level()),
            kvp("battery level", robot.get_battery_level()),
            kvp("Function Type", robot.get_function_type()),
            kvp("Error Status", robot.get_error_status()),
            kvp("Task Status", robot.get_task_status())
        ));
    }
    catch(const std::exception& e){
        std::cout << "Exception in write_robot " << e.what() << std::endl;
    }

}


/**
 * Reads a robot with a given key and outputs the information pertaining to that robot
 * If robot does not exist a string is returned specifying that
 */
robots::Robots adapters::Mongo_Adapter::read_robot(int id) {
    auto result = db_["robot"].find_one(make_document(kvp("_id", id)));
    if (result) {
        try{
            auto information = bsoncxx::to_json(*result);
            json Doc = json::parse(information);

            // Assuming Doc is a JSON object, access fields by their keys.
            auto Id = Doc["_id"];
            auto Size = Doc["size"];
            auto Water_Level = Doc["water_level"];
            auto Battery_Level = Doc["battery level"];
            auto Function_type = Doc["Function Type"];
            auto Error_Status = Doc["Error Status"];
            auto Task_Status = Doc["Task Status"];

            Room room(0, "", "", "");
            robots::Robots new_robot = robots::Robots{Id, Size, Water_Level, Battery_Level, Error_Status, Task_Status, room, Function_type, 0} ;
            
            return new_robot;
        }catch(const std::exception e){
            std::cout << "Exception in read_robot " << e.what() << std::endl;
        }

    } 
    Room room(0, "", "", "");
    robots::Robots new_robot = robots::Robots(id, "", 0, 0, "No instance of robot with id", "", room, "", 0);
    return new_robot;
}

/**
 * Outputs all robots currently in the robot collection
 */
std::vector<robots::Robots> adapters::Mongo_Adapter::read_all_robots(){
    std::vector<robots::Robots> robots = {};
    try{
        auto cursor = db_["robot"].find({});
        for( auto&& doc : cursor) {
            auto information = bsoncxx::to_json(doc);
            json Doc = json::parse(information);
            auto Id = Doc["_id"];
            auto Size = Doc["size"];
            auto Water_Level = Doc["water_level"];
            auto Battery_Level = Doc["battery level"];
            auto Function_type = Doc["Function Type"];
            auto Error_Status = Doc["Error Status"];
            auto Task_Status = Doc["Task Status"];
            
        

        //temporary placeholder to only retrieve "newer" robots that were created with a task status
        if (!Task_Status.is_null())
        {
            Room room(0, "", "", "");
            robots::Robots new_robot = robots::Robots{Id, Size, Water_Level, Battery_Level, Error_Status, Task_Status, room, Function_type, 0};
            robots.push_back(new_robot);
        }
    }
    return robots;
    }catch(const std::exception e){
        std::cout << "Exception in read_all_robots1 " << e.what() << std::endl;
    }

    // for( auto&& doc : cursor) {
    //         auto information = bsoncxx::to_json(doc);
    //         json Doc = json::parse(information);
    //         auto Id = Doc["_id"];
    //         auto Size = Doc["size"];
    //         auto Water_Level = Doc["water_level"];
    //         auto Battery_Level = Doc["battery level"];
    //         auto Function_type = Doc["Function Type"];
    //         auto Error_Status = Doc["Error Status"];
    //         auto Task_Status = Doc["Task Status"];
    //         
        

    //     //temporary placeholder to only retrieve "newer" robots that were created with a task status
    //     if (!Task_Status.is_null())
    //     {
    //         Room room(0, "", "", "");
    //         robots::Robots new_robot = robots::Robots{Id, Size, Water_Level, Battery_Level, Error_Status, Task_Status, room, Function_type, 0};
    //         robots.push_back(new_robot);
    //     }
    // }
    // return robots;
}
    
/**
 * Deletes the robot with the specified robot id
 */
std::string adapters::Mongo_Adapter::delete_robot(int id){
    auto result = db_["robot"].find_one(make_document(kvp("_id", id)));
    if (result) {
        auto information = bsoncxx::to_json(*result);
        auto result = db_["robot"].delete_one(make_document(kvp("_id", id)));
        return information;
    } 
    else{
        return "No instance of robot with id " + std::to_string(id);
    }
}

/**
 * Deletes all the documents in robot as well as the collection
 */
void adapters::Mongo_Adapter::delete_all_robots(){
    db_["robot"].drop( {} );
}

/**
 * Udapte the robot instance in the database with the given water level and battery level
 */
void adapters::Mongo_Adapter::update_robot(int id, int water_level, int battery_level){
    //Create the document with the query
    auto query_filter = make_document(kvp("_id", id));
    auto result = db_["robot"].find_one(make_document(kvp("_id", id)));
    //Create documents with the new battery level and water level
    auto update_doc1 = make_document(kvp("$set", make_document(kvp("battery level", battery_level), kvp("water_level", water_level))));

    //Update the old robot instance in the database
    db_["robot"].update_one(query_filter.view(), update_doc1.view());
}

/**
 * Return a vector of all the ids in the current robot collection
 */
std::vector<int> adapters::Mongo_Adapter::get_all_ids(){
    // Create a new ids vector
    std::vector<int> ids;

    // Loop through every row of the database and add the id parameter into the vector
    auto cursor = db_["robot"].find({});
    for(auto&& doc : cursor) {
        auto information = bsoncxx::to_json(doc);
        json info = json::parse(information);
        auto Id = info["_id"];
        ids.push_back(Id);
    }
    return ids;
}

//Room Functions

/**
 * Write all rooms to the database from a vector of rooms
 */
void adapters::Mongo_Adapter::write_rooms(std::vector<Room> rooms){
    //Write all the rooms to the collection of rooms
    for(Room room : rooms){
        //Write room with id, size, floor type, and Availability
        try{
            db_["room"].insert_one(make_document(
                kvp("Room Id", room.getRoomNumber()),
                kvp("Room Size", room.getRoomSize()),
                kvp("Floor Type", room.getFloorType()),
                kvp("Availability", room.getAvailability())
            ));
        }
        catch(const std::exception& e){
            std::cout << "Exception in write_rooms" << e.what() << std::endl;
        }

    }
}

/**
 * Change a rooms availability to the parameter specified
 */
void adapters::Mongo_Adapter::update_room_availability(int id, std::string availability){
    auto result = db_["room"].find_one(make_document(kvp("Room Id", id)));
    if(result){
        // Find the room to update
        try{
            auto query_filter = make_document(kvp("Room Id", id));
            // Create documents with the new room availability
            auto update_doc1 = make_document(kvp("$set", make_document(kvp("Availability", availability))));
            // Update room
            db_["room"].update_one(query_filter.view(), update_doc1.view());
        }
        catch(const std::exception& e){
            std::cout << "Exception in update_room_availability" << e.what() << std::endl;
        }
    }
}

/**
 * Returns a room object of a specific room from in the database
 */
Room adapters::Mongo_Adapter::read_room(int id){
    //Find the room in the database
    try{
        auto result = db_["room"].find_one(make_document(kvp("Room Id", id)));
        if(result){
            auto information = bsoncxx::to_json(*result);
            json room_Doc = json::parse(information);

            // Assuming Doc is a JSON object, access fields by their keys.
            auto Id = room_Doc["Room Id"];
            auto Size = room_Doc["Room Size"];
            auto Availability = room_Doc["Availability"];
            auto Floor_type = room_Doc["Floor Type"];

            Room room(Id, Size, Floor_type, Availability);
            //return the room
            return room;
            
        // If this room exists create a room with the information in the database
                
        }
        else{
            //If room does not exists return an empty room
            Room room(id, "", "", "No Room with id");
            return room;
        }
    }catch(const std::exception e){
        std::cout << "Exception in read_room1 " << e.what() << std::endl;
    }

    // if(result){
    //         auto information = bsoncxx::to_json(*result);
    //         json room_Doc = json::parse(information);

    //         // Assuming Doc is a JSON object, access fields by their keys.
    //         auto Id = room_Doc["Room Id"];
    //         auto Size = room_Doc["Room Size"];
    //         auto Availability = room_Doc["Availability"];
    //         auto Floor_type = room_Doc["Floor Type"];

    //         Room room(Id, Size, Floor_type, Availability);
    //         //return the room
    //         return room;
    //         
    //     // If this room exists create a room with the information in the database
                
    // }
    // else{
    //     //If room does not exists return an empty room
    //     Room room(id, "", "", "No Room with id");
    //     return room;
    // }
}

/**
 * Delete all rooms from the Database
 */
void adapters::Mongo_Adapter::delete_rooms(){
    db_["room"].drop( {} );
}


/**
 * Read all rooms from the database and return as a vector of rooms
 */
std::vector<Room> adapters::Mongo_Adapter::read_all_rooms(){
    //Read all the rooms from the database
    std::vector<Room> rooms = {};
    
    try{
        auto cursor = db_["room"].find({});
        //Loop through all the rooms in the database
    for( auto&& doc : cursor) {
        
            auto information = bsoncxx::to_json(doc);
            json room_Doc = json::parse(information);

            // Assuming Doc is a JSON object, access fields by their keys.
            auto Id = room_Doc["Room Id"];
            auto Size = room_Doc["Room Size"];
            auto Availability = room_Doc["Availability"];
            auto Floor_type = room_Doc["Floor Type"];

            // Create a room object for the room in the database
            Room room(Id, Size, Floor_type, Availability);

            // Add room to the vector
            rooms.push_back(room);
    }
            
        //Return Rooms
        return rooms;
    }catch(const std::exception e){
        std::cout << "Exception in read_all_rooms1 " << e.what() << std::endl;
    }
    // //Loop through all the rooms in the database
    // for( auto&& doc : cursor) {
    //
    //         auto information = bsoncxx::to_json(doc);
    //         json room_Doc = json::parse(information);

    //         // Assuming Doc is a JSON object, access fields by their keys.
    //         auto Id = room_Doc["Room Id"];
    //         auto Size = room_Doc["Room Size"];
    //         auto Availability = room_Doc["Availability"];
    //         auto Floor_type = room_Doc["Floor Type"];

    //         // Create a room object for the room in the database
    //         Room room(Id, Size, Floor_type, Availability);

    //         // Add room to the vector
    //         rooms.push_back(room);
    //     
    //     
    //  
        
    // }
    // //Return Rooms
    // return rooms;
}


//Task Functions

/**
 * Write task to data base using robot object for the information
 */
void adapters::Mongo_Adapter::write_task(robots::Robots new_task){
    // Make sure the robot is not already doing a task
    auto result = db_["robot"].find_one(make_document(kvp("_id", new_task.get_id()), kvp("Task Status", "Ongoing")));
    auto result1 = db_["room"].find_one(make_document(kvp("Room Id", new_task.get_task_room().getRoomNumber()), kvp("Availability", "Busy")));
    if(result){
        throw std::invalid_argument{ "Robot In Progress of Task" };
    }
    if(result1){
        throw std::invalid_argument{ "Robot In Progress of In Room" };
    }
    // If the robot is not doing task then we should write this new task to a table

    try{
        db_["task"].insert_one(make_document(
                kvp("robot_id", new_task.get_id()),
                kvp("Room", new_task.get_task_room().getRoomNumber()),
                kvp("Error Status", new_task.get_error_status()),
                kvp("Task Status", "Ongoing"),
                kvp("Task Percent", new_task.get_task_percent())
        ));
        
        // Update the robot in the robot class to say that it now has a new task and is busy
        auto query_filter = make_document(kvp("_id", new_task.get_id()));
        // Create documents with the new task status
        auto update_doc1 = make_document(kvp("$set", make_document(kvp("Task Status", "Ongoing"))));
        // Update robot
        db_["robot"].update_one(query_filter.view(), update_doc1.view());
    }
    catch(const std::exception& e){
        std::cout << "Exception in write_task" << e.what() << std::endl;
    }


    //Update room to be unavailable
    update_room_availability(new_task.get_task_room().getRoomNumber(), "Busy");
}

/**
 * Write task to database with a robot id and a room number
 */
void adapters::Mongo_Adapter::write_task(int id, int room){
    // Make sure the robot is not already doing a task
    auto result = db_["robot"].find_one(make_document(kvp("_id", id), kvp("Task Status", "Ongoing")));
    auto result1 = db_["room"].find_one(make_document(kvp("Room Id", room), kvp("Availability", "Busy")));
    if(result){
        throw std::invalid_argument{ "Robot In Progress of Task" };
    }
    if(result1){
        throw std::invalid_argument{ "Robot In Progress of In Room" };
    }

    robots::Robots robot_info = read_robot(id);
    // If the robot is not doing task then we should write this new task to a table
    try{
        db_["task"].insert_one(make_document(
                kvp("robot_id", id),
                kvp("Room", room),
                kvp("Error Status", robot_info.get_error_status()),
                kvp("Task Status", "Ongoing"),
                kvp("Task Percent", 0)
        ));
        
        // Update the robot in the robot class to say that it now has a new task and is busy
        auto query_filter = make_document(kvp("_id", id));
        // Create documents with the new task status
        auto update_doc1 = make_document(kvp("$set", make_document(kvp("Task Status", "Ongoing"))));
        // Update robot
        db_["robot"].update_one(query_filter.view(), update_doc1.view());
    }
    catch(const std::exception& e){
        std::cout << "Exception in write_task2" << e.what() << std::endl;
    }
    
    //Also update the room to unavailable

    //Update room to be unavailable
    update_room_availability(room, "Busy");
}



/**
 * Update the tasks and robots from the robots we got from the simulation and data manager
 */
void adapters::Mongo_Adapter::update_task_status(std::vector<robots::Robots> updates){
    // Update all tasks
    for(robots::Robots update : updates) {
        // Check if this task we want to update has alrady been started and stored
        // It should already be stored because we initially called write_task()
        auto result = db_["task"].find_one(make_document(kvp("robot_id", update.get_id()), kvp("Task Status", "Ongoing")));   
        // else we should just update the robot class if we do not find an ongiong task for this robot update
        if(result){
                auto task_information = bsoncxx::to_json(*result);
                json task_Doc = json::parse(task_information);
                auto Room_Number = task_Doc["Room"];

            //If the robot now has an error
            if(update.get_error_status() != ""){
                //add the error to the error table for safe keeping to grab things later. if we are inquiring about an error log
                try {
                    db_["error"].insert_one(make_document(
                    kvp("robot_id", update.get_id()),
                    kvp("Size", update.get_size()),
                    kvp("Water Level", update.get_water_level()),
                    kvp("Battery Level", update.get_battery_level()),
                    kvp("Function Type", update.get_function_type()),
                    kvp("Error Status", update.get_error_status()),
                    kvp("Room", update.get_task_room().getRoomNumber()),
                    kvp("Task Percent", update.get_task_percent())
                    //add task status
                    ));

                    auto task_query_filter = make_document(kvp("robot_id", update.get_id()), kvp("Task Status", "Ongoing"));

                    // Update the task with updated information
                    auto replace_doc = make_document(kvp("$set", 
                    make_document(
                        kvp("robot_id", update.get_id()),
                        kvp("Room", update.get_task_room().getRoomNumber()),
                        kvp("Error Status", update.get_error_status()),
                        kvp("Task Status", "Cancelled"),
                        kvp("Task Percent", update.get_task_percent())
                        )
                    ));

                    // Update the task
                    db_["task"].update_one(task_query_filter.view(), replace_doc.view());

                    //Update the robot table
                    auto robot_query_filter = make_document(kvp("_id", update.get_id()));
                    auto update_doc = make_document(kvp("$set", make_document(
                        kvp("battery level", update.get_battery_level()), 
                        kvp("water_level", update.get_water_level()),
                        kvp("Task Status", "Available"),
                        kvp("Error Status", update.get_error_status())
                    )));
                    db_["robot"].update_one(robot_query_filter.view(), update_doc.view());
                }
                // catch block to catch the thrown exception
                catch (const std::exception& e) {
                    // print the exception
                    std::cout << "Exception in update task status error" << e.what() << std::endl;
                }
                

                //Update room to now be available
                update_room_availability(Room_Number, "Available");
            }
            else if(update.get_task_percent() == 100 ){
                // Find the specific task to update
                auto task_query_filter = make_document(kvp("robot_id", update.get_id()), kvp("Task Status", "Ongoing"));

                // Make the new task with updated information

                try {
                    auto replace_doc = make_document(kvp("$set", 
                    make_document(
                        kvp("robot_id", update.get_id()),
                        kvp("Room", update.get_task_room().getRoomNumber()),
                        kvp("Error Status", update.get_error_status()),
                        kvp("Task Status", update.get_task_status()),
                        kvp("Task Percent", update.get_task_percent())
                        )
                    ));

                    // Update the task
                    db_["task"].update_one(task_query_filter.view(), replace_doc.view());

                    //Update robot with updated information
                    auto robot_query_filter = make_document(kvp("_id", update.get_id()));
                    auto update_doc = make_document(kvp("$set", make_document(
                        kvp("battery level", update.get_battery_level()), 
                        kvp("water_level", update.get_water_level()),
                        kvp("Task Status", "Available"),
                        kvp("Error Status", update.get_error_status())
                    )));
                    db_["robot"].update_one(robot_query_filter.view(), update_doc.view());
                }
                // catch block to catch the thrown exception
                catch (const std::exception& e) {
                    // print the exception
                    std::cout << "Exception  in complete update task" << e.what() << std::endl;
                }

                //Update the Room availability
                update_room_availability(Room_Number, "Available");

            }
            else if(update.get_task_status() == "Cancelled" && update.get_error_status() == ""){
                // Find the specific task to update
                auto task_query_filter = make_document(kvp("robot_id", update.get_id()), kvp("Task Status", "Ongoing"));

                // Make the new task with updated information

                try {

                    auto replace_doc = make_document(kvp("$set", 
                    make_document(
                        kvp("robot_id", update.get_id()),
                        kvp("Room", update.get_task_room().getRoomNumber()),
                        kvp("Error Status", update.get_error_status()),
                        kvp("Task Status", update.get_task_status()),
                        kvp("Task Percent", update.get_task_percent())
                        )
                    ));

                    // Update the task
                    db_["task"].update_one(task_query_filter.view(), replace_doc.view());

                    // Update robot information
                    auto robot_query_filter = make_document(kvp("_id", update.get_id()));
                    auto update_doc = make_document(kvp("$set", make_document(
                        kvp("battery level", update.get_battery_level()), 
                        kvp("water_level", update.get_water_level()),
                        kvp("Task Status", "Available"),
                        kvp("Error Status", update.get_error_status())
                    )));
                    db_["robot"].update_one(robot_query_filter.view(), update_doc.view());
                }
                // catch block to catch the thrown exception
                catch (const std::exception& e) {
                    // print the exception
                    std::cout << "Exception in cancelled update task " << e.what() << std::endl;
                }

                //Update the Room Availability
                update_room_availability(Room_Number, "Available");
            }
            else{

                try {
                    // Find the specific task to update
                    auto task_query_filter = make_document(kvp("robot_id", update.get_id()), kvp("Task Status", "Ongoing"));

                    // Make the new task with updated information
                    auto replace_doc = make_document(kvp("$set", 
                    make_document(
                        kvp("robot_id", update.get_id()),
                        kvp("Room", update.get_task_room().getRoomNumber()),
                        kvp("Error Status", update.get_error_status()),
                        kvp("Task Status", update.get_task_status()),
                        kvp("Task Percent", update.get_task_percent())
                        )
                    ));

                    // Update the task
                    db_["task"].update_one(task_query_filter.view(), replace_doc.view());
                    
                    // Update robot information
                    auto robot_query_filter = make_document(kvp("_id", update.get_id()));
                    auto update_doc = make_document(kvp("$set", make_document(
                        kvp("battery level", update.get_battery_level()), 
                        kvp("water_level", update.get_water_level()),
                        kvp("Task Status", update.get_task_status()),
                        kvp("Error Status", update.get_error_status())
                    )));
                    db_["robot"].update_one(robot_query_filter.view(), update_doc.view());
                }
                // catch block to catch the thrown exception
                catch (const std::exception& e) {
                    // print the exception
                    std::cout << "Exception in else 1 update task " << e.what() << std::endl;
                }
                

                //Room should still be unavailiable because the only things that are in the else statement are ongoing tasks
                update_room_availability(Room_Number, "Busy");
            }
        }else{

                try {
                    auto robot_query_filter = make_document(kvp("_id", update.get_id()));
                    auto update_doc = make_document(kvp("$set", make_document(
                        kvp("battery level", update.get_battery_level()), 
                        kvp("water_level", update.get_water_level()),
                        kvp("Task Status", update.get_task_status()),
                        kvp("Error Status", update.get_error_status())
                    )));
                    db_["robot"].update_one(robot_query_filter.view(), update_doc.view());
                }
                // catch block to catch the thrown exception
                catch (const std::exception& e) {
                    // print the exception
                    std::cout << "Exception in else 2 update task status " << e.what() << std::endl;
                }
            // If the robot task is available and not ongoing then just update the robot class as only the water and battery level are changing
            
            //No need to update room because these robots are charging and not a part of an ongoing tasks attached to a room
        }
    }
}

/**
 * Read ongoing task of a specific robot
 */
robots::Robots adapters::Mongo_Adapter::read_ongoing_task(int id){
    //Find the ongoing task for the specific robot
    try{
        auto task_result = db_["task"].find_one(make_document(kvp("robot_id", id), kvp("Task Status", "Ongoing"))); 
        if (task_result) {
        
            //If there is an ongoing task then create a robot with all the data specific to the task and robot
            auto task_information = bsoncxx::to_json(*task_result);
            json task_Doc = json::parse(task_information);

            robots::Robots robot_info = read_robot(id);

            // Assuming Doc is a JSON object, access fields by their keys.
            auto Id = task_Doc["robot_id"];
            auto Room_Number = task_Doc["Room"];
            auto Function_type = robot_info.get_function_type();
            auto Error_Status = task_Doc["Error Status"];
            auto Task_Status = task_Doc["Task Status"];
            auto Task_Percent = task_Doc["Task Percent"];
            auto Size = robot_info.get_size();
            auto Water_Level = robot_info.get_water_level();
            auto Battery_Level = robot_info.get_battery_level();

            Room room = read_room(Room_Number);
            robots::Robots new_robot = robots::Robots{Id, Size, Water_Level, Battery_Level, Error_Status, Task_Status, room, Function_type, Task_Percent} ;
            
            return new_robot;
       
        
    } 
    else{
        //If there is no ongoing task read info from just the robot table
        robots::Robots robot_info = read_robot(id);

        auto Size = robot_info.get_size();

        auto Water_Level = robot_info.get_water_level();
        auto Battery_Level = robot_info.get_battery_level();
        auto Function_type = robot_info.get_function_type();
        auto Task_Status = robot_info.get_task_status();
        auto Error_Status = robot_info.get_error_status();
        Room room(0, "", "", "");
        robots::Robots new_robot = robots::Robots(id, Size, Water_Level, Battery_Level, Error_Status, Task_Status, room, Function_type, 0);
        return new_robot;
    }
    }catch(const std::exception e){
        std::cout << "Exception in read_ongoing_tasks" << e.what() << std::endl;
    }
   
    // if (task_result) {
        
    //         //If there is an ongoing task then create a robot with all the data specific to the task and robot
    //         auto task_information = bsoncxx::to_json(*task_result);
    //         json task_Doc = json::parse(task_information);

    //         robots::Robots robot_info = read_robot(id);

    //         // Assuming Doc is a JSON object, access fields by their keys.
    //         auto Id = task_Doc["robot_id"];
    //         auto Room_Number = task_Doc["Room"];
    //         auto Function_type = robot_info.get_function_type();
    //         auto Error_Status = task_Doc["Error Status"];
    //         auto Task_Status = task_Doc["Task Status"];
    //         auto Task_Percent = task_Doc["Task Percent"];
    //         auto Size = robot_info.get_size();
    //         auto Water_Level = robot_info.get_water_level();
    //         auto Battery_Level = robot_info.get_battery_level();

    //         Room room = read_room(Room_Number);
    //         robots::Robots new_robot = robots::Robots{Id, Size, Water_Level, Battery_Level, Error_Status, Task_Status, room, Function_type, Task_Percent} ;
            
    //         return new_robot;
       
        
    // } 
    // else{
    //     //If there is no ongoing task read info from just the robot table
    //     robots::Robots robot_info = read_robot(id);

    //     auto Size = robot_info.get_size();

    //     auto Water_Level = robot_info.get_water_level();
    //     auto Battery_Level = robot_info.get_battery_level();
    //     auto Function_type = robot_info.get_function_type();
    //     auto Task_Status = robot_info.get_task_status();
    //     auto Error_Status = robot_info.get_error_status();
    //     Room room(0, "", "", "");
    //     robots::Robots new_robot = robots::Robots(id, Size, Water_Level, Battery_Level, Error_Status, Task_Status, room, Function_type, 0);
    //     return new_robot;
    // }
}


 /**
  * Read all ongoing tasks of all the robots
  */
std::vector<robots::Robots> adapters::Mongo_Adapter::read_all_ongoing_tasks(){
    std::vector<robots::Robots> ongoing_tasks;
    try{
        auto cursor = db_["task"].find(make_document(kvp("Task Status", "Ongoing")));
        for( auto&& doc : cursor) {
        
            auto task_information = bsoncxx::to_json(doc);
            json task_Doc = json::parse(task_information);

            // Assuming Doc is a JSON object, access fields by their keys.
            auto Id = task_Doc["robot_id"];
            robots::Robots robot_info = read_robot(Id);
            auto Room_Number = task_Doc["Room"];
            auto Function_type = robot_info.get_function_type();
            auto Error_Status = task_Doc["Error Status"];
            auto Task_Status = task_Doc["Task Status"];
            auto Task_Percent = task_Doc["Task Percent"];
            auto Size = robot_info.get_size();
            auto Water_Level = robot_info.get_water_level();
            auto Battery_Level = robot_info.get_battery_level();

            Room room = read_room(Room_Number);
            robots::Robots new_task = robots::Robots{Id, Size, Water_Level, Battery_Level, Error_Status, Task_Status, room, Function_type, Task_Percent} ;
            ongoing_tasks.push_back(new_task);
        
        
    }
    return ongoing_tasks;
    }catch(const std::exception e){
        std::cout << "Exception in read_all_ongoing_tasks " << e.what() << std::endl;
    }
    // for( auto&& doc : cursor) {
        
    //         auto task_information = bsoncxx::to_json(doc);
    //         json task_Doc = json::parse(task_information);

    //         // Assuming Doc is a JSON object, access fields by their keys.
    //         auto Id = task_Doc["robot_id"];
    //         robots::Robots robot_info = read_robot(Id);
    //         auto Room_Number = task_Doc["Room"];
    //         auto Function_type = robot_info.get_function_type();
    //         auto Error_Status = task_Doc["Error Status"];
    //         auto Task_Status = task_Doc["Task Status"];
    //         auto Task_Percent = task_Doc["Task Percent"];
    //         auto Size = robot_info.get_size();
    //         auto Water_Level = robot_info.get_water_level();
    //         auto Battery_Level = robot_info.get_battery_level();

    //         Room room = read_room(Room_Number);
    //         robots::Robots new_task = robots::Robots{Id, Size, Water_Level, Battery_Level, Error_Status, Task_Status, room, Function_type, Task_Percent} ;
    //         ongoing_tasks.push_back(new_task);
        
        
    // }
    // return ongoing_tasks;
}

/**
 * Read all the tasks a robot has done and are ongoing
 */
std::vector<robots::Robots> adapters::Mongo_Adapter::read_robot_tasks(int id){
    try{
        auto cursor = db_["task"].find(make_document(kvp("robot_id", id)));
        std::vector<robots::Robots> tasks;

    // auto robot_result = db_["robot"].find_one(make_document(kvp("_id", id))); 
    for( auto&& doc : cursor) {
        
            auto task_information = bsoncxx::to_json(doc);
            json task_Doc = json::parse(task_information);


            // Assuming Doc is a JSON object, access fields by their keys.
            auto Id = task_Doc["robot_id"];
            robots::Robots robot_info = read_robot(Id);
            auto Room_Number = task_Doc["Room"];
            auto Function_type = robot_info.get_function_type();
            auto Error_Status = task_Doc["Error Status"];
            auto Task_Status = task_Doc["Task Status"];
            auto Task_Percent = task_Doc["Task Percent"];
            auto Size = robot_info.get_size();
            auto Water_Level = robot_info.get_water_level();
            auto Battery_Level = robot_info.get_battery_level();
        
        

        Room room = read_room(Room_Number);
        robots::Robots new_task = robots::Robots{Id, Size, Water_Level, Battery_Level, Error_Status, Task_Status, room, Function_type, Task_Percent} ;
        tasks.push_back(new_task);
    }
    return tasks;
    }catch(const std::exception e){
        std::cout << "Exception in read_robot_tasks " << e.what() << std::endl;
    }
    
}

/**
 * Read all tasks from the task table
 */
std::vector<robots::Robots> adapters::Mongo_Adapter::read_all_tasks(){
    //Vector to have all the tasks of a specific robot
    std::vector<robots::Robots> all_tasks;
    try{
        auto cursor = db_["task"].find({});
        for( auto&& doc : cursor) {
        
            auto task_information = bsoncxx::to_json(doc);
            json task_Doc = json::parse(task_information);
            

            // Assuming Doc is a JSON object, access fields by their keys.
            auto Id = task_Doc["robot_id"];
            robots::Robots robot_info = read_robot(Id);
            auto Room_Number = task_Doc["Room"];
            auto Function_type = robot_info.get_function_type();
            auto Error_Status = task_Doc["Error Status"];
            auto Task_Status = task_Doc["Task Status"];
            auto Task_Percent = task_Doc["Task Percent"];
            auto Size = robot_info.get_size();
            auto Water_Level = robot_info.get_water_level();
            auto Battery_Level = robot_info.get_battery_level();

            Room room = read_room(Room_Number);
            robots::Robots new_task = robots::Robots{Id, Size, Water_Level, Battery_Level, Error_Status, Task_Status, room, Function_type, Task_Percent} ;
            all_tasks.push_back(new_task);
        
            
        
        
    }
    return all_tasks;
    }catch(const std::exception e){
        std::cout << "Exception in read_robot " << e.what() << std::endl;
    }
    
    //Loop through all the tasks of the robot
    // for( auto&& doc : cursor) {
        
    //         auto task_information = bsoncxx::to_json(doc);
    //         json task_Doc = json::parse(task_information);
            

    //         // Assuming Doc is a JSON object, access fields by their keys.
    //         auto Id = task_Doc["robot_id"];
    //         robots::Robots robot_info = read_robot(Id);
    //         auto Room_Number = task_Doc["Room"];
    //         auto Function_type = robot_info.get_function_type();
    //         auto Error_Status = task_Doc["Error Status"];
    //         auto Task_Status = task_Doc["Task Status"];
    //         auto Task_Percent = task_Doc["Task Percent"];
    //         auto Size = robot_info.get_size();
    //         auto Water_Level = robot_info.get_water_level();
    //         auto Battery_Level = robot_info.get_battery_level();

    //         Room room = read_room(Room_Number);
    //         robots::Robots new_task = robots::Robots{Id, Size, Water_Level, Battery_Level, Error_Status, Task_Status, room, Function_type, Task_Percent} ;
    //         all_tasks.push_back(new_task);
        
    //         std::cout << "Exception in read_robot " << e.what() << std::endl;
        
        
    // }
    // return all_tasks;
}

/**
 * Delete the entire task table
 */
void adapters::Mongo_Adapter::delete_all_tasks(){
    db_["task"].drop( {} );
}


/**
 * Return the error log for a specific robot
 */
std::vector<std::string> adapters::Mongo_Adapter::get_error_log(int id){
    std::vector<std::string> error_log;
    try{
        auto cursor = db_["error"].find(make_document(kvp("robot_id", id)));
        //Loop through all the tasks of the robot
    for( auto&& doc : cursor) {
        
            auto error_information = bsoncxx::to_json(doc);
            json error_Doc = json::parse(error_information);
            

            // Assuming Doc is a JSON object, access fields by their keys.
            auto Id = error_Doc["robot_id"];
            auto Room_Number = error_Doc["Room"];
            std::string Function_type = error_Doc["Function Type"];
            std::string Error_Status = error_Doc["Error Status"];
            auto Task_Percent = error_Doc["Task Percent"];
            std::string Size = error_Doc["Size"];
            auto Water_Level = error_Doc["Water Level"];
            auto Battery_Level = error_Doc["Battery Level"];

            Room room = read_room(Room_Number);
            std::string new_error = "Robot Id: " + to_string(Id) + ", Error Status: " + Error_Status + ", Task Percent: " + to_string(Task_Percent) + ", Function Type: " + Function_type + ", Room Number: " + to_string(Room_Number) + ", Room Size: " + room.getRoomSize() + ", Room Floor Type: "+ room.getFloorType();
            error_log.push_back(new_error);
        
            
        
        
    }

    return error_log;
    }catch(const std::exception e){
        std::cout << "Exception in get_error_log " << e.what() << std::endl;
    }

    
}

//Delete the error log
void adapters::Mongo_Adapter::delete_error_log(){
    db_["error"].drop( {} );
}
