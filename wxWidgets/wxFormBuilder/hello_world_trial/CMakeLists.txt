cmake_minimum_required(VERSION 3.10)
project(WxFormBuilderTest)

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

# Find wxWidgets (ensure that the necessary components are found)
find_package(wxWidgets REQUIRED COMPONENTS core base)

# Debugging: Output the wxWidgets include directories
message(STATUS "wxWidgets include directories: ${wxWidgets_INCLUDE_DIRS}")

# Include wxWidgets settings (adds include directories and compile/link flags)
include(${wxWidgets_USE_FILE})

# Add your source files
set(SRC_FILES
    MyProjectBase.cpp
    derivedFrame.cpp
    main.cpp
)

# Add your executable target
add_executable(WxFormBuilderTest ${SRC_FILES})

# Link wxWidgets to the target
target_link_libraries(WxFormBuilderTest ${wxWidgets_LIBRARIES})
