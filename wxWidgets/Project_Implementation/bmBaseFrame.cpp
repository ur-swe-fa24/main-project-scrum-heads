#include "bmBaseFrame.hpp"
#include "robotInfoFrame.hpp"
#include "addTaskFrame.hpp"
#include "viewTaskFrame.hpp"
#include <wx/wx.h>

MyBMBaseFrame::MyBMBaseFrame(wxWindow* parent, DataManager* dataManager, MyBaseFrame* baseFrame)
    : bmBaseFrame(parent), dataManager(dataManager), baseFrame(baseFrame)  // Call the base class constructor
{
    // Connect the button event to the overridden method
    bmRefreshButton->Bind(wxEVT_BUTTON, &MyBMBaseFrame::OnBMRefreshButtonClick, this);

    //this is just to refresh the info when opening a new window
    //right now its cutting off the text, not sure why, doesn't happen when automatically refreshing when adding/removing robots/tasks
    wxCommandEvent dummyEvent; // Create a dummy event
    OnBMRefreshButtonClick(dummyEvent); // Call the method with the dummy event
}

void MyBMBaseFrame::OnBMRefreshButtonClick(wxCommandEvent& event)
{
    baseFrame->HandleRefreshButton(event, robotListBox, taskListBox, roomListBox);
}

void MyBMBaseFrame::OnRobotListBoxDClick(wxCommandEvent& event)
{
    baseFrame->HandleRobotListBoxDClick(this, robotListBox, "BM");
}

void MyBMBaseFrame::OnTaskListBoxDClick(wxCommandEvent& event)
{
    baseFrame->HandleTaskListBoxDClick(this, taskListBox);
}

void MyBMBaseFrame::OnAddTaskButtonClick(wxCommandEvent& event)
{
    // Create and show the AddTaskFrame (window where field engineer can add tasks)
    // First this: makes the current feFrame the parent window of the created addTaskFrame
    // Second this: passes instance of feFrame as a pointer to itself, allowing created addTaskFrame to communicate directly with it
    // necessary for taking the robot info added in the addTaskFrame and transporting it to feBaseFrame where field engineer can view
    MyAddTaskFrame* addTaskFrame = new MyAddTaskFrame(this, robotListBox, taskListBox, roomListBox, dataManager, baseFrame, "BM");
    addTaskFrame->Show();
}

void MyBMBaseFrame::AddTaskToList(const wxString& roomSelection, const RobotData& robotSelection)
{
    baseFrame->AddTaskToList(roomSelection, robotSelection);
}

void MyBMBaseFrame::OnRoomTaskSelect(wxCommandEvent& event)
{
    changeAvailabilityButton->Disable();
    wxString taskRoomAssignment = roomListBox->GetStringSelection();
    std::string roomInfoString = std::string(taskRoomAssignment.mb_str());

    //extracts room ID number from room info string
    size_t RoomIdPos = roomInfoString.find("ID: ");
    size_t RoomIdStart = RoomIdPos + 4; // Position right after "ID: "
    size_t RoomIdEnd = roomInfoString.find(" ", RoomIdStart); // Find the space after the ID number
    std::string roomIDString = roomInfoString.substr(RoomIdStart, RoomIdEnd - RoomIdStart);
    roomID = std::stoi(roomIDString);

    //temporary room placeholder
    Room selectedRoom(0, "", "", "");

    //get full room
    std::vector<Room> rooms = dataManager->GetRooms();
    for (Room room : rooms)
    {
        if (room.getRoomNumber() == roomID)
        {
            selectedRoom = room;
            break;
        }
    }

    //if available or unavailable (i.e. not busy), enable change button
    //set bool accordingly
    if (selectedRoom.getAvailability() == "Available")
    {
        isAvailable = true;
        changeAvailabilityButton->Enable();
    }
    else if (selectedRoom.getAvailability() == "Unavailable")
    {
        isAvailable = false;
        changeAvailabilityButton->Enable();
    }

}

void MyBMBaseFrame::OnChangeRoomAButtonClick(wxCommandEvent& event)
{
    dataManager->ChangeRoomAvailability(roomID, isAvailable);

    //refresh after availability is changed
    baseFrame->HandleRefreshButton(event, robotListBox, taskListBox, roomListBox);
    changeAvailabilityButton->Disable();
}