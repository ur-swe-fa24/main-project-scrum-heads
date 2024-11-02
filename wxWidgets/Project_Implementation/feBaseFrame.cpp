#include "feBaseFrame.hpp"
#include "addRobotFrame.hpp"
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
    // Add the robot description to the list of robots 
    robotListBox->Append(robotDescription);
}