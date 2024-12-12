#pragma once
#include "MyProjectBase.h" // Generated base class
#include "feBaseFrame.hpp"

class MyAddTaskFrame : public addTaskFrame
{
public:
    MyAddTaskFrame(wxWindow* parent, wxListBox* robotListBox, wxListBox* taskListBox, wxListBox* roomListBox,DataManager* dataManager, MyBaseFrame* baseFrame, std::string userRole);


protected:
    //override button
    void OnCreateTaskButtonClick(wxCommandEvent& event) override;

    MyFEBaseFrame* my_feFrame;

    // Event corresponding to user selecting something from room list
    void OnRoomTaskSelect(wxCommandEvent& event) override;
    // Event corresponding to user selecting something from robot list
    void OnRobotTaskSelect(wxCommandEvent& event) override;

private:
    // Variables to track whether the appropriate task data has been initialized in dropdown menus
    bool isRobotSelected = false;
    bool isRoomSelected = false;

    // Method that checks the above boolean values are both set to true
    void CheckSelections();

    //pointer to dataManager
    DataManager* dataManager;

    //variable to hold target robot to display UI info when giving robot a task
    RobotData targetRobot;

    //vector to hold available robots
    std::vector <robots::Robots> availableRobotVector;

    //vector to hold available rooms
    std::vector <Room> availableRoomsVector;

    //pointers to list boxes
    wxListBox* localRobotListBox;
    wxListBox* localTaskListBox;
    wxListBox* localRoomListBox;

    MyBaseFrame* baseFrame;  // Pointer to the baseFrame

    std::string userRole;
};