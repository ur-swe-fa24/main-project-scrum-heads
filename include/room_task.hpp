#ifndef ROOM_TASK_HPP
#define ROOM_TASK_HPP

#include <string>

namespace tasks {

class RoomTask {
public:
    // Enum for room size
    enum class RoomSize { SMALL, MEDIUM, LARGE };

    // Method to calculate the duration of a task based on room size
    static int calculate_task_duration(const std::string& room_size);

    // Method to get resource usage based on room size
    static int get_resource_usage(const std::string& room_size);
};

} // namespace tasks

#endif // ROOM_TASK_HPP
