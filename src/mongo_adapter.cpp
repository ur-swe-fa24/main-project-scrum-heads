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
        //add task status
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
    std::vector<robots::Robots> robots;
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
                //add task status
    ));
    
    // Update the robot in the robot class to say that it now has a new task and is busy
    auto query_filter = make_document(kvp("_id", new_task.get_id()));
    // Create documents with the new task status
    auto update_doc1 = make_document(kvp("$set", make_document(kvp("Task Status", "Ongoing"))));
    // Update robot
    db_["robot"].update_one(query_filter.view(), update_doc1.view());

}

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
                //add task status
    ));
    
    // Update the robot in the robot class to say that it now has a new task and is busy
    auto query_filter = make_document(kvp("_id", id));
    // Create documents with the new task status
    auto update_doc1 = make_document(kvp("$set", make_document(kvp("Task Status", "Ongoing"))));
    // Update robot
    db_["robot"].update_one(query_filter.view(), update_doc1.view());

}

void adapters::Mongo_Adapter::update_task_status(std::vector<robots::Robots> updates){
    // Update all tasks
    for(robots::Robots update : updates) {
        // Check if this task we want to update has alrady been started and stored
        // It should already be stored because we initially called write_task()
        auto result = db_["task"].find_one(make_document(kvp("robot_id", update.get_id()), kvp("Task Status", "Ongoing")));   
       if(result){
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

            // Update the Robot in the Robot class
            auto robot_query_filter = make_document(kvp("_id", update.get_id()));
            auto update_doc = make_document(kvp("$set", make_document(
                kvp("battery level", update.get_battery_level()), 
                kvp("water_level", update.get_water_level()),
                kvp("Task Status", update.get_task_status()), 
                kvp("Task Percent", update.get_task_percent())
            )));
            db_["robot"].update_one(robot_query_filter.view(), update_doc.view());
        }
        // else{
        //     // db_["task"].insert_one(make_document(
        //     //     kvp("robot_id", update.get_id()),
        //     //     kvp("Room", update.get_room()),
        //     //     kvp("Error Status", update.get_error_status()),
        //     //     kvp("Task Status", update.get_task_status()),
        //     //     kvp("Task Percent", update.get_task_percent())
        //     //     //add task status
        //     // ));
        // }
        // auto information = bsoncxx::to_json(doc);
        // json info = json::parse(information);
        // auto Id = info["_id"];
        // ids.push_back(Id);
    }
}

robots::Robots adapters::Mongo_Adapter::read_ongoing_task(int id){
    auto task_result = db_["task"].find_one(make_document(kvp("robot_id", id), kvp("Task Status", "Ongoing"))); 
    // auto robot_result = db_["robot"].find_one(make_document(kvp("robot_id", id))); 
    if (task_result) {
        auto task_information = bsoncxx::to_json(*task_result);
        json task_Doc = json::parse(task_information);

        robots::Robots robot_info = read_robot(id);
        // auto robot_information = bsoncxx::to_json(*robot_result);
        // json robot_Doc = json::parse(robot_information);

        // Assuming Doc is a JSON object, access fields by their keys.
        auto Id = task_Doc["robot_id"];
        // std::cout << Id << std::endl;
        auto Room = task_Doc["Room"];
        // std::cout << Room << std::endl;
        auto Function_type = robot_info.get_function_type();
        // std::cout << Function_type << std::endl;
        auto Error_Status = task_Doc["Error Status"];
        // std::cout << Error_Status << std::endl;
        auto Task_Status = task_Doc["Task Status"];
        // std::cout << Task_Status << std::endl;
        auto Task_Percent = task_Doc["Task Percent"];
        // std::cout << Task_Percent << std::endl;
        auto Size = robot_info.get_size();
        // std::cout << Size << std::endl;
        auto Water_Level = robot_info.get_water_level();
        // std::cout << Water_Level << std::endl;
        auto Battery_Level = robot_info.get_battery_level();
        // std::cout << Battery_Level << std::endl;


        robots::Robots new_robot = robots::Robots{Id, Size, Water_Level, Battery_Level, Error_Status, Task_Status, Room, Function_type, Task_Percent} ;
        
        return new_robot;
    } 
    else{
        robots::Robots new_robot = robots::Robots(id, "", 0, 0, "No instance of ongoing task with robot id", "", 0, "", 0);
        return new_robot;
    }
}

std::vector<robots::Robots> adapters::Mongo_Adapter::read__all_ongoing_tasks(){
    std::vector<robots::Robots> ongoing_tasks;
    auto cursor = db_["task"].find(make_document(kvp("Task Status", "Ongoing")));
    for( auto&& doc : cursor) {
        auto task_information = bsoncxx::to_json(doc);
        json task_Doc = json::parse(task_information);

        // auto robot_information = bsoncxx::to_json(*robot_result);
        // json robot_Doc = json::parse(robot_information);

        // Assuming Doc is a JSON object, access fields by their keys.
        auto Id = task_Doc["robot_id"];
        robots::Robots robot_info = read_robot(Id);
        // std::cout << Id << std::endl;
        auto Room = task_Doc["Room"];
        // std::cout << Room << std::endl;
        auto Function_type = robot_info.get_function_type();
        // std::cout << Function_type << std::endl;
        auto Error_Status = task_Doc["Error Status"];
        // std::cout << Error_Status << std::endl;
        auto Task_Status = task_Doc["Task Status"];
        // std::cout << Task_Status << std::endl;
        auto Task_Percent = task_Doc["Task Percent"];
        // std::cout << Task_Percent << std::endl;
        auto Size = robot_info.get_size();
        // std::cout << Size << std::endl;
        auto Water_Level = robot_info.get_water_level();
        // std::cout << Water_Level << std::endl;
        auto Battery_Level = robot_info.get_battery_level();
        // std::cout << Battery_Level << std::endl;


        robots::Robots new_task = robots::Robots{Id, Size, Water_Level, Battery_Level, Error_Status, Task_Status, Room, Function_type, Task_Percent} ;
        ongoing_tasks.push_back(new_task);
    }
    return ongoing_tasks;
}

std::vector<robots::Robots> adapters::Mongo_Adapter::read_robot_tasks(int id){
    std::vector<robots::Robots> tasks;
    auto cursor = db_["task"].find(make_document(kvp("robot_id", id)));
    // auto robot_result = db_["robot"].find_one(make_document(kvp("_id", id))); 
    for( auto&& doc : cursor) {
        auto task_information = bsoncxx::to_json(doc);
        json task_Doc = json::parse(task_information);

        // auto robot_information = bsoncxx::to_json(*robot_result);
        // json robot_Doc = json::parse(robot_information);

        // Assuming Doc is a JSON object, access fields by their keys.
        auto Id = task_Doc["robot_id"];
        auto Room = task_Doc["Room"];
        // auto Function_type = robot_Doc["Function Type"];
        auto Error_Status = task_Doc["Error Status"];
        auto Task_Status = task_Doc["Task Status"];
        auto Task_Percent = task_Doc["Task Percent"];
        // auto Size = robot_Doc["size"];
        // auto Water_Level = robot_Doc["water_level"];
        // auto Battery_Level = robot_Doc["battery level"];


        robots::Robots new_task = robots::Robots{Id, "Size", 0, 0, Error_Status, Task_Status, Room, "Function_type", Task_Percent} ;
        tasks.push_back(new_task);
    }
    return tasks;
}


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
        auto Room = task_Doc["Room"];
        auto Error_Status = task_Doc["Error Status"];
        auto Task_Status = task_Doc["Task Status"];
        auto Task_Percent = task_Doc["Task Percent"];


        robots::Robots new_task = robots::Robots{Id, "Size", 0, 0, Error_Status, Task_Status, Room, "Function_type", Task_Percent} ;
        all_tasks.push_back(new_task);
    }
    return all_tasks;
}

std::string adapters::Mongo_Adapter::cancel_task(int id){
    auto task_result = db_["task"].find_one(make_document(kvp("robot_id", id), kvp("Task Status", "Ongoing"))); 
    if (task_result) {
        auto task_query_filter = make_document(kvp("_id", id), kvp("Task Status", "Ongoing"));
        auto update_doc = make_document(kvp("$set", make_document(
            kvp("Task Status", "Complete")
        )));
        db_["task"].update_one(task_query_filter.view(), update_doc.view());
        auto robot_query_filter = make_document(kvp("_id", id));
        auto update_doc2 = make_document(kvp("$set", make_document(
            kvp("Task Status", "Complete")
        )));
        db_["robot"].update_one(task_query_filter.view(), update_doc2.view());
        return "1";
    } 
    else{
        std::cout << "No instance of robot with id " << id << std::endl;
        return "No instance of robot with id " + std::to_string(id);
    }
}

void adapters::Mongo_Adapter::delete_all_tasks(){
    db_["task"].drop( {} );
}


