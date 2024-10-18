#include <iostream>
#include "robot.hpp"

int robots::Robots::get_task_length() const {
    int start_total_seconds = task_start_time_.start_hour * 3600 + 
                              task_start_time_.start_minute * 60 + 
                              task_start_time_.start_second;
    int end_total_seconds = task_end_time_.end_hour * 3600 + 
                            task_end_time_.end_minute * 60 + 
                            task_end_time_.end_second;
    return end_total_seconds - start_total_seconds;
}

void robots::Robots::toString() const {
    std::cout << "Robot ID: " << get_id() << "\n"
              << "Size: " << get_size() << "\n"
              << "Water Level: " << get_water_level() << "\n"
              << "Battery Level: " << get_battery_level() << "\n"
              << "Error Status: " << get_error_status() << "\n"
              << "Task Status: " << get_task_status() << "\n"
              << "Task Room: " << get_task_room() << "\n"
              << "Function Type: " << get_function_type() << "\n"
              << "Location X: " << get_location_x() << "\n"
              << "Location Y: " << get_location_y() << "\n"
              << "Start Time: " << task_start_time_.start_hour << ":" 
                                << task_start_time_.start_minute << ":" 
                                << task_start_time_.start_second << "\n"
              << "End Time: " << task_end_time_.end_hour << ":" 
                              << task_end_time_.end_minute << ":" 
                              << task_end_time_.end_second << "\n"
             << "Task Length: " << get_task_length() << " seconds" << std::endl;
}