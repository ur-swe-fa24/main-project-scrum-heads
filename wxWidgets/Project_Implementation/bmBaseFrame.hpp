#pragma once
#include "MyProjectBase.h"  // Include the generated base class
#include "../include/DataManager.h"
#include "baseFrame.hpp"

class DataManager;

class MyBaseFrame;

class MyBMBaseFrame : public bmBaseFrame
{
public:
    MyBMBaseFrame(wxWindow* parent, MyBaseFrame* baseFrame);

    void OnBMRefreshButtonClick(wxCommandEvent& event);

protected:
    // Method to add a robot to the wxListBox that holds robot info
    void AddRobotToList(const wxString& robotSize, const wxString& robotFunction);

    // Method to add a task to the wxListBox that holds task info
    void AddTaskToList(const wxString& taskRoom, const RobotData& taskRobot);

    // Override virtual method for double clicking robot in wxListBox
    void OnRobotListBoxDClick(wxCommandEvent& event) override;

    // Override virtual method for double clicking task in wxListBox
    void OnTaskListBoxDClick(wxCommandEvent& event) override;


private:

    MyBaseFrame* baseFrame;  // Pointer to the baseFrame

};
