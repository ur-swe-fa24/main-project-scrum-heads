# Create a library from the robot.cpp file in src
add_library(robot_lib robot.cpp)

# Include directories for robot_lib
target_include_directories(robot_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)
