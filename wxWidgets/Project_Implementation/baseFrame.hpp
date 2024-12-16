#pragma once
#include "MyProjectBase.h"  // Include the generated base class
#include "bmBaseFrame.hpp"
#include "bsBaseFrame.hpp"
#include "smBaseFrame.hpp"
#include "feBaseFrame.hpp"
#include "DataManager.h"
#include "robotInfoFrame.hpp"
#include "viewTaskFrame.hpp"
#include "../include/DataManager.h"

class DataManager;

class MyBaseFrame : public baseFrame
{
public:

    MyBaseFrame(wxWindow* parent, DataManager* dataManager);

    //handles the selection of a robot from the robot list
    void HandleRobotListBoxDClick(wxWindow* parent, wxListBox* robotListBox, std::string userRole);

    //handles the selection of a task from the task list
    void HandleTaskListBoxDClick(wxWindow* parent, wxListBox* taskListBox);

    //handles pressing of the refresh button
    void HandleRefreshButton(wxCommandEvent& event, wxListBox* robotListBox, wxListBox* taskListBox, wxListBox* roomListBox);

    //handles adding a task to the task list
    void AddTaskToList(const wxString& roomSelection, const RobotData& robotSelection);

protected:
    // Override the virtual method for various button clicks
    void OnFESelectButtonClick(wxCommandEvent& event) override;
    void OnBMSelectButtonClick(wxCommandEvent& event) override;
    void OnBSSelectButtonClick(wxCommandEvent& event) override;
    void OnSMSelectButtonClick(wxCommandEvent& event) override;

    DataManager* dataManager; //pointer to DataManager
};
