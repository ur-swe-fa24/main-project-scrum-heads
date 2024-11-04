# Define room_task as a library
add_library(room_task room_task.cpp)

# Specify the include directories for room_task
target_include_directories(room_task
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)

# Link required libraries to room_task
target_link_libraries(room_task
    PUBLIC
        spdlog::spdlog
)
