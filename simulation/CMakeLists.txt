# Declare files in this subdirectory for inclusion in the parent CMakeLists.txt
set(SIMULATION_SOURCES
    robot_manager.cpp
    robot_do_task.cpp
)

# Include this folder's headers
target_include_directories(robot_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})