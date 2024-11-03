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
    // Mongo db will read exampledoc as a rvalue so the doc should be created all in one line 

    auto result = db_["robot"].insert_one(make_document(
        kvp("_id", robot.get_id()),
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
    std::optional< bsoncxx::document::value > result = db_["robot"].find_one(make_document(kvp("_id", robot.get_id())));
    if (result){
        std::cout << bsoncxx::to_json(*result) << std::endl;
        // auto information = bsoncxx::to_json(*result);
        // json Doc{json::parse(information)};

        // std::cout << "here" << std::endl;
        // std::string Id{Doc[0]};
        // std::string Size{Doc[1]};
        // std::string Water_Level{Doc[2]};
        // std::string Battery_Level{Doc[3]};
        // std::string Error_Status{Doc[4]};
        // std::string Task_Status{Doc[5]};
        // std::string Function_type{Doc[6]};
        // std::string Location_x{Doc[7]};
        // std::string Location_y{Doc[8]};

        // std::cout << "here" << std::endl;

        // std::cout << "id: "  + Id << std::endl;
        // std::cout << "size: " + Size << std::endl;
        // std::cout << "Water Level: " + Water_Level << std::endl;
        // std::cout << "Battery Level: " + Battery_Level << std::endl;
        // std::cout << "Error Status: " + Error_Status << std::endl;
        // std::cout << "Task Status: " + Task_Status << std::endl;
        // std::cout << "Function Type: " + Function_type << std::endl;
        // std::cout << "Location x: " + Location_x << std::endl;
        // std::cout << "Location y: " + Location_y << std::endl;
    }
    else{
        std::cout << "No instance of robot with id "<< std::endl;
    }

    
        // std::cout << bsoncxx::to_json(*result) << std::endl;
    
    

    // std::cout << "Should be one robot" << std::endl;
    // auto results = db_["robot"].find(make_document(kvp("_id", 2)));
    // for(auto&& doc : results) {
    //     std::cout << bsoncxx::to_json(doc) << std::endl;
    // }
}

void adapters::Mongo_Adapter::delete_robot(const robots::Robots& robot){
    auto result = db_["robot"].delete_one(make_document(kvp("_id", robot.get_id())));
}

