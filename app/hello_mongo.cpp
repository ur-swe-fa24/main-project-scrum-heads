#include "spdlog/spdlog.h"

#include <cstdint>
#include <iostream>
#include <vector>

// #include <bsoncxx/builder/basic/document.hpp>
// #include <bsoncxx/json.hpp>
// #include <mongocxx/client.hpp>
// #include <mongocxx/instance.hpp>

#include "robot.hpp"
#include "adapters/mongo_adapter.hpp"

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_array;
using bsoncxx::builder::basic::make_document;

int main() 
{
    std::cout << "First make a robot: " << std::endl;

    robots::Robots::Start_Time startTime = {9, 0, 0};  // Represents 9:00:00 AM
    robots::Robots::End_Time endTime = {17, 30, 45}; 
    robots::Robots temp_robot(47, "Large", 100, 50, "", "Vacuum", 3, robots::Robots::robotFunction::SCRUB, 10, 15, startTime, endTime);
    adapters::Mongo_Adapter mongo_database{};
    spdlog::info("Connected to the mongodb!");

    std::cout << "Now let's write a Robot" << std::endl;
    mongo_database.write_robot(temp_robot);

    std::cout << "Now let's read the robot" << std::endl;
    std::string hello = mongo_database.read_robot(47);
    std::cout << hello << std::endl;


    std::cout << "Now let's update the robot" << std::endl;
    mongo_database.update_robot(47, 50, 25);

    std::cout << "Now let's read the robot" << std::endl;
    mongo_database.read_robot(47);
    mongo_database.get_all_ids();


    std::cout << "Now let's delete the robot" << std::endl;
    mongo_database.delete_robot(47);

    std::cout << "Now let's check the robot was deleted" << std::endl;
    mongo_database.read_robot(47);


    std::cout << "Now delete all robots" << std::endl;
    mongo_database.write_robot(temp_robot);
    mongo_database.delete_all_robots();

    std::cout << "Now let's check all robots were deleted" << std::endl;
    mongo_database.read_all_robots();


    std::cout << "End of program" << std::endl;


}
