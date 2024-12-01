#include "bmBaseFrame.hpp"
#include "robotInfoFrame.hpp"
#include "addTaskFrame.hpp"
#include "viewTaskFrame.hpp"
#include <wx/wx.h>

MyBMBaseFrame::MyBMBaseFrame(wxWindow* parent)
    : bmBaseFrame(parent)  // Call the base class constructor
{

}

// // void MyBMBaseFrame::OnBMButtonClick(wxCommandEvent& event)
// // {
// //     // Implement necessary button press logic here
// //     wxMessageBox("Building Manager Frame", "Info", wxOK | wxICON_INFORMATION);
// // }

// void MyBMBaseFrame::OnRobotListBoxDClick(wxCommandEvent& event)
// {
//     //retrieves the updated vector of RobotData
//     std::vector<RobotData>& robots = dataManager->GetRobots();

//     int selectionIndex = robotListBox->GetSelection(); //gets the selection index of whichever robot you clicked on in the wxListBox

//     //if selection index is found and smaller than vector of RobotData (should always be the case)
//     if (selectionIndex != wxNOT_FOUND && selectionIndex < robots.size()) {

//         RobotData selectedRobot = robots[selectionIndex]; //finds the coordinated robot from the robots vector

//         //converts robot ID to integer to use as key for database
//         int robotId = std::stoi(selectedRobot.robotID);

//         //complete robot information, accessed using the robot's ID
//         const robots::Robots& completeRobot = dataManager->GetAllRobotInfo(robotId);

//         // Create robotInfoFrame, passes through string to function as title to display robotID (not currently implemented visually)
//         //also passed through the completed robot information (full robot class info) and instance of dataManager
//         MyRobotInfoFrame* infoFrame = new MyRobotInfoFrame(this, "Robot ID: " + selectedRobot.robotID, completeRobot, dataManager);
//         // Set the appropriate data and show the frame
//         infoFrame->SetRobotData(completeRobot);
//         infoFrame->Show();
//     }
// }

// void MyBMBaseFrame::OnTaskListBoxDClick(wxCommandEvent& event)
// {
//     //implement logic to open task info window by double clicking task here
//     //retrieves the updated vector of RobotData
//     std::vector<TaskData>& tasks = dataManager->GetTasks();

//     int selectionIndex = taskListBox->GetSelection(); //gets the selection index of whichever robot you clicked on in the wxListBox

//     //if selection index is found and smaller than vector of RobotData (should always be the case)
//     if (selectionIndex != wxNOT_FOUND && selectionIndex < tasks.size()) {

//         TaskData selectedTask = tasks[selectionIndex]; //finds the coordinated task from the tasks vector

//         wxString taskStatus = "need to get task status here";

//         // Create viewTaskFrame
//         MyViewTaskFrame* taskInfoFrame = new MyViewTaskFrame(this, this);
    
//         //converts robot ID to integer to use as key for database
//         int robotId = std::stoi(selectedTask.taskRobot.robotID);

//         //complete robot information, accessed using the robot's ID
//         const robots::Robots& completeRobot = dataManager->GetAllRobotInfo(robotId);

//         taskInfoFrame->SetTaskData(completeRobot);

//         taskInfoFrame->Show();
//     }
// }

// void MyBMBaseFrame::OnAddTaskButtonClick(wxCommandEvent& event)
// {
//     // Create and show the AddTaskFrame (window where field engineer can add tasks)
//     // First this: makes the current feFrame the parent window of the created addTaskFrame
//     // Second this: passes instance of feFrame as a pointer to itself, allowing created addTaskFrame to communicate directly with it
//     // necessary for taking the robot info added in the addTaskFrame and transporting it to feBaseFrame where field engineer can view
//     MyAddTaskFrame* addTaskFrame = new MyAddTaskFrame(this, this, dataManager);
//     addTaskFrame->Show();
// }

// void MyBMBaseFrame::AddTaskToList(const wxString& roomSelection, const RobotData& robotSelection)
// {
//     //create robot with user-specified size and function. ID string created as 0, actually assigned in DataManager::AddRobot()
//     TaskData task = {roomSelection, robotSelection};

//     //adds created task to vector of TaskData in data manager
//     dataManager->AddTask(task);

//     wxMessageBox("Task created in room: " + roomSelection + ", using robot with ID: " + robotSelection.robotID, "Success!", wxOK | wxICON_INFORMATION);

//     //task is actually appended to the list on refresh button click, which is being called in the addTaskFrame
// }