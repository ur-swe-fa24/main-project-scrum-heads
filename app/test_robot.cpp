#include <iostream>
#include "robot.hpp"
#include <vector>

using namespace robots;
using namespace std;

int main() {
    Robots temp_robot(0, "Small", 100, 100, "", "", 0, "Scrub", 0);
    vector<Robots> robot_list;
    robots::Robots::add_robot(robot_list, temp_robot);
    cout << "Number of robots in the list: " << robot_list.size() << endl;
    return 0;
}

// #include <iostream>
// #include "robot.hpp"
// #include <vector>

// using namespace robots;
// using namespace std;

// int main() {
//     cout << "Hi! Which role are you? Enter 'FieldEngineer': ";
//     string user_role;
//     cin >> user_role; // Input the role of the user

//     // Check if the user is a Field Engineer
//     if (user_role == "FieldEngineer") {
//         cout << "What do you want to do today? Enter 'create_robot' or 'view_robot_status': ";
//         string action;
//         cin >> action; // Input the action the user wants to perform

//         // Set start and end times
//         Robots::Start_Time startTime = {9, 0, 0};  // Represents 9:00:00 AM
//         Robots::End_Time endTime = {17, 30, 45};   // Represents 5:30:45 PM

//         if (action == "create_robot") {
//             // Vector to hold robots
//             vector<Robots> robot_list; // Create a vector to store Robots objects

//             // Creating a temporary Robots object for calling the non-static add_robot method ******************
//             Robots temp_robot(0, "", 0, 0, "", "", 0, "scrub" , 0, 0);

//             // Call add_robot function using the temp_robot object
//             temp_robot.add_robot(robot_list);

//             // Output the status of the newly added robot if available
//             if (!robot_list.empty()) {
//                 cout << "\n--- Robot Status after Addition ---\n";
//                 robot_list.back().field_engineer_view_status();
//             } else {
//                 cout << "No robots were added." << endl;
//             }
//         } else if (action == "view_robot_status") {
//             // Assuming we already have a robot to view, normally you'd select which robot's status to view
//             Robots robot1(1, "Medium", 100, 90, "No Error", "Finished", 101, 
//                           Robots::robotFunction::SCRUB, 5, 5, startTime, endTime);
//             cout << "\n--- Viewing Robot Status ---\n";
//             robot1.field_engineer_view_status();
//         } else {
//             cout << "Invalid action entered." << endl;
//         }
//     } else {
//         cout << "Access denied. Only field engineers can perform actions." << endl;
//     }

//     return 0; // Return 0 to indicate successful execution
// }