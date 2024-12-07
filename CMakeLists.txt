cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
message("Export compile commands: ${CMAKE_EXPORT_COMPILE_COMMANDS}")
set(CMAKE_INSTALL_PREFIX "$ENV{HOME}/libs/mongo-cxx-driver")
message("CMake install prefix: ${CMAKE_INSTALL_PREFIX}")

project(ScrumHeads VERSION 1.0)

# Include dependencies
include(dependencies/get_cpm.cmake)
include(dependencies/dependencies.cmake)

# Find MongoDB C++ libraries
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

# Create robot_lib for robot-related implementations
add_library(robot_lib
    simulation/robot_manager.cpp
    simulation/robot_do_task.cpp
)

# Set include directories for robot_lib
target_include_directories(robot_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include      # Include the 'include' directory
    ${CMAKE_CURRENT_SOURCE_DIR}/simulation  # Include the 'simulation' directory
)

# Link dependencies for robot_lib
target_link_libraries(robot_lib PUBLIC)

# Create adapter_lib for MongoDB adapter
add_library(adapter_lib src/mongo_adapter.cpp)
target_link_libraries(adapter_lib mongo::mongocxx_shared)

# Create data_lib and link it with adapter_lib and robot_lib
add_library(data_lib src/DataManager.cpp)
target_link_libraries(data_lib PUBLIC adapter_lib robot_lib wx::net wx::core wx::base)

# Add subdirectories for components
add_subdirectory(app)
add_subdirectory(tests)
add_subdirectory(wxWidgets)
add_subdirectory(simulation)



# Find spdlog package
find_package(spdlog REQUIRED)

# Link spdlog to your target
target_link_libraries(data_lib PUBLIC spdlog::spdlog)
