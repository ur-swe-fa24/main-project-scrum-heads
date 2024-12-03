#include "addTaskFrame.hpp"
#include <wx/wx.h>

// Takes feBaseFrame as both a parent and a pointer to the frame so it can pass it data from the created robots
MyAddTaskFrame::MyAddTaskFrame(wxWindow* parent, wxListBox* robotListBox, wxListBox* taskListBox, DataManager* dataManager, MyBaseFrame* baseFrame)
    : addTaskFrame(parent), localRobotListBox(robotListBox), localTaskListBox(taskListBox), dataManager(dataManager), baseFrame(baseFrame) // Initializes values
{
    createTaskButton->Bind(wxEVT_BUTTON, &MyAddTaskFrame::OnCreateTaskButtonClick, this);

    // //obviously need to update this so the list boxes are updated with actual rooms and robot IDs, not just manual insertions
    roomSelectionListBox->Append("room1");
    // roomSelectionListBox->Append("room2");
    // robotSelectionListBox->Append("24");
    // robotSelectionListBox->Append("2");

    //replace with something like:
    // dataManager->GetAvailableRooms();
    // iterate through vector of rooms, need getters for room number, floor type, size so I can append
    
    //get available robots for task
    availableRobotVector = dataManager->GetAvailableRobots();
    //iterate through available robots and append options
    for (robots::Robots robot : availableRobotVector) {
        std::string robotID = std::to_string(robot.get_id());
        std::string robotSize = robot.get_size();
        std::string robotFunction = robot.get_function_type();
        std::string robotInfo = "ID: " + robotID + " (Size: " + robotSize + ", Function: " + robotFunction + ")";
        robotSelectionListBox->Append(robotInfo);
    }
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

    std::string robotInfoString = std::string(taskRobotAssignment.mb_str());

    //extracts robot ID number from robot info string
    size_t idPos = robotInfoString.find("ID: ");
    size_t idStart = idPos + 4; // Position right after "ID: "
    size_t idEnd = robotInfoString.find(" ", idStart); // Find the space after the ID number
    std::string robotIDString = robotInfoString.substr(idStart, idEnd - idStart);

    //NEED TO somehow get this parameter to be RobotData
    //maybe extract robot ID from the string, and then use that to find appropriate robot in RobotData vector from datamanager
    //or, maybe there's a GetStringSelection() equivalent that would be able to retrieve RobotData instead?

    // //convert robotID from wxString to string
    // std::string robotID = std::string(taskRobotAssignment.mb_str());
    // std::cout << robotID << std::endl;

    //get vector of RobotData from dataManager
    std::vector<RobotData>& robotVector = dataManager->GetRobots();

    //iterate through RobotData vector until finding appropriate robot
    for (RobotData& robot : robotVector) {
        if (robot.robotID == robotIDString)
        {
            targetRobot = robot;
            break;
        }
    }

    // // Pass the robot description to feFrame's list box (if creating a new feFrame, will need to use refresh button, or will automtically refresh when addind/deleting a robot)
    // my_feFrame->AddTaskToList(taskRoomAssignment, targetRobot);

    baseFrame->AddTaskToList(taskRoomAssignment, targetRobot);

    // // Trigger refresh event using the same event as remove robot button click (to mimic user pressing refresh button)
    // my_feFrame->OnFERefreshButtonClick(event);

    baseFrame->HandleRefreshButton(event, localRobotListBox, localTaskListBox);

    //automatically close task creation window
    Close();
}