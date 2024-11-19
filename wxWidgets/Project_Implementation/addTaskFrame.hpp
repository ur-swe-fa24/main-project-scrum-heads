#pragma once
#include "MyProjectBase.h" // Generated base class
#include "feBaseFrame.hpp"

class MyAddTaskFrame : public addTaskFrame
{
public:
    MyAddTaskFrame(wxWindow* parent, MyFEBaseFrame* feFrame);

protected:

    void OnCreateTaskButtonClick(wxCommandEvent& event) override;

    MyFEBaseFrame* my_feFrame;

private:
    // Variables to track whether the appropriate task data has been initialized in dropdown menus
    bool isRobotSelected = false;
    bool isRoomSelected = false;

    // Method that checks the above boolean values are both set to true
    void CheckSelections();

    //NOTE: this is currently emulating addRobotFrame, but addRobotFrame uses dropdown menus
    //I'm not sure if dropdown menus work here, because will need to be dynamically fetching
    //available robots and rooms so can't predetermine the dropdown (number of items and contents)
};