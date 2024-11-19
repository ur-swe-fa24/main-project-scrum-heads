#include <iostream>
#include "robot.hpp"
#include <vector>

using namespace robots;
using namespace std;

int main() {
    Robots temp_robot(0, "small", 100, 100, "", "", 0, "scrub", 0);
    vector<Robots> robot_list;
    robots::Robots::add_robot(robot_list, temp_robot);
    cout << "Number of robots in the list: " << robot_list.size() << endl;
    return 0;
}