# CMakeLists.txt in tests folder

# Enable FetchContent to download dependencies if not found
include(FetchContent)

# Find or download Catch2 (version 3)
find_package(Catch2 3 REQUIRED)

if (Catch2_FOUND)
    message(STATUS "Found Catch2 with target: Catch2::Catch2WithMain")
else()
    message(FATAL_ERROR "Could not find Catch2. Make sure it's installed on your system!")
endif()

# Fetch or find spdlog
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.10.0  # Use a stable version of spdlog
)

FetchContent_MakeAvailable(spdlog)

# Define the test executable for unit_test_loop.cpp
add_executable(unit_test_loop unit_test_loop.cpp)

# Link required libraries: Catch2, robot_lib, room_task, and spdlog
target_link_libraries(unit_test_loop
    PRIVATE
        Catch2::Catch2WithMain  # Catch2 with main function
        robot_lib               # Library for Robots
        room_task               # Library for RoomTask
        spdlog::spdlog          # Logging library
)

# Set the C++ standard to 17
target_compile_features(unit_test_loop PRIVATE cxx_std_17)
