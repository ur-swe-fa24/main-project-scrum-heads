#include "addTaskFrame.hpp"
#include <wx/wx.h>

// Takes feBaseFrame as both a parent and a pointer to the frame so it can pass it data from the created robots
MyAddTaskFrame::MyAddTaskFrame(wxWindow* parent, MyFEBaseFrame* feFrame)
    : addTaskFrame(parent), my_feFrame(feFrame) // Initializes values
{
    createTaskButton->Bind(wxEVT_BUTTON, &MyAddTaskFrame::OnCreateTaskButtonClick, this);
}

//some function to check room selected for task (change isRoomSelected), calls CheckSelections when done
//some function to check robot assigned for task (change isRobotSelected), calls CheckSelections when done

void MyAddTaskFrame::CheckSelections()
{
    createTaskButton->Enable(isRoomSelected && isRobotSelected);
}

void MyAddTaskFrame::OnCreateTaskButtonClick(wxCommandEvent& event)
{
    //implement logic for creating task on button click, must first validate that selection have been made


    // Trigger refresh event using the same event as remove robot button click (to mimic user pressing refresh button)
    my_feFrame->OnFERefreshButtonClick(event);

    //automatically close task creation window
    Close();
}