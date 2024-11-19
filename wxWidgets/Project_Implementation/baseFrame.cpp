#include "baseFrame.hpp"
#include "bmBaseFrame.hpp"
#include "bsBaseFrame.hpp"
#include "smBaseFrame.hpp"
#include "feBaseFrame.hpp"
#include "DataManager.h"
#include <wx/wx.h>

DataManager dataManager; //create single shared instance of dataManager

MyBaseFrame::MyBaseFrame(wxWindow* parent)
    : baseFrame(parent)  // Call the base class constructor
{
    // Connect the button event to the overridden method
    feSelectButton->Bind(wxEVT_BUTTON, &MyBaseFrame::OnFESelectButtonClick, this);
    smSelectButton->Bind(wxEVT_BUTTON, &MyBaseFrame::OnSMSelectButtonClick, this);
    bsSelectButton->Bind(wxEVT_BUTTON, &MyBaseFrame::OnBSSelectButtonClick, this);
    bmSelectButton->Bind(wxEVT_BUTTON, &MyBaseFrame::OnBMSelectButtonClick, this);
}

void MyBaseFrame::OnFESelectButtonClick(wxCommandEvent& event)
{
    // Implement necessary button press logic here
    // wxMessageBox("Field Engineer Frame", "Info", wxOK | wxICON_INFORMATION);
    // DataManager dataManager; //create single shared instance of dataManager
    MyFEBaseFrame* feFrame = new MyFEBaseFrame(nullptr, &dataManager);

    //here is where I would interact with the system manager to fetch all the necessary data I need,
    //since it's here that the feFrame is created

    // wxString sampleText = "Hello, Field Engineer!";
    // feFrame->SetText(sampleText);  // Set the text in feFrame’s text control
    
    feFrame->Show(true);
}

void MyBaseFrame::OnSMSelectButtonClick(wxCommandEvent& event)
{
    // Implement necessary button press logic here
    // wxMessageBox("Senior Management Frame", "Info", wxOK | wxICON_INFORMATION);
    MySMBaseFrame* smFrame = new MySMBaseFrame(nullptr);
    smFrame->Show(true);
}

void MyBaseFrame::OnBSSelectButtonClick(wxCommandEvent& event)
{
    // Implement necessary button press logic here
    // wxMessageBox("Building Staff Frame", "Info", wxOK | wxICON_INFORMATION);
    MyBSBaseFrame* bsFrame = new MyBSBaseFrame(nullptr);
    bsFrame->Show(true);
}

void MyBaseFrame::OnBMSelectButtonClick(wxCommandEvent& event)
{
    // Implement necessary button press logic here
    // wxMessageBox("Building Manager Frame", "Info", wxOK | wxICON_INFORMATION);
    MyBMBaseFrame* bmFrame = new MyBMBaseFrame(nullptr);
    bmFrame->Show(true);
}
