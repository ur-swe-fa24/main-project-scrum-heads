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


// struct RobotData {
//     wxString robotSize;
//     wxString robotFunction;
// };

class DataManager;

class MyBaseFrame : public baseFrame
{
public:
    MyBaseFrame(wxWindow* parent, DataManager* dataManager);

    void HandleRobotListBoxDClick(wxWindow* parent, wxListBox* robotListBox, std::string userRole);

    void HandleTaskListBoxDClick(wxWindow* parent, wxListBox* taskListBox);

    void HandleRefreshButton(wxCommandEvent& event, wxListBox* robotListBox, wxListBox* taskListBox, wxListBox* roomListBox);

    void AddTaskToList(const wxString& roomSelection, const RobotData& robotSelection);

protected:
    // Override the virtual method for various button clicks
    void OnFESelectButtonClick(wxCommandEvent& event) override;
    void OnBMSelectButtonClick(wxCommandEvent& event) override;
    void OnBSSelectButtonClick(wxCommandEvent& event) override;
    void OnSMSelectButtonClick(wxCommandEvent& event) override;

    DataManager* dataManager; //pointer to DataManager

    // MyBaseFrame* localBaseFrame; //pointer to BaseFrame
};
