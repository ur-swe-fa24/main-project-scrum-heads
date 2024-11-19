#include <iostream>
#include "robot.hpp"

namespace robots {
    void Robots::add_robot(std::vector<Robots>& robot_list, const Robots& new_robot) {
        robot_list.push_back(new_robot);
    }
}