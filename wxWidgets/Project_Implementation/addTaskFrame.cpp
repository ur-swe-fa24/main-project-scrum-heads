#include "addTaskFrame.hpp"
#include <wx/wx.h>

// Takes feBaseFrame as both a parent and a pointer to the frame so it can pass it data from the created robots
MyAddTaskFrame::MyAddTaskFrame(wxWindow* parent, MyFEBaseFrame* feFrame)
    : addTaskFrame(parent), my_feFrame(feFrame) // Initializes values
{
    createTaskButton->Bind(wxEVT_BUTTON, &MyAddTaskFrame::OnCreateTaskButtonClick, this);
    roomSelectionListBox->Append("room1");
    roomSelectionListBox->Append("room2");
    robotSelectionListBox->Append("robot1");
    robotSelectionListBox->Append("robot2");
}

void MyAddTaskFrame::OnRoomTaskSelect(wxCommandEvent& event)
{
    isRoomSelected = (roomSelectionListBox->GetSelection() != wxNOT_FOUND);
    CheckSelections(); //checks if create task button can be made accessible
}

void MyAddTaskFrame::OnRobotTaskSelect(wxCommandEvent& event)
{
    isRobotSelected = (robotSelectionListBox->GetSelection() != wxNOT_FOUND);
    CheckSelections(); //checks if create task button can be made accessible
}

void MyAddTaskFrame::CheckSelections()
{
    createTaskButton->Enable(isRoomSelected && isRobotSelected);
}

void MyAddTaskFrame::OnCreateTaskButtonClick(wxCommandEvent& event)
{
    //implement logic for creating task on button click, must first validate that selections have been made


    wxString taskRoomAssignment = roomSelectionListBox->GetStringSelection();
    wxString taskRobotAssignment = robotSelectionListBox->GetStringSelection();

    // Pass the robot description to feFrame's list box (if creating a new feFrame, will need to use refresh button, or will automtically refresh when addind/deleting a robot)
    my_feFrame->AddTaskToList(taskRoomAssignment, taskRobotAssignment);

    // Trigger refresh event using the same event as remove robot button click (to mimic user pressing refresh button)
    my_feFrame->OnFERefreshButtonClick(event);

    //automatically close task creation window
    Close();
}