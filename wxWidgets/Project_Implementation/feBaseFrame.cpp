#include "feBaseFrame.hpp"
#include "addRobotFrame.hpp"
#include "robotInfoFrame.hpp"
#include "addTaskFrame.hpp"
#include "viewTaskFrame.hpp"
#include <wx/wx.h>

// #include "DataManager.hpp"  // need for data manager

MyFEBaseFrame::MyFEBaseFrame(wxWindow* parent, DataManager* dataManager, MyBaseFrame* baseFrame)
    : feBaseFrame(parent), dataManager(dataManager), baseFrame(baseFrame)  // Call the base class constructor
{
    
    // Connect the button event to the overridden method
    feRefreshButton->Bind(wxEVT_BUTTON, &MyFEBaseFrame::OnFERefreshButtonClick, this);

    //this is just to refresh the info when opening a new window
    //right now its cutting off the text, not sure why, doesn't happen when automatically refreshing when adding/removing robots/tasks
    wxCommandEvent dummyEvent; // Create a dummy event
    OnFERefreshButtonClick(dummyEvent); // Call the method with the dummy event
}

void MyFEBaseFrame::OnFERefreshButtonClick(wxCommandEvent& event)
{
    baseFrame->HandleRefreshButton(event, robotListBox, taskListBox, roomListBox);
}

void MyFEBaseFrame::OnAddRobotButtonClick(wxCommandEvent& event)
{
    // Create and show the AddRobotFrame (window where field engineer can add robots)
    // First this: makes the current feFrame the parent window of the created addRobotFrame
    // Second this: passes instance of feFrame as a pointer to itself, allowing created addRobotFrame to communicate directly with it
    // necessary for taking the robot info added in the addRobotFrame and transporting it to feBaseFrame where field engineer can view
    MyAddRobotFrame* addRobotFrame = new MyAddRobotFrame(this, this);
    addRobotFrame->Show(true);
}

void MyFEBaseFrame::AddRobotToList(const wxString& robotSize, const wxString& robotFunction)
{
    //create robot with user-specified size and function. ID string created as 0, actually assigned in DataManager::AddRobot()
    RobotData robot = {"0", robotSize, robotFunction};
    //adds created robot to vector of RobotData in data manager
    dataManager->AddRobot(robot);

    //gets actual assigned robot ID as string to print out for user
    std::string idString = dataManager->GetIDString();

    wxMessageBox("Robot created with ID: " + idString, "Success!", wxOK | wxICON_INFORMATION);

    //robot is actually appended to the list on refresh button click, which is being called in the addRobotFrame
}

void MyFEBaseFrame::OnRobotListBoxDClick(wxCommandEvent& event)
{
    baseFrame->HandleRobotListBoxDClick(this, robotListBox, "FE");
}

void MyFEBaseFrame::OnTaskListBoxDClick(wxCommandEvent& event)
{
    baseFrame->HandleTaskListBoxDClick(this, taskListBox);
}

void MyFEBaseFrame::OnAddTaskButtonClick(wxCommandEvent& event)
{
    // Create and show the AddTaskFrame (window where field engineer can add tasks)
    // First this: makes the current feFrame the parent window of the created addTaskFrame
    // Second this: passes instance of feFrame as a pointer to itself, allowing created addTaskFrame to communicate directly with it
    // necessary for taking the robot info added in the addTaskFrame and transporting it to feBaseFrame where field engineer can view
    MyAddTaskFrame* addTaskFrame = new MyAddTaskFrame(this, robotListBox, taskListBox, roomListBox, dataManager, baseFrame, "FE");
    addTaskFrame->Show();
}

void MyFEBaseFrame::AddTaskToList(const wxString& roomSelection, const RobotData& robotSelection)
{
    //task is actually appended to the list on refresh button click, which is being called in the addTaskFrame

    baseFrame->AddTaskToList(roomSelection, robotSelection);
}
