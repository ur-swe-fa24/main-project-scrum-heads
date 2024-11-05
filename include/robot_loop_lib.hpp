// robot_loop_lib.hpp
#ifndef ROBOT_LOOP_LIB_HPP
#define ROBOT_LOOP_LIB_HPP

#include <atomic>
#include <string>
#include "robot.hpp"
#include "room_task.hpp"

enum class Event {
    START,
    STOP,
    QUIT,
    CONTINUE,
    UNKNOWN
};

enum class ErrorType {
    OVERHEAT,
    LOW_BATTERY,
    MOTOR_FAILURE,
    SENSOR_FAILURE,
    SOFTWARE_CRASH
};

std::string event_string(Event event);
std::string error_string(ErrorType error);
int task(robots::Robots& robot, tasks::RoomTask& room_task, std::atomic_bool& is_canceled, std::atomic_bool& is_paused, int task_length);

#endif // ROBOT_LOOP_LIB_HPP
