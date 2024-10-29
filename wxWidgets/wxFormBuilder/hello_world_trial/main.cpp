#include "MyProjectBase.h"
#include "derivedFrame.hpp"
#include "newDerivedFrame.hpp"
#include <wx/wx.h>

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

// This is called on application startup/initialization, creates the main window
bool MyApp::OnInit()
{
    MyDerivedFrame* frame = new MyDerivedFrame(nullptr);
    // Frames are created hidden to allow filling them with content before showing all the content at once
    // Show() is necessary to show this hidden ontent
    frame->Show(true);

    // MyNewDerivedFrame* frame2 = new MyNewDerivedFrame(nullptr);
    // frame2->Show(true);
    // Returning true here allows the application to start running
    return true;
}

// This macro essentially functions as our main(). Takes the name of the application class
wxIMPLEMENT_APP(MyApp);
