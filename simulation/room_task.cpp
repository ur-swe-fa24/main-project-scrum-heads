#include "room_task.hpp"

namespace tasks {

int RoomTask::calculate_task_duration(const std::string& room_size) {
    if (room_size == "small") { return 8000; }   // Small room task duration (ms)
    if (room_size == "medium") { return 10000; } // Medium room task duration (ms)
    if (room_size == "large") { return 12000; }  // Large room task duration (ms)
    return 0;
}

int RoomTask::get_resource_usage(const std::string& room_size) {
    if (room_size == "small") { return 1; }      // Small room resource usage
    if (room_size == "medium") { return 4; }    // Medium room resource usage
    if (room_size == "large") { return 9; }     // Large room resource usage
    return 0;
}

} // namespace tasks
