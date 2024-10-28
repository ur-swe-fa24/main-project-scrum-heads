cmake_minimum_required(VERSION 3.10)
project(WxAppTest)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# # Define the location of wxWidgets
# # Note: this is specifically implemented for my local machine. You will need to change this for your machine.
# set(wxWidgets_ROOT_DIR "/Users/jeremywhite/Desktop/CMSC 322/Project/wxWidgets-3.2.6/")
# set(wxWidgets_LIB_DIR "${wxWidgets_ROOT_DIR}/lib")
# set(wxWidgets_INCLUDE_DIR "${wxWidgets_ROOT_DIR}/include")

# # Add wxWidgets to CMake's search paths
# list(APPEND CMAKE_PREFIX_PATH "${wxWidgets_ROOT_DIR}")
# list(APPEND CMAKE_LIBRARY_PATH "${wxWidgets_LIB_DIR}")

# Find wxWidgets
find_package(wxWidgets REQUIRED COMPONENTS core base)

# Include wxWidgets
include(${wxWidgets_USE_FILE})

# Add your executable target
add_executable(WxAppTest hello_world.cpp)

# Link wxWidgets to the target
target_link_libraries(WxAppTest ${wxWidgets_LIBRARIES})
