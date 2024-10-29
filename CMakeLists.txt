cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
message("Export compile commands: ${CMAKE_EXPORT_COMPILE_COMMANDS}")
set(CMAKE_INSTALL_PREFIX "$ENV{HOME}/libs/mongo-cxx-driver")
message("CMake install prefix: ${CMAKE_INSTALL_PREFIX}")

include(dependencies/get_cpm.cmake)
include(dependencies/dependencies.cmake)

find_package(mongocxx REQUIRED)
if (mongocxx_FOUND)
  message(STATUS "mongocxx found!")
endif()
find_package(bsoncxx REQUIRED)
if (bsoncxx_FOUND)
  message(STATUS "bsoncxx found!")
endif()

# Project name and version
project(ScrumHeads VERSION 1.0)

# Add include directories
include_directories(include)

# Add subdirectories for app
add_subdirectory(app)
# add_subdirectory(wxWidgets)

# Create a library from the robot.cpp file in src
add_library(robot_lib src/robot.cpp)

# Include directories for robot_lib
target_include_directories(robot_lib PUBLIC include)
