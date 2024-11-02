#include "addRobotFrame.hpp"
#include <wx/wx.h>

MyAddRobotFrame::MyAddRobotFrame(wxWindow* parent, MyFEBaseFrame* feFrame)
    : AddRobotFrame(parent), my_feFrame(feFrame)
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
    wxString robotSize = robotSizeDropdown->GetStringSelection();
    wxString robotFunction = robotFunctionDropdown->GetStringSelection();
    // From here, can share the generated robot with size and function

    // Temp confirmation message
    wxMessageBox("Robot Added Successfully", "Confirmation Message", wxOK | wxICON_INFORMATION);

    wxString robotDescription = wxString::Format("Size: %s, Function: %s", robotSize, robotFunction);
    // Use wxLogMessage to log the creation for feedback
    wxLogMessage("Robot created with size: %s and function: %s", robotSize, robotFunction);

    // Pass the robot description to feFrame's list box
    if (my_feFrame) {
        my_feFrame->AddRobotToList(robotDescription);
    }

    // Close the AddRobotFrame after robot creation
    Close();
}
