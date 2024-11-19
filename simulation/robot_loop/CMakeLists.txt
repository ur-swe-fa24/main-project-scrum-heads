# add_library(robot_loop_lib
#     robot_loop_lib.cpp
# )

# Link dependencies for robot_loop_lib
# target_link_libraries(robot_loop_lib
#     PUBLIC
#         spdlog::spdlog
#         robot_lib  # Include robot_lib if needed by robot_loop_lib
# )

# Define the robot_loop executable
add_executable(robot_do_task
    robot_do_task.cpp
)

# Link robot_loop executable with robot_loop_lib
target_link_libraries(robot_do_task
    PRIVATE
        room_task
        robot_lib
)