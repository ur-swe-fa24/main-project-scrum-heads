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
        kvp("Error Status", robot.get_error_status())
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
        //Remove error status, task status and room, and location
        auto Id = Doc["_id"];
        auto Size = Doc["size"];
        auto Water_Level = Doc["water_level"];
        auto Battery_Level = Doc["battery level"];
        // auto Task_Status = Doc["Task Status"];
        auto Function_type = Doc["Function Type"];
        auto Error_Status = Doc["Error Status"];

        robots::Robots new_robot = robots::Robots{Id, Size, Water_Level, Battery_Level, Error_Status, "", 0, Function_type, 0, 0} ;
        
        std::cout << "Robot ID: " << Id << std::endl;
        std::cout << "Size: " << Size << std::endl;
        std::cout << "Water Level: " << Water_Level << std::endl;
        std::cout << "Battery Level: " << Battery_Level << std::endl;
        std::cout << "Function Type: " << Function_type << std::endl;
        std::cout << "Error Status: " << Error_Status << std::endl;
        return new_robot;
    } 
    std::cout << "No instance of robot with id " << id << std::endl;
    robots::Robots new_robot = robots::Robots(id, "", 0, 0, "No instance of robot with id", "", 0, "", 0, 0);
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

        robots::Robots new_robot = robots::Robots{Id, Size, Water_Level, Battery_Level, Error_Status, "", 0, Function_type, 0, 0};
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
    //Create documents with the new battery level and water level
    auto update_doc1 = make_document(kvp("$set", make_document(kvp("battery level", battery_level))));
    auto update_doc2 = make_document(kvp("$set", make_document(kvp("water_level", water_level))));

    //Update the old robot instance in the database
    db_["robot"].update_one(query_filter.view(), update_doc1.view());
    db_["robot"].update_one(query_filter.view(), update_doc2.view());
}

std::vector<int> adapters::Mongo_Adapter::get_all_ids(){
    std::vector<int> ids;
    auto cursor = db_["robot"].find({});
    for(auto&& doc : cursor) {
        auto information = bsoncxx::to_json(doc);
        json info = json::parse(information);
        auto Id = info["_id"];
        ids.push_back(Id);
    }
    return ids;
}



