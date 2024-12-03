cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
message("Export compile commands: ${CMAKE_EXPORT_COMPILE_COMMANDS}")
message("CMake install prefix: ${CMAKE_INSTALL_PREFIX}")

project(ScrumHeads VERSION 1.0)

# Include dependencies
include(dependencies/get_cpm.cmake)
include(dependencies/dependencies.cmake)

# # Find MongoDB C++ libraries
# find_package(mongocxx CONFIG REQUIRED)
# if (mongocxx_FOUND)
#   message(STATUS "mongocxx found!")
# endif()

# find_package(bsoncxx REQUIRED)
if (bsoncxx_FOUND)
  message(STATUS "bsoncxx found!")
endif()

# Add include directories
include_directories(include)

# Add subdirectories for components
add_subdirectory(app)
add_subdirectory(tests)
add_subdirectory(wxWidgets)

# Create libraries
add_library(robot_lib src/robot.cpp)
target_include_directories(robot_lib PUBLIC include)
# add_library(adapter_lib src/mongo_adapter.cpp)
# target_link_libraries(adapter_lib PRIVATE mongo::mongocxx_shared)
