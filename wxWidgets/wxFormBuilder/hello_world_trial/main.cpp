#include "MyProjectBase.h"
#include <wx/app.h>

class MyApp : public wxApp
{
public:
    virtual bool OnInit()
    {
        MyFrame1* frame = new MyFrame1(NULL, wxID_ANY, "WxFormBuilder Test");
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);
