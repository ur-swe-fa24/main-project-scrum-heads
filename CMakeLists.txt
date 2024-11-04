cmake_minimum_required(VERSION 3.10)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Project name and version
project(ScrumHeads VERSION 1.0)

# Add include directories
include_directories(include)

# Add subdirectories for app, wxWidgets, robot_loop, and room_task
add_subdirectory(app)
add_subdirectory(wxWidgets)
add_subdirectory(robot_loop)
add_subdirectory(room_task)
add_subdirectory(src)  # Include src directory to build robot_lib
