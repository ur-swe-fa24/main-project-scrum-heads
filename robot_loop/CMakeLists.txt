add_library(robot_loop_lib
    robot_loop_lib.cpp
)

# Link dependencies for robot_loop_lib
target_link_libraries(robot_loop_lib
    PUBLIC
        spdlog::spdlog
        robot_lib  # Include robot_lib if needed by robot_loop_lib
)

# Define the robot_loop executable
add_executable(robot_loop
    robot_loop.cpp
)

# Link robot_loop executable with robot_loop_lib
target_link_libraries(robot_loop
    PRIVATE
        robot_loop_lib
        robot_lib
        room_task
        spdlog::spdlog
)