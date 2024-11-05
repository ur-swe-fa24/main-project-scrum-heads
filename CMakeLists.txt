cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
message("Export compile commands: ${CMAKE_EXPORT_COMPILE_COMMANDS}")
message("CMake install prefix: ${CMAKE_INSTALL_PREFIX}")

project(ScrumHeads VERSION 1.0)

include(dependencies/get_cpm.cmake)
include(dependencies/dependencies.cmake)

# Add include directories
include_directories(include)

# Add subdirectories for components
add_subdirectory(app)
add_subdirectory(robot_loop)
add_subdirectory(room_task)
add_subdirectory(simulation_tests)

# Create a library from the robot.cpp file in src
add_library(robot_lib src/robot.cpp)

# Include directories for robot_lib
target_include_directories(robot_lib PUBLIC include)