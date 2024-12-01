#pragma once
#include "MyProjectBase.h"  // Include the generated base class
#include "../include/DataManager.h"

class DataManager;

class MyBMBaseFrame : public bmBaseFrame
{
public:
    MyBMBaseFrame(wxWindow* parent);

    // Method to add a robot to the wxListBox that holds robot info
    void AddRobotToList(const wxString& robotSize, const wxString& robotFunction);

    // Method to add a task to the wxListBox that holds task info
    void AddTaskToList(const wxString& taskRoom, const RobotData& taskRobot);

protected:

};
