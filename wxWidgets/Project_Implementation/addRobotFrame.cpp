#include "addRobotFrame.hpp"
#include <wx/wx.h>

MyAddRobotFrame::MyAddRobotFrame(wxWindow* parent)
    : AddRobotFrame(parent)
{
    // Bind event handlers for dropdown menus and button click
    robotSizeDropdown->Bind(wxEVT_CHOICE, &MyAddRobotFrame::OnRobotSizeChoice, this);
    robotFunctionDropdown->Bind(wxEVT_CHOICE, &MyAddRobotFrame::OnRobotFunctionChoice, this);
    createRobotButton->Bind(wxEVT_BUTTON, &MyAddRobotFrame::OnCreateRobotButtonClick, this);
}

void MyAddRobotFrame::OnRobotSizeChoice(wxCommandEvent& event)
{
    isSizeSelected = (robotSizeDropdown->GetSelection() != wxNOT_FOUND);
    CheckSelections();
}

void MyAddRobotFrame::OnRobotFunctionChoice(wxCommandEvent& event)
{
    isFunctionSelected = (robotFunctionDropdown->GetSelection() != wxNOT_FOUND);
    CheckSelections();
}

void MyAddRobotFrame::CheckSelections()
{
    // Enable Create Robot button only if both selections are made
    createRobotButton->Enable(isSizeSelected && isFunctionSelected);
}

void MyAddRobotFrame::OnCreateRobotButtonClick(wxCommandEvent& event)
{
    // Collect the selected robot size and function
    wxString robotSize = robotSizeDropdown->GetString(robotSizeDropdown->GetSelection());
    wxString robotFunction = robotFunctionDropdown->GetString(robotFunctionDropdown->GetSelection());

    // Store or pass this data to other parts of the program as needed
    wxLogMessage("Robot created with size: %s and function: %s", robotSize, robotFunction);

    // Optionally, close the AddRobotFrame after robot creation
    Close();
}
