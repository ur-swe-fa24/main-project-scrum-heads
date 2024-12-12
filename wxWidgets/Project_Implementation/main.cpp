#include "MyProjectBase.h"
#include "baseFrame.hpp"
#include "bmBaseFrame.hpp"
#include "bsBaseFrame.hpp"
#include "smBaseFrame.hpp"
#include "feBaseFrame.hpp"
#include <wx/wx.h>
#include "../include/DataManager.h"

class DataManager;

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
    DataManager dataManager;
};

// This is called on application startup/initialization, creates the main window
bool MyApp::OnInit()
{
    MyBaseFrame* frame = new MyBaseFrame(nullptr, &dataManager);
    // Frames are created hidden to allow filling them with content before showing all the content at once
    // Show() is necessary to show this hidden ontent
    frame->Show(true);

    

    return true;
}

// This macro essentially functions as our main(). Takes the name of the application class
wxIMPLEMENT_APP(MyApp);
