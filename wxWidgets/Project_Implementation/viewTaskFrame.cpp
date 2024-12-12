#include "viewTaskFrame.hpp"
#include <wx/wx.h>

// Takes feBaseFrame as both a parent and a pointer to the frame so it can pass it data from the created robots
MyViewTaskFrame::MyViewTaskFrame(wxWindow* parent)
    : viewTaskFrame(parent)// Initializes values
{

}

void MyViewTaskFrame::SetTaskData(robots::Robots robot) {
    //make sure list boxes are clear
    roomTaskListBox->Clear();
    robotTaskListBox->Clear();

    //add task info
    //if robot is not working or task cancelled, don't include task percent
    if (robot.get_task_status() != "Available" && robot.get_task_status() != "Cancelled")
    {
        taskStatusPlaceholderText->SetLabel(std::to_string(robot.get_task_percent()) + "% complete, " + robot.get_task_status());
    }
    else
    {
        taskStatusPlaceholderText->SetLabel(robot.get_task_status());
    }
    Room room = robot.get_task_room();
    int roomID = room.getRoomNumber();
    roomTaskListBox->Append(std::to_string(roomID));
    robotTaskListBox->Append(std::to_string(robot.get_id()));
    Layout();
}