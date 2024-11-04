add_executable(robot_loop
    robot_loop.cpp
)

target_include_directories(robot_loop
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)

target_link_libraries(robot_loop
    spdlog::spdlog
)