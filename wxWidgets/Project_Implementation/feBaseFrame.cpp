#include "feBaseFrame.hpp"
#include <wx/wx.h>

MyFEBaseFrame::MyFEBaseFrame(wxWindow* parent)
    : feBaseFrame(parent)  // Call the base class constructor
{
    // Connect the button event to the overridden method
    feButton->Bind(wxEVT_BUTTON, &MyFEBaseFrame::OnFEButtonClick, this);
}

void MyFEBaseFrame::OnFEButtonClick(wxCommandEvent& event)
{
    // Implement necessary button press logic here
    wxMessageBox("Field Engineer Frame", "Info", wxOK | wxICON_INFORMATION);
}