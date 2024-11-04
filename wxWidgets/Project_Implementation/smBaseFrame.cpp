#include "smBaseFrame.hpp"
#include <wx/wx.h>

MySMBaseFrame::MySMBaseFrame(wxWindow* parent)
    : smBaseFrame(parent)  // Call the base class constructor
{
    // Connect the button event to the overridden method
    smButton->Bind(wxEVT_BUTTON, &MySMBaseFrame::OnSMButtonClick, this);
}

void MySMBaseFrame::OnSMButtonClick(wxCommandEvent& event)
{
    // Implement necessary button press logic here
    wxMessageBox("Senior Management Frame", "Info", wxOK | wxICON_INFORMATION);
}