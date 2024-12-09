#pragma once
#include "MyProjectBase.h"  // Include the generated base class
#include "../include/DataManager.h"
#include "baseFrame.hpp"

class DataManager;

class MyBaseFrame;

class MyBMBaseFrame : public bmBaseFrame
{
public:
    MyBMBaseFrame(wxWindow* parent, DataManager* dataManager, MyBaseFrame* baseFrame);

    void OnBMRefreshButtonClick(wxCommandEvent& event);

protected:

    // Method to add a task to the wxListBox that holds task info
    void AddTaskToList(const wxString& taskRoom, const RobotData& taskRobot);

    // Override virtual method for double clicking robot in wxListBox
    void OnRobotListBoxDClick(wxCommandEvent& event) override;

    // Override virtual method for double clicking task in wxListBox
    void OnTaskListBoxDClick(wxCommandEvent& event) override;

    void OnAddTaskButtonClick(wxCommandEvent& event) override;

    void OnChangeRoomAButtonClick(wxCommandEvent& event) override;

    void OnRoomTaskSelect(wxCommandEvent& event) override;


private:

    DataManager* dataManager;  // Pointer to the data manager

    MyBaseFrame* baseFrame;  // Pointer to the baseFrame

    bool isAvailable;

    int roomID;

};
