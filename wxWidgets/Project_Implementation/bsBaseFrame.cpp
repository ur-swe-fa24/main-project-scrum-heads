#include "bsBaseFrame.hpp"
#include <wx/wx.h>

MyBSBaseFrame::MyBSBaseFrame(wxWindow* parent)
    : bsBaseFrame(parent)  // Call the base class constructor
{
    // Connect the button event to the overridden method
    bsButton->Bind(wxEVT_BUTTON, &MyBSBaseFrame::OnBSButtonClick, this);
}

void MyBSBaseFrame::OnBSButtonClick(wxCommandEvent& event)
{
    // Implement necessary button press logic here
    wxMessageBox("Building Staff Frame", "Info", wxOK | wxICON_INFORMATION);
}