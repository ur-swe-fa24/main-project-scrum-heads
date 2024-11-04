#include "adapters/mongo_adapter.hpp"
#include "robot.hpp"
#include <memory>
#include <utility>

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

adapters::Mongo_Adapter::Mongo_Adapter(){
    // Initialize the instance and mongo db as private variables
}

// Pass by const ref - protects original objects the parameters are the senor or actuator
void adapters::Mongo_Adapter::write_robot(const robots::Robots& robot){
    // Mongo db will read exampledoc as a rvalue so the doc should be created all in one line 
    auto result = db_["robot"].insert_one(make_document(
        kvp("_id", robot.get_id()),
        kvp("size", robot.get_size()),
        kvp("water_level", robot.get_water_level()),
        kvp("battery level", robot.get_battery_level()),
        kvp("Error Status", robot.get_error_status()),
        kvp("Task Status", robot.get_task_status()),
        kvp("Task Room", robot.get_task_room()),
        kvp("Function Type", robot.get_function_type()),
        kvp("Location x", robot.get_location_x()),
        kvp("Location y", robot.get_location_y())
    ));
}

void adapters::Mongo_Adapter::read_robot(int id) {
    auto result = db_["robot"].find_one(make_document(kvp("_id", id)));
    if (result) {
        auto information = bsoncxx::to_json(*result);
        std::cout << "here" << std::endl;
        json Doc = json::parse(information);

        // Assuming Doc is a JSON object, access fields by their keys.
        std::cout << "here" << std::endl;
        auto Id = Doc["_id"];
        auto Size = Doc["size"];
        auto Water_Level = Doc["water_level"];
        auto Battery_Level = Doc["battery level"];
        auto Error_Status = Doc["Error Status"];
        auto Task_Status = Doc["Task Status"];
        auto Task_Room = Doc["Task Room"];
        auto Function_type = Doc["Function Type"];
        auto Location_x = Doc["Location x"];
        auto Location_y = Doc["Location y"];
        std::cout << "here" << std::endl;

        // Print or utilize the extracted information as needed
        std::cout << "Robot ID: " << Id << std::endl;
        std::cout << "Size: " << Size << std::endl;
        std::cout << "Water Level: " << Water_Level << std::endl;
        std::cout << "Battery Level: " << Battery_Level << std::endl;
        std::cout << "Error Status: " << Error_Status << std::endl;
        std::cout << "Task Status: " << Task_Status << std::endl;
        std::cout << "Task Room: " << Task_Room << std::endl;
        std::cout << "Function Type: " << Function_type << std::endl;
        std::cout << "Location: (" << Location_x << ", " << Location_y << ")" << std::endl;
    } else {
        std::cout << "No instance of robot with id " << id << std::endl;
    }
}

void adapters::Mongo_Adapter::read_all_robots(){
    auto cursor = db_["robot"].find({});
    for( auto&& doc : cursor) {
        std::cout << bsoncxx::to_json(doc) << std::endl;
    }
}
    

void adapters::Mongo_Adapter::delete_robot(int id){
    auto result = db_["robot"].delete_one(make_document(kvp("_id", id)));
}

void adapters::Mongo_Adapter::delete_all_robots(){
    db_["robot"].drop( {} );
}


void adapters::Mongo_Adapter::update_robot(int id, int water_level, int battery_level){
    auto query_filter = make_document(kvp("_id", id));
    auto update_doc1 = make_document(kvp("$set", make_document(kvp("battery level", battery_level))));
    auto update_doc2 = make_document(kvp("$set", make_document(kvp("water_level", water_level))));
    db_["robot"].update_one(query_filter.view(), update_doc1.view());
    db_["robot"].update_one(query_filter.view(), update_doc2.view());

}


