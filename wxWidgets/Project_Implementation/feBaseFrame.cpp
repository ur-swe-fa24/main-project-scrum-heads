#include "feBaseFrame.hpp"
#include "addRobotFrame.hpp"
#include "robotInfoFrame.hpp"
#include <wx/wx.h>

MyFEBaseFrame::MyFEBaseFrame(wxWindow* parent)
    : feBaseFrame(parent)  // Call the base class constructor
{
    // Connect the button event to the overridden method
    feButton->Bind(wxEVT_BUTTON, &MyFEBaseFrame::OnFEButtonClick, this);
    
    // Connect the button event to the overridden method
    feRefreshButton->Bind(wxEVT_BUTTON, &MyFEBaseFrame::OnFERefreshButtonClick, this);
}

void MyFEBaseFrame::OnFEButtonClick(wxCommandEvent& event)
{
    // Implement necessary button press logic here
    wxMessageBox("Field Engineer Frame", "Info", wxOK | wxICON_INFORMATION);
}

void MyFEBaseFrame::OnFERefreshButtonClick(wxCommandEvent& event)
{
    // Implement necessary button press logic here
    wxMessageBox("Refresh", "Info", wxOK | wxICON_INFORMATION);
}

void MyFEBaseFrame::OnAddRobotButtonClick(wxCommandEvent& event)
{
    // Create and show the AddRobotFrame (window where field engineer can add robots)
    // First this: makes the current feFrame the parent window of the created addRobotFrame
    // Second this: passes instance of feFrame as a pointer to itself, allowing created addRobotFrame to communicate directly with it
    // necessary for taking the robot info added in the addRobotFrame and transporting it to feBaseFrame where field engineer can view
    MyAddRobotFrame* addRobotFrame = new MyAddRobotFrame(this, this);
    addRobotFrame->Show(true);
}

void MyFEBaseFrame::SetText(const wxString& text)
{
    feTextControl->SetValue(text);  // Update text in feTextCtrl
}

void MyFEBaseFrame::AddRobotToList(const wxString& robotDescription)
{
    // //add robotDescription (currently just properties, so size and function) to robots vector
    RobotData robot = {robotDescription};
    robots.push_back(robot);

    // Add the robot description to the list of robots 
    robotListBox->Append(robotDescription);
}

void MyFEBaseFrame::OnRobotListBoxDClick(wxCommandEvent& event)
{
    //note: the exact logic here will change such that when a user clicks on a robot it accesses it's ID and then retrives the necessary data
    int selectionIndex = robotListBox->GetSelection(); //gets the selection index of whichever robot you clicked on in the wxListBox
    if (selectionIndex != wxNOT_FOUND && selectionIndex < robots.size()) {
        RobotData selectedRobot = robots[selectionIndex]; //finds the coordinated robot from the robots vector

        // Create robotInfoFrame
        MyRobotInfoFrame* infoFrame = new MyRobotInfoFrame(this, "Robot ID: ");
        // Set the appropriate data and show the frame
        infoFrame->SetRobotData(selectedRobot.robotPropertyData);
        infoFrame->Show();
    }
}