#include "MyProjectBase.h"
#include "derivedFrame.hpp"
#include <wx/wx.h>

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

bool MyApp::OnInit()
{
    MyDerivedFrame* frame = new MyDerivedFrame(nullptr);
    frame->Show(true);
    return true;
}

wxIMPLEMENT_APP(MyApp);
