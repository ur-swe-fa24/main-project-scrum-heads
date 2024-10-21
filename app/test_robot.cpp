#include <iostream>
#include "robot.hpp"
#include <vector>

using namespace robots;

int main(int argc, char* argv[]) {
    /** This is a pseudo code for how I planned the system manager should interact with the user(Only for this sprint)
    robots::Robots::Start_Time startTime = {9, 0, 0};  // 9:00:00
        robots::Robots::End_Time endTime = {17, 30, 45};   // 17:30:45
    // Create a Robot object
    robots::Robots robot(a,b,c,d)
    a = 1
    
    robots::Robots robot1(1, "Medium", 100, 90, "No Error", "Finished", 101, 
                      robots::Robots::robotFunction::SCRUB, 5, 5, startTime, endTime);
    std::cout << "Hi! Which role are you: FieldEngineer" << std::endl;
    cin >> string
    if (string == FieldEngineer) {
        std::cout << "What you do want to do today? choices: create robot" << std::endl;
        cin >> string2
        // Create a Robot object
        robots::Robots robot1(1, "Medium", 100, 90, "No Error", "Finished", 101, 
                      robots::Robots::robotFunction::SCRUB, 5, 5, startTime, endTime);
        std::cout << "What you do want to do today? choices: create robot" << std::endl;

        if (string2 == "view_robot1_status") {
            robot1.field_engineer_view_status();
        }
    }
    */

    // testing field_engineer_view_status()
    std::cout << "\n--- testing field_engineer_view_status() ---\n";
    robots::Robots::Start_Time startTime = {9, 0, 0};  // 9:00:00
    robots::Robots::End_Time endTime = {17, 30, 45};   // 17:30:45

    robots::Robots robot1(1, "Medium", 100, 90, "No Error", "Finished", 101, 
                        robots::Robots::robotFunction::SCRUB, 5, 5, startTime, endTime);
    robot1.field_engineer_view_status();

    //testing add a robot
    std::cout << "\n--- testing add_robot() ---\n";
    std::vector<robots::Robots> robot_list;

    // Create a Robots object to call add_robot (the robot object will be overwritten by new user input)
    robots::Robots temp_robot(0, "", 0, 0, "", "", 0, robots::Robots::robotFunction::SCRUB, 0, 0);

    // Call add_robot function using temp_robot object
    temp_robot.add_robot(robot_list);

    // View the robot's status after it's added
    if (!robot_list.empty()) {
        std::cout << "\n--- Robot Status ---\n";
        robot_list[0].field_engineer_view_status();
    } else {
        std::cout << "No robots were added." << std::endl;
    }
    return 0;
}

