cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
project(ScrumHeads VERSION 1.0)

# Add include directories
include_directories(include)

# Add subdirectories for source and app
add_subdirectory(app)
