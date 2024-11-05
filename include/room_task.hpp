#ifndef ROOM_TASK_HPP
#define ROOM_TASK_HPP

#include "robot.hpp"
#include <string>

namespace tasks {

class RoomTask {
public:
    // Enum for room size
    enum class RoomSize { SMALL, MEDIUM, LARGE };

    // Constructor to set room size
    explicit RoomTask(RoomSize size) : room_size_(size) {}

    // Method to calculate the duration of the task based on room size
    int calculate_task_duration() const;

    // Method to get resource usage percentage based on room size
    int get_resource_usage() const;

private:
    RoomSize room_size_;  // Store the size of the room for this task
};

} // namespace tasks

#endif // ROOM_TASK_HPP
