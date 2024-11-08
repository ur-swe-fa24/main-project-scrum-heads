#include "bmBaseFrame.hpp"
#include <wx/wx.h>

MyBMBaseFrame::MyBMBaseFrame(wxWindow* parent)
    : bmBaseFrame(parent)  // Call the base class constructor
{
    // Connect the button event to the overridden method
    bmButton->Bind(wxEVT_BUTTON, &MyBMBaseFrame::OnBMButtonClick, this);
}

void MyBMBaseFrame::OnBMButtonClick(wxCommandEvent& event)
{
    // Implement necessary button press logic here
    wxMessageBox("Building Manager Frame", "Info", wxOK | wxICON_INFORMATION);
}