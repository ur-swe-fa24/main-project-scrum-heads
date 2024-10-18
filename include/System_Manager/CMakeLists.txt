cmake_minimum_required(VERSION 3.10)
project(SystemManagerComponent)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${PROJECT_SOURCE_DIR}/include)

# Add executable for the System Manager
add_executable(system_manager
    ${PROJECT_SOURCE_DIR}/src/SystemManager.cpp
)


target_link_libraries(system_manager
    spdlog::spdlog
)
