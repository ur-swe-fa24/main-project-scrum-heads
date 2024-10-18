#include <iostream>
#include "robot.hpp"

using namespace robots;

int main() {
    robots::Robots::Start_Time startTime = {9, 0, 0};  // 9:00:00
    robots::Robots::End_Time endTime = {17, 30, 45};   // 17:30:45

    // Create a Robot object
    robots::Robots robot1(1, "Medium", 100, 90, "No Error", "Finished", 101, 
                        robots::Robots::robotFunction::SCRUB, 5, 5, startTime, endTime);
    robot1.toString();
}
