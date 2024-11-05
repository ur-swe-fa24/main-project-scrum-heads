#ifndef ROBOT_LOOP_HPP
#define ROBOT_LOOP_HPP

#include <atomic>
#include <string>
#include "robot_loop_lib.hpp"

// Helper functions to convert enums to strings
std::string event_string(Event event);
std::string error_string(ErrorType error);

// Function to run the main robot loop
void run_robot_loop();

#endif // ROBOT_LOOP_HPP
