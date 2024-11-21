#pragma once
#include "MyProjectBase.h" // Generated base class
#include "feBaseFrame.hpp"

class MyAddTaskFrame : public addTaskFrame
{
public:
    MyAddTaskFrame(wxWindow* parent, MyFEBaseFrame* feFrame);

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
};