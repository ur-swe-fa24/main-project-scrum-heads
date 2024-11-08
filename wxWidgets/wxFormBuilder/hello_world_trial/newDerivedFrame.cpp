#include "newDerivedFrame.hpp"
#include <wx/wx.h>

MyNewDerivedFrame::MyNewDerivedFrame(wxWindow* parent)
    : MyFrame2(parent)  // Call the base class constructor
{
    // Connect the button event to the overridden method
    testButton2->Bind(wxEVT_BUTTON, &MyNewDerivedFrame::testButtonOnButtonClick, this);
}

void MyNewDerivedFrame::testButtonOnButtonClick(wxCommandEvent& event)
{
    // Implement necessary button press logic here
    wxMessageBox("Second window test", "Info", wxOK | wxICON_INFORMATION);
}