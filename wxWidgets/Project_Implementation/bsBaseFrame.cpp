#include "bsBaseFrame.hpp"
#include "robotInfoFrame.hpp"
#include "addTaskFrame.hpp"
#include "viewTaskFrame.hpp"
#include <wx/wx.h>

MyBSBaseFrame::MyBSBaseFrame(wxWindow* parent)
    : bsBaseFrame(parent)  // Call the base class constructor
{

}

// void MyBSBaseFrame::OnBSButtonClick(wxCommandEvent& event)
// {
//     // Implement necessary button press logic here
//     wxMessageBox("Building Staff Frame", "Info", wxOK | wxICON_INFORMATION);
// }