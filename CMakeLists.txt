cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
message("Export compile commands: ${CMAKE_EXPORT_COMPILE_COMMANDS}")
# set(CMAKE_INSTALL_PREFIX "$ENV{HOME}/libs/mongo-cxx-driver")
message("CMake install prefix: ${CMAKE_INSTALL_PREFIX}")

project(ScrumHeads VERSION 1.0)

include(dependencies/get_cpm.cmake)
include(dependencies/dependencies.cmake)
# cmake -DCMAKE_PREFIX_PATH="/home/kc3ks/libs/mongo-cxx-driver" ..
find_package(mongocxx CONFIG REQUIRED)
if (mongocxx_FOUND)
  message(STATUS "mongocxx found!")
endif()
find_package(bsoncxx REQUIRED)
if (bsoncxx_FOUND)
  message(STATUS "bsoncxx found!")
endif()



# Add include directories
include_directories(include)

# Add subdirectories for app, wxWidgets, robot_loop, and room_task
add_subdirectory(app)
add_subdirectory(wxWidgets)

# Create a library from the robot.cpp file in src
add_library(robot_lib src/robot.cpp)
add_library(adapter_lib src/mongo_adapter.cpp)

target_link_libraries(adapter_lib
    PRIVATE
      mongo::mongocxx_shared
)

# Create a library from the DataManager.cpp file in src
add_library(dataManager_lib src/DataManager.cpp)

target_link_libraries(dataManager_lib wx::net wx::core wx::base)

# Include directories for robot_lib
target_include_directories(robot_lib PUBLIC include)
add_subdirectory(robot_loop)
add_subdirectory(room_task)
