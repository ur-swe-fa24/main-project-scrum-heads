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
    // Create and show the AddRobotFrame
    MyAddRobotFrame* addRobotFrame = new MyAddRobotFrame(this);
    addRobotFrame->Show(true);
}

void MyFEBaseFrame::SetText(const wxString& text)
{
    feTextControl->SetValue(text);  // Update text in feTextCtrl
}