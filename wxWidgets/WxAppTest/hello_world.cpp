// Taken from wxWidgets website, Hello World tutorial

// Start of wxWidgets "Hello World" Program

// Global include for wxWidgets' header files, includes common headers, not all
#include <wx/wx.h> 

// Class derives from wxApp
class MyApp : public wxApp
{
public:
    // Overrides initialization virtual function
    bool OnInit() override; 
};

// This macro essentially functions as our main(). Takes the name of the application class
wxIMPLEMENT_APP(MyApp);

// Main window of a typical application is a wxFrame object
class MyFrame : public wxFrame
{
public:
    MyFrame();
 
private:
    // These are event handlers
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};

// In order to be able to react to a menu command, must be given a unique identifier, often defined as an enum element
// Do not need to define identifiers for About and Exit (so just Hello), because wsWidgets predefines these (as wxID_ABOUT and wxID_EXIT)
enum
{
    ID_Hello = 1
};

// This is called on application startup/initialization, creates the main window
bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame();
    // Frames are created hidden to allow filling them with content before showing all the content at once
    // Show() is necessary to show this hidden ontent
    frame->Show(true);
    // Returning true here allows the application to start running
    return true;
}
 
MyFrame::MyFrame()
    : wxFrame(nullptr, wxID_ANY, "Hello World")
{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
                     "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
 
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
 
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
 
    SetMenuBar( menuBar );
 
    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");
 
    // Bind() connects event handlers to the events we want to handle in them
    // Sends all the menu elements (identified by wxEVT_MENU event type) to the given function
    // Parameteres: (event type, pointer to the method to call, object to call it on (uses "this" here), and optional identifier)
    Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
}

// Standard implementation for OnExit. Closes the main window by calling Close()
// Parameter "true" indicates that other windows have no veto power (i.e. "Do you really want to close?")
// If there is no other main window left, the application will quit
void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}
 
// Standard implementation for OnAbout. Displays a small window with some text in it
// In order to see this, when running application go to top toolbar, select app dropdown, and click About
void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a wxWidgets Hello World example",
                 "About Hello World", wxOK | wxICON_INFORMATION);
}

// Implementation of custom menu command handler performs whatever task necessary, here just displaying a message
void MyFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets!");
}