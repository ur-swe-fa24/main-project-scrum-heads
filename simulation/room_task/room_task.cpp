#include "room_task.hpp"
#include "spdlog/spdlog.h"

namespace tasks {

int RoomTask::calculate_task_duration(room_size_) const {
    if (room_size_ == "small"){return 8000; }   // Small task duration (ms)
    if (room_size_ == "medium"){return 10000; }   // Small task duration (ms)
    if (room_size_ == "large"){return 12000; }   // Small task duration (ms)
    return 0;
}

int RoomTask::get_resource_usage() const {
    if (room_size_ == "small"){return 1; }
    if (room_size_ == "medium"){return 4; }
    if (room_size_ == "large"){return 9; }
    return 0;
}

} // namespace tasks
