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
    CheckSelections(); //checks if create robot button can be made accessible
}

// When user interacts with the function dropdown menu, make sure function is selected
void MyAddRobotFrame::OnRobotFunctionChoice(wxCommandEvent& event)
{
    isFunctionSelected = (robotFunctionDropdown->GetSelection() != wxNOT_FOUND);
    CheckSelections(); //checks if create robot button can be made accessible
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

    // Pass the robot description to feFrame's list box (if creating a new feFrame, will need to use refresh button, or will automtically refresh when addind/deleting a robot)
    my_feFrame->AddRobotToList(robotSize, robotFunction);

    // Trigger refresh event using the same event as remove robot button click (to mimic user pressing refresh button)
    my_feFrame->OnFERefreshButtonClick(event);

    // Close the AddRobotFrame after robot creation
    Close();
}
