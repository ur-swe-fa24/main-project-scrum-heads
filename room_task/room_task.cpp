#include "room_task.hpp"
#include "spdlog/spdlog.h"

namespace tasks {

int RoomTask::calculate_task_duration() const {
    switch (room_size_) {
        case RoomSize::SMALL: return 8000;    // Shortest task duration (ms)
        case RoomSize::MEDIUM: return 10000;   // Medium task duration (ms)
        case RoomSize::LARGE: return 12000;   // Longest task duration (ms)
    }
    return 0;
}

int RoomTask::get_resource_usage() const {
    switch (room_size_) {
        case RoomSize::SMALL: return 1;
        case RoomSize::MEDIUM: return 4;
        case RoomSize::LARGE: return 9;
    }
    return 0;
}

} // namespace tasks
