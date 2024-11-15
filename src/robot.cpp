#include <iostream>
#include "robot.hpp"


// Function to display the robot's full status for field engineers
void robots::Robots::field_engineer_view_status() const {
    std::cout << "Robot ID: " << get_id() << "\n"
              << "Size: " << get_size() << "\n"
              << "Water Level: " << get_water_level() << "\n"
              << "Battery Level: " << get_battery_level() << "\n"
              << "Error Status: " << get_error_status() << "\n"
              << "Task Status: " << get_task_status() << "\n"
              << "Task Room: " << get_task_room() << "\n"
              << "Function Type: " << get_function_type() << "\n"
              << "Location X: " << get_location_x() << "\n"
              << "Location Y: " << get_location_y() << "\n" << std::endl;
}

// // Function to convert string to robotFunction
// void robots::Robots::add_robot(std::vector<robots::Robots>& robot_list) {
//     int16_t robot_id, water_level, battery_level;
//     std::string size, function_type_input;

//     // Get user input for robot details
//     std::cout << "Enter Robot ID: ";
//     std::cin >> robot_id;
//     std::cout << "Enter Robot Size (Small, Medium, Large): ";
//     std::cin >> size;
//     std::cout << "Enter Water Level: ";
//     std::cin >> water_level;
//     std::cout << "Enter Battery Level: ";
//     std::cin >> battery_level;
//     std::cout << "Enter Function Type (scrub, shampoo, vacuum): ";
//     std::cin >> function_type_input;

//     // Convert function type input to enum
//     robots::Robots::robotFunction function_type;
//     if (function_type_input == "scrub") {
//         function_type = robots::Robots::robotFunction::SCRUB;
//     } else if (function_type_input == "shampoo") {
//         function_type = robots::Robots::robotFunction::SHAMPOO;
//     } else if (function_type_input == "vacuum") {
//         function_type = robots::Robots::robotFunction::VACUUM;
//     } else {
//         std::cerr << "Invalid function type input!" << std::endl;
//         return;
//     }

//     // Automatically set error status and task status to empty string and task room, location_x, location_y to 0
//     std::string error_status = "null";   // Error status is empty/null
//     std::string task_status = "null";    // Task status is empty/null
//     int16_t task_room = 0;           // Task room is set to 0
//     int16_t location_x = 0;          // Location x is set to 0
//     int16_t location_y = 0;          // Location y is set to 0

//     // Create a new Robot object with default values for task room, location, and statuses
//     robots::Robots new_robot(robot_id, size, water_level, battery_level, error_status, task_status, 
//                              task_room, function_type, location_x, location_y, {}, {});

//     // Add the new robot to the list
//     robot_list.push_back(new_robot);

//     std::cout << "Robot with ID " << robot_id << " has been added successfully.\n";
// }
