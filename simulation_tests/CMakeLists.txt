find_package(Catch2 3 REQUIRED)

if (Catch2_FOUND)
    message(STATUS "Found Catch2")
else ()
    message(FATAL_ERROR "Could not find Catch2. Ensure it is installed!")
endif ()

# Add the test executable
# add_executable(unit_test_loop unit_test_loop.cpp)

# # Link required libraries
# target_link_libraries(unit_test_loop
#     PRIVATE
#         Catch2::Catch2
#         robot_loop_lib
#         robot_lib
#         room_task
# )

# target_compile_features(unit_test_loop PRIVATE cxx_std_17)

# # Include directories for the test executable
# target_include_directories(unit_test_loop
#     PRIVATE
#         ${CMAKE_SOURCE_DIR}/include
# )

