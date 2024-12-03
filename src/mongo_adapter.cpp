#include "adapters/mongo_adapter.hpp"
#include "robot.hpp"
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

/**
 * Reads a robot with a given key and outputs the information pertaining to that robot
 * If robot does not exist a string is returned specifying that
 */
robots::Robots adapters::Mongo_Adapter::read_robot(int id) {
    auto result = db_["robot"].find_one(make_document(kvp("_id", id)));
    if (result) {
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

        robots::Robots new_robot = robots::Robots{Id, Size, Water_Level, Battery_Level, Error_Status, Task_Status, 0, Function_type, 0} ;
        
        return new_robot;
    } 
    std::cout << "No instance of robot with id " << id << std::endl;
    robots::Robots new_robot = robots::Robots(id, "", 0, 0, "No instance of robot with id", "", 0, "", 0);
    return new_robot;
}

/**
 * Outputs all robots currently in the robot collection
 */
std::vector<robots::Robots> adapters::Mongo_Adapter::read_all_robots(){
    std::vector<robots::Robots> robots = {};
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

        robots::Robots new_robot = robots::Robots{Id, Size, Water_Level, Battery_Level, Error_Status, Task_Status, 0, Function_type, 0};
        robots.push_back(new_robot);
    }
    return robots;
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
        std::cout << "No instance of robot with id " << id << std::endl;
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


/**
 * Write task to data base using robot object for the information
 */
void adapters::Mongo_Adapter::write_task(robots::Robots new_task){
    // Make sure the robot is not already doing a task
    auto result = db_["robot"].find_one(make_document(kvp("_id", new_task.get_id()), kvp("Task Status", "Ongoing")));
    if(result){
        throw std::invalid_argument{ "Robot In Progress of Task" };
    }
    // If the robot is not doing task then we should write this new task to a table
    db_["task"].insert_one(make_document(
                kvp("robot_id", new_task.get_id()),
                kvp("Room", new_task.get_task_room()),
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

/**
 * Write task to database with a robot id and a room number
 */
void adapters::Mongo_Adapter::write_task(int id, int room){
    // Make sure the robot is not already doing a task
    auto result = db_["robot"].find_one(make_document(kvp("_id", id), kvp("Task Status", "Ongoing")));
    if(result){
        throw std::invalid_argument{ "Robot In Progress of Task" };
    }

    robots::Robots robot_info = read_robot(id);
    // If the robot is not doing task then we should write this new task to a table
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
            //If the robot now has an error
            if(update.get_error_status() != ""){

                //add the error to the error table for safe keeping to grab things later. if we are inquiring about an error log
                db_["error"].insert_one(make_document(
                    kvp("robot_id", update.get_id()),
                    kvp("Size", update.get_size()),
                    kvp("Water Level", update.get_water_level()),
                    kvp("Battery Level", update.get_battery_level()),
                    kvp("Function Type", update.get_function_type()),
                    kvp("Error Status", update.get_error_status()),
                    kvp("Room", update.get_task_room()),
                    kvp("Task Percent", update.get_task_percent())
                    //add task status
                ));

                auto task_query_filter = make_document(kvp("robot_id", update.get_id()), kvp("Task Status", "Ongoing"));

                // Update the task with updated information
                auto replace_doc = make_document(kvp("$set", 
                make_document(
                    kvp("robot_id", update.get_id()),
                    kvp("Room", update.get_task_room()),
                    kvp("Error Status", update.get_error_status()),
                    kvp("Task Status", update.get_task_status()),
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
            else if(update.get_task_status() == "Complete" ){
                // Find the specific task to update
                auto task_query_filter = make_document(kvp("robot_id", update.get_id()), kvp("Task Status", "Ongoing"));

                // Make the new task with updated information
                auto replace_doc = make_document(kvp("$set", 
                make_document(
                    kvp("robot_id", update.get_id()),
                    kvp("Room", update.get_task_room()),
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
            else if(update.get_task_status() == "Cancelled" && update.get_error_status() == ""){
                // Find the specific task to update
                auto task_query_filter = make_document(kvp("robot_id", update.get_id()), kvp("Task Status", "Ongoing"));

                // Make the new task with updated information
                auto replace_doc = make_document(kvp("$set", 
                make_document(
                    kvp("robot_id", update.get_id()),
                    kvp("Room", update.get_task_room()),
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
            else{
                std::cout << "in available" << std::endl;
                // Find the specific task to update
                auto task_query_filter = make_document(kvp("robot_id", update.get_id()), kvp("Task Status", "Ongoing"));

                // Make the new task with updated information
                std::cout << update.get_water_level() << std::endl;
                auto replace_doc = make_document(kvp("$set", 
                make_document(
                    kvp("robot_id", update.get_id()),
                    kvp("Room", update.get_task_room()),
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
        }else{
            // If the robot task is available and not ongoing then just update the robot class as only the water and battery level are changing
            auto robot_query_filter = make_document(kvp("_id", update.get_id()));
            auto update_doc = make_document(kvp("$set", make_document(
                kvp("battery level", update.get_battery_level()), 
                kvp("water_level", update.get_water_level()),
                kvp("Task Status", update.get_task_status()),
                kvp("Error Status", update.get_error_status())
            )));
            db_["robot"].update_one(robot_query_filter.view(), update_doc.view());
        }
    }
}

/**
 * Read ongoing task of a specific robot
 */
robots::Robots adapters::Mongo_Adapter::read_ongoing_task(int id){
    auto task_result = db_["task"].find_one(make_document(kvp("robot_id", id), kvp("Task Status", "Ongoing"))); 
    if (task_result) {
        auto task_information = bsoncxx::to_json(*task_result);
        json task_Doc = json::parse(task_information);

        robots::Robots robot_info = read_robot(id);

        // Assuming Doc is a JSON object, access fields by their keys.
        auto Id = task_Doc["robot_id"];
        auto Room = task_Doc["Room"];
        auto Function_type = robot_info.get_function_type();
        auto Error_Status = task_Doc["Error Status"];
        auto Task_Status = task_Doc["Task Status"];
        auto Task_Percent = task_Doc["Task Percent"];
        auto Size = robot_info.get_size();
        auto Water_Level = robot_info.get_water_level();
        auto Battery_Level = robot_info.get_battery_level();


        robots::Robots new_robot = robots::Robots{Id, Size, Water_Level, Battery_Level, Error_Status, Task_Status, Room, Function_type, Task_Percent} ;
        
        return new_robot;
    } 
    else{
        //If there is no ongoing task read info from just the robot table
        robots::Robots robot_info = read_robot(id);

        auto Size = robot_info.get_size();

        auto Water_Level = robot_info.get_water_level();
        std::cout << Water_Level << std::endl;
        auto Battery_Level = robot_info.get_battery_level();
        std::cout << Battery_Level << std::endl;
        auto Function_type = robot_info.get_function_type();
        std::cout << Function_type << std::endl;
        auto Task_Status = robot_info.get_task_status();
        std::cout << Task_Status << std::endl;
        robots::Robots new_robot = robots::Robots(id, Size, Water_Level, Battery_Level, "", Task_Status, 0, Function_type, 0);
        return new_robot;
    }
}
 /**
  * Read all ongoing tasks of all the robots
  */
std::vector<robots::Robots> adapters::Mongo_Adapter::read_all_ongoing_tasks(){
    std::vector<robots::Robots> ongoing_tasks;
    auto cursor = db_["task"].find(make_document(kvp("Task Status", "Ongoing")));
    for( auto&& doc : cursor) {
        auto task_information = bsoncxx::to_json(doc);
        json task_Doc = json::parse(task_information);

        // Assuming Doc is a JSON object, access fields by their keys.
        auto Id = task_Doc["robot_id"];
        robots::Robots robot_info = read_robot(Id);
        auto Room = task_Doc["Room"];
        auto Function_type = robot_info.get_function_type();
        auto Error_Status = task_Doc["Error Status"];
        auto Task_Status = task_Doc["Task Status"];
        auto Task_Percent = task_Doc["Task Percent"];
        auto Size = robot_info.get_size();
        auto Water_Level = robot_info.get_water_level();
        auto Battery_Level = robot_info.get_battery_level();


        robots::Robots new_task = robots::Robots{Id, Size, Water_Level, Battery_Level, Error_Status, Task_Status, Room, Function_type, Task_Percent} ;
        ongoing_tasks.push_back(new_task);
    }
    return ongoing_tasks;
}

/**
 * Read all the tasks a robot has done and are ongoing
 */
std::vector<robots::Robots> adapters::Mongo_Adapter::read_robot_tasks(int id){
    std::vector<robots::Robots> tasks;
    auto cursor = db_["task"].find(make_document(kvp("robot_id", id)));
    // auto robot_result = db_["robot"].find_one(make_document(kvp("_id", id))); 
    for( auto&& doc : cursor) {
        auto task_information = bsoncxx::to_json(doc);
        json task_Doc = json::parse(task_information);


        // Assuming Doc is a JSON object, access fields by their keys.
        auto Id = task_Doc["robot_id"];
        robots::Robots robot_info = read_robot(Id);
        auto Room = task_Doc["Room"];
        auto Function_type = robot_info.get_function_type();
        auto Error_Status = task_Doc["Error Status"];
        auto Task_Status = task_Doc["Task Status"];
        auto Task_Percent = task_Doc["Task Percent"];
        auto Size = robot_info.get_size();
        auto Water_Level = robot_info.get_water_level();
        auto Battery_Level = robot_info.get_battery_level();


        robots::Robots new_task = robots::Robots{Id, Size, Water_Level, Battery_Level, Error_Status, Task_Status, Room, Function_type, Task_Percent} ;
        tasks.push_back(new_task);
    }
    return tasks;
}

/**
 * Read all tasks from the task table
 */
std::vector<robots::Robots> adapters::Mongo_Adapter::read_all_tasks(){
    //Vector to have all the tasks of a specific robot
    std::vector<robots::Robots> all_tasks;
    auto cursor = db_["task"].find({});
    //Loop through all the tasks of the robot
    for( auto&& doc : cursor) {
        auto task_information = bsoncxx::to_json(doc);
        json task_Doc = json::parse(task_information);
        

        // Assuming Doc is a JSON object, access fields by their keys.
        auto Id = task_Doc["robot_id"];
        robots::Robots robot_info = read_robot(Id);
        auto Room = task_Doc["Room"];
        auto Function_type = robot_info.get_function_type();
        auto Error_Status = task_Doc["Error Status"];
        auto Task_Status = task_Doc["Task Status"];
        auto Task_Percent = task_Doc["Task Percent"];
        auto Size = robot_info.get_size();
        auto Water_Level = robot_info.get_water_level();
        auto Battery_Level = robot_info.get_battery_level();


        robots::Robots new_task = robots::Robots{Id, Size, Water_Level, Battery_Level, Error_Status, Task_Status, Room, Function_type, Task_Percent} ;
        all_tasks.push_back(new_task);
    }
    return all_tasks;
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
std::string adapters::Mongo_Adapter::get_error_log(int id){
    auto cursor = db_["error"].find(make_document(kvp("robot_id", id)));
    //Loop through all the tasks of the robot
    std::string error_log;
    for( auto&& doc : cursor) {
        auto error_information = bsoncxx::to_json(doc);
        json error_Doc = json::parse(error_information);
        

        // Assuming Doc is a JSON object, access fields by their keys.
        auto Id = error_Doc["robot_id"];
        auto Room = error_Doc["Room"];
        std::string Function_type = error_Doc["Function Type"];
        std::string Error_Status = error_Doc["Error Status"];
        auto Task_Percent = error_Doc["Task Percent"];
        std::string Size = error_Doc["Size"];
        auto Water_Level = error_Doc["Water Level"];
        auto Battery_Level = error_Doc["Battery Level"];

        std::string new_error = "Robot Id: " + to_string(Id) + ", Error Status: " + Error_Status + ", Task Percent: " + to_string(Task_Percent) + ", Function Type: " + Function_type + ", Room: " + to_string(Room) + "\n";
        error_log = error_log + new_error;
    }

    return error_log;
}

//Delete the error log
void adapters::Mongo_Adapter::delete_error_log(){
    db_["error"].drop( {} );
}
