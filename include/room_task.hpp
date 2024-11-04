#ifndef ROOM_TASK_HPP
#define ROOM_TASK_HPP

#include "robot.hpp"
#include <string>

namespace tasks {

class RoomTask {
public:
    enum class RoomSize { SMALL, MEDIUM, LARGE };

    explicit RoomTask(RoomSize size) : room_size_(size) {}

    // Function to perform the task, modifying the robot's battery and water levels
    void perform_task(robots::Robots& robot);

private:
    RoomSize room_size_;
    int calculate_task_duration() const;
    int get_resource_usage() const;
};

} // namespace tasks

#endif // ROOM_TASK_HPP
