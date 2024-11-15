#include <iostream>
#include "../DataManager.h"
#include "../wxWidgets/Project_Implementation/feBaseFrame.hpp"
#include <wx/wx.h>

class MyApp : public wxApp {
public:
    virtual bool OnInit() override {
        // Create the UI frame for adding robots
        MyFEBaseFrame* frame = new MyFEBaseFrame(nullptr);
        frame->Show(true);

        // Make sure the frame is displayed so that a robot can be added
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);

int main() {
    // Step 1: Launch the wxWidgets GUI
    MyApp app;

    // The user will add robot data via the UI here.
    // The MyFEBaseFrame class contains the add robot window, which allows the user to add the robot.
    // This action will trigger DataManager::AddRobot(), collecting data from the user.
    app.OnInit();

    // Step 2: Create DataManager instance, which automatically updates IDs from MongoDB
    DataManager manager;

    // Step 3: Print current IDs before adding a new robot
    std::cout << "Current IDs in the database:" << std::endl;
    for (int id : manager.GetAllIds()) {
        std::cout << id << " ";
    }
    std::cout << std::endl;

    // Step 4: After adding via UI, fetch and print all robots from DataManager
    std::vector<RobotData>& robots = manager.GetRobots();
    for (const RobotData& robot : robots) {
        std::cout << "Robot ID: " << robot.robotId << ", Size: " << std::string(robot.robotSize.mb_str())
                  << ", Function: " << std::string(robot.robotFunction.mb_str()) << std::endl;
    }

    // Step 5: Fetch the robots from the MongoDB database directly and print
    std::cout << "\nRobots from MongoDB:" << std::endl;
    manager.mongo_database.read_all_robots();  // Should print details of all robots

    return 0;
}
