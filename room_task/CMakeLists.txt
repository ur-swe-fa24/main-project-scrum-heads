add_library(room_task room_task.cpp)

target_include_directories(room_task
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)

target_link_libraries(room_task
    PUBLIC
        spdlog::spdlog
)
