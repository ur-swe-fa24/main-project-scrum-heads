#include "derivedFrame.hpp"
#include <wx/wx.h>

MyDerivedFrame::MyDerivedFrame(wxWindow* parent)
    : MyFrame1(parent)  // Call the base class constructor
{
    // Connect the button event to the overridden method
    testButton->Bind(wxEVT_BUTTON, &MyDerivedFrame::testButtonOnButtonClick, this);
}

void MyDerivedFrame::testButtonOnButtonClick(wxCommandEvent& event)
{
    // Implement your custom logic here
    wxMessageBox("Button clicked from derived frame!", "Info", wxOK | wxICON_INFORMATION);
    std::cout << "test" << std::endl;
}
