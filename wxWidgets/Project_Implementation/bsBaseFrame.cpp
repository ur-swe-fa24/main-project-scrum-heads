#include "bsBaseFrame.hpp"
#include "robotInfoFrame.hpp"
#include "addTaskFrame.hpp"
#include "viewTaskFrame.hpp"
#include <wx/wx.h>

MyBSBaseFrame::MyBSBaseFrame(wxWindow* parent, DataManager* dataManager, MyBaseFrame* baseFrame)
    : bsBaseFrame(parent), dataManager(dataManager), baseFrame(baseFrame)  // Call the base class constructor
{
    // Connect the button event to the overridden method
    bsRefreshButton->Bind(wxEVT_BUTTON, &MyBSBaseFrame::OnBSRefreshButtonClick, this);

    //this is just to refresh the info when opening a new window
    //right now its cutting off the text, not sure why, doesn't happen when automatically refreshing when adding/removing robots/tasks
    wxCommandEvent dummyEvent; // Create a dummy event
    OnBSRefreshButtonClick(dummyEvent); // Call the method with the dummy event
}

void MyBSBaseFrame::OnBSRefreshButtonClick(wxCommandEvent& event)
{
    baseFrame->HandleRefreshButton(event, robotListBox, taskListBox, roomListBox);
}

void MyBSBaseFrame::OnRobotListBoxDClick(wxCommandEvent& event)
{
    baseFrame->HandleRobotListBoxDClick(this, robotListBox, "BS");
}

void MyBSBaseFrame::OnTaskListBoxDClick(wxCommandEvent& event)
{
    baseFrame->HandleTaskListBoxDClick(this, taskListBox);
}

void MyBSBaseFrame::OnAddTaskButtonClick(wxCommandEvent& event)
{
    // Create and show the AddTaskFrame (window where field engineer can add tasks)
    // First this: makes the current feFrame the parent window of the created addTaskFrame
    // Second this: passes instance of feFrame as a pointer to itself, allowing created addTaskFrame to communicate directly with it
    // necessary for taking the robot info added in the addTaskFrame and transporting it to feBaseFrame where field engineer can view
    MyAddTaskFrame* addTaskFrame = new MyAddTaskFrame(this, robotListBox, taskListBox, roomListBox, dataManager, baseFrame, "BS");
    addTaskFrame->Show();
}

void MyBSBaseFrame::AddTaskToList(const wxString& roomSelection, const RobotData& robotSelection)
{
    baseFrame->AddTaskToList(roomSelection, robotSelection);
}