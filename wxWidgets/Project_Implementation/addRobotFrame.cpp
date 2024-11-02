#include "addRobotFrame.hpp"
#include <wx/wx.h>

// Takes feBaseFrame as both a parent and a pointer to the frame so it can pass it data from the created robots
MyAddRobotFrame::MyAddRobotFrame(wxWindow* parent, MyFEBaseFrame* feFrame)
    : AddRobotFrame(parent), my_feFrame(feFrame) // Initializes values
{
    // Bind event handlers for dropdown menu selections and button click
    robotSizeDropdown->Bind(wxEVT_CHOICE, &MyAddRobotFrame::OnRobotSizeChoice, this);
    robotFunctionDropdown->Bind(wxEVT_CHOICE, &MyAddRobotFrame::OnRobotFunctionChoice, this);
    createRobotButton->Bind(wxEVT_BUTTON, &MyAddRobotFrame::OnCreateRobotButtonClick, this);
}

// When user interacts with the size dropdown menu, make sure size is selected
void MyAddRobotFrame::OnRobotSizeChoice(wxCommandEvent& event)
{
    isSizeSelected = (robotSizeDropdown->GetSelection() != wxNOT_FOUND);
    CheckSelections();
}

// When user interacts with the function dropdown menu, make sure function is selected
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
    // Collect the selected robot size and function as wxString
    wxString robotSize = robotSizeDropdown->GetStringSelection();
    wxString robotFunction = robotFunctionDropdown->GetStringSelection();
    // From here, can share the generated robot with size and function
    // Will likely want to add robot ID number in future, figure out best way to control user input for that

    // Use wxLogMessage to log the creation for testing
    wxLogMessage("Robot created with size: %s and function: %s", robotSize, robotFunction);

    // // Temporary confirmation message
    // wxMessageBox("Robot Added Successfully", "Confirmation Message", wxOK | wxICON_INFORMATION);

    // Create robot description to show up on field engineer view of list of robots
    // Robot description also serving as a temporary/preliminary structure to represent how robot data might be cumulated here before being retrived by system manager
    wxString robotDescription = wxString::Format("Size: %s, Function: %s", robotSize, robotFunction);

    // Pass the robot description to feFrame's list box
    if (my_feFrame) {
        my_feFrame->AddRobotToList(robotDescription);
    }

    // Close the AddRobotFrame after robot creation
    Close();
}
