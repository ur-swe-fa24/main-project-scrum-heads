# Add the executable for the test program
add_executable(test_robot 
    test_robot.cpp
    ../src/robot.cpp)

# Link the executable to the adapters library
target_link_libraries(test_robot)

find_package(spdlog REQUIRED)
if (spdlog_FOUND)
  message(STATUS "spdlog found!")
endif()

add_executable(hello_mongo
  hello_mongo.cpp
)

target_include_directories(hello_mongo
    PRIVATE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)


target_link_libraries(hello_mongo
    PRIVATE
        adapter_lib
)

target_link_libraries(hello_mongo
  PRIVATE 
    spdlog::spdlog_header_only
    mongo::mongocxx_shared
)


