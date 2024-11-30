find_package(Catch2 3 REQUIRED)

IF (${Catch2_FOUND})
    MESSAGE(STATUS "Found Catch2")
ELSE (${Catch2_FOUND})
    MESSAGE(STATUS "Cound not find Catch2. Check to make sure its installed on your system!")
ENDIF (${Catch2_FOUND})

add_executable(test_mongodb 
    test_mongodb.cpp
)

target_include_directories(test_mongodb
    PRIVATE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)

target_compile_features(test_mongodb PRIVATE cxx_std_17)

target_link_libraries(test_mongodb
  PRIVATE
    Catch2::Catch2WithMain
    spdlog::spdlog_header_only
    mongo::mongocxx_shared
)

target_link_libraries(test_mongodb
    PRIVATE
        adapter_lib
)

# Define robot_do_task as a library
add_library(robot_do_task ../simulation/robot_do_task.cpp)
target_include_directories(robot_do_task
    PRIVATE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)
target_link_libraries(robot_do_task PRIVATE spdlog::spdlog_header_only)

# Define room_task as a library
add_library(room_task ../simulation/room_task.cpp)
target_include_directories(room_task
    PRIVATE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)

# Define test_simulation executable
add_executable(test_simulation 
    test_simulation.cpp
    ../src/robot.cpp
)

target_include_directories(test_simulation
    PRIVATE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)

target_compile_features(test_simulation PRIVATE cxx_std_17)

target_link_libraries(test_simulation
  PRIVATE
    Catch2::Catch2WithMain
    spdlog::spdlog_header_only
    robot_do_task
    room_task
)

# add_executable(test_datamanager 
#     test_datamanager.cpp
# )

# target_include_directories(test_datamanager
#     PRIVATE
#     $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
# )

# target_compile_features(test_datamanager PRIVATE cxx_std_17)

# target_link_libraries(test_datamanager
#   PRIVATE
#     Catch2::Catch2WithMain
#     spdlog::spdlog_header_only
#     mongo::mongocxx_shared
#     data_lib
# )
