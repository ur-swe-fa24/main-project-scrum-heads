# Add the room_task library
add_library(room_task STATIC
    room_task.cpp
)

# Add include directories for room_task
target_include_directories(room_task
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include> # Public headers (e.g., room_task.hpp)
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>   # For the current directory
)

# Add the robot_do_task library
add_library(robot_do_task STATIC
    robot_do_task.cpp
)

# Add include directories for robot_do_task
target_include_directories(robot_do_task
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include> # Public headers (e.g., robot_do_task.hpp)
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>   # For the current directory
)

# Link dependencies for robot_do_task
target_link_libraries(robot_do_task
    PRIVATE
        room_task       # Link room_task as a dependency
        robot_lib       # Assuming robot_lib is another library in your project
)
