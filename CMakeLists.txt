cmake_minimum_required(VERSION 3.10)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Project name and version
project(ScrumHeads VERSION 1.0)

# Add include directories
include_directories(include)

# Add subdirectories for app
add_subdirectory(app)

# Create a library from the robot.cpp file in src
add_library(robot_lib src/robot.cpp)

# Include directories for robot_lib
target_include_directories(robot_lib PUBLIC include)
