#include "derivedFrame.hpp"
#include "newDerivedFrame.hpp"
#include <wx/wx.h>

MyDerivedFrame::MyDerivedFrame(wxWindow* parent)
    : MyFrame1(parent)  // Call the base class constructor
{
    // Connect the button event to the overridden method
    testButton1->Bind(wxEVT_BUTTON, &MyDerivedFrame::testButtonOnButtonClick, this);
}

void MyDerivedFrame::testButtonOnButtonClick(wxCommandEvent& event)
{
    // Implement necessary button press logic here
    wxMessageBox("Button clicked from derived frame!", "Info", wxOK | wxICON_INFORMATION);

    MyNewDerivedFrame* frame2 = new MyNewDerivedFrame(nullptr);
    frame2->Show(true);
}
