cmake_minimum_required(VERSION 3.10)
project(wxWidgets)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(../dependencies/get_cpm.cmake)
include(../dependencies/dependencies.cmake)

# # Define the location of wxWidgets
# # Note: this is specifically implemented for my local machine. You will need to change this for your machine.
# set(wxWidgets_ROOT_DIR "/Users/jeremywhite/Desktop/CMSC 322/Project/wxWidgets-3.2.6/")
# set(wxWidgets_LIB_DIR "${wxWidgets_ROOT_DIR}/lib")
# set(wxWidgets_INCLUDE_DIR "${wxWidgets_ROOT_DIR}/include")

# # Add wxWidgets to CMake's search paths
# list(APPEND CMAKE_PREFIX_PATH "${wxWidgets_ROOT_DIR}")
# list(APPEND CMAKE_LIBRARY_PATH "${wxWidgets_LIB_DIR}")

# Find wxWidgets (ensures that the necessary components are found)
# find_package(wxWidgets REQUIRED COMPONENTS core base)

# Include wxWidgets settings
# include(${wxWidgets_USE_FILE})

# # Combine WxFormBuilder source files
# set(WX_FORM_BUILDER_FILES
#     wxFormBuilder/hello_world_trial/MyProjectBase.cpp
#     wxFormBuilder/hello_world_trial/derivedFrame.cpp
#     wxFormBuilder/hello_world_trial/newDerivedFrame.cpp
#     wxFormBuilder/hello_world_trial/main.cpp
# )

# # Combine WxApp source files
# set(WX_APP_FILES
#     WxAppTest/hello_world.cpp
# )

# Combine WxApp source files
set(PROJECT_GUI_IMPLEMENTATION_FILES
    Project_Implementation/MyProjectBase.cpp
    Project_Implementation/baseFrame.cpp
    Project_Implementation/bmBaseFrame.cpp
    Project_Implementation/smBaseFrame.cpp
    Project_Implementation/bsBaseFrame.cpp
    Project_Implementation/feBaseFrame.cpp
    Project_Implementation/addRobotFrame.cpp
    Project_Implementation/robotInfoFrame.cpp
    Project_Implementation/addTaskFrame.cpp
    Project_Implementation/viewTaskFrame.cpp
    Project_Implementation/main.cpp
    # ../src/DataManager.cpp
)

# # Add executable target for WxFormBuilder
# add_executable(WxFormBuilderTest ${WX_FORM_BUILDER_FILES})

# # Add executable target for WxApp
# add_executable(WxAppTest ${WX_APP_FILES})

add_executable(ProjectGUI ${PROJECT_GUI_IMPLEMENTATION_FILES})

# # Link wxWidgets to target
# target_link_libraries(WxFormBuilderTest wx::net wx::core wx::base)

# # Link wxWidgets to target
# target_link_libraries(WxAppTest wx::net wx::core wx::base)

# Link wxWidgets to target
target_link_libraries(ProjectGUI wx::net wx::core wx::base data_lib)