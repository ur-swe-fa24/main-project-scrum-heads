#include "adapters/mongo_adapter.hpp"
#include "robot.hpp"
#include <memory>
#include <utility>

#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_array;
using bsoncxx::builder::basic::make_document;

adapters::Mongo_Adapter::Mongo_Adapter(){
    // mongo_instance_ instance{}; // This should be done only once.
    // mongocxx::uri uri("mongodb://localhost:27017");
    // mongocxx::client client(uri);
    
    auto collection = db_["robot"];
}

// Pass by const ref - protects original objects the parameters are the senor or actuator
void adapters::Mongo_Adapter::write_robot(const robots::Robots& robot){
    //std::vector<bsoncxx::document::value> documents;
    // auto example_doc = make_document(
    //     kvp("id", robot.get_id()),
    //     kvp("size", robot.get_size()),
    //     kvp("water_level", robot.get_water_level()),
    //     kvp("battery level", robot.get_battery_level()),
    //     kvp("Error Status", robot.get_error_status()),
    //     kvp("Task Status", robot.get_task_status()),
    //     kvp("Function Type", robot.get_function_type()),
    //     kvp("Location x:", robot.get_location_x()),
    //     kvp("Location y:", robot.get_location_y()),
    //     kvp("Task Length:", robot.get_task_length()),
    //     kvp("Location x:", robot.get_location_x())
    // );

    auto result = db_["robot"].insert_one(make_document(
        kvp("robot_id", robot.get_id()),
        kvp("size", robot.get_size()),
        kvp("water_level", robot.get_water_level()),
        kvp("battery level", robot.get_battery_level()),
        kvp("Error Status", robot.get_error_status()),
        kvp("Task Status", robot.get_task_status()),
        kvp("Function Type", robot.get_function_type()),
        kvp("Location x:", robot.get_location_x()),
        kvp("Location y:", robot.get_location_y())
    ));
}

void adapters::Mongo_Adapter::read_robot(const robots::Robots& robot){
    auto result = db_["robot"].find_one(make_document(kvp("robot_id", robot.get_id())));
    std::cout << bsoncxx::to_json(*result) << std::endl;
}