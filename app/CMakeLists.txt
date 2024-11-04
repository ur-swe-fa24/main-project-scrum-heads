# Add the test_loop executable from the test_loop.cpp file in the app folder
add_executable(test_loop test_loop.cpp)

# Link test_loop with robot_lib, room_task, and spdlog
target_link_libraries(test_loop PRIVATE robot_lib room_task spdlog::spdlog)

# Include directories for headers (if needed for test_loop)
target_include_directories(test_loop PRIVATE ${CMAKE_SOURCE_DIR}/include)
