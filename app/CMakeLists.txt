# Add the executable for the test program
add_executable(test_robot 
    test_robot.cpp
    ../src/robot.cpp)

# Link the executable to the adapters library
target_link_libraries(test_robot)
