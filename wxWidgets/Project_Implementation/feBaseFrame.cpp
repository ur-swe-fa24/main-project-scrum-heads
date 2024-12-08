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
    // feButton->Bind(wxEVT_BUTTON, &MyFEBaseFrame::OnFEButtonClick, this);
    
    // Connect the button event to the overridden method
    feRefreshButton->Bind(wxEVT_BUTTON, &MyFEBaseFrame::OnFERefreshButtonClick, this);

    //this is just to refresh the info when opening a new window
    //right now its cutting off the text, not sure why, doesn't happen when automatically refreshing when adding/removing robots/tasks
    wxCommandEvent dummyEvent; // Create a dummy event
    OnFERefreshButtonClick(dummyEvent); // Call the method with the dummy event

    // Pass this frame instance to DataManager
    // DataManager* dataManager = new DataManager(this); 
    // bindEvents();
}

// void MyFEBaseFrame::OnFEButtonClick(wxCommandEvent& event)
// {
//     // Implement necessary button press logic here
//     wxMessageBox("Field Engineer Frame", "Info", wxOK | wxICON_INFORMATION);
// }

void MyFEBaseFrame::OnFERefreshButtonClick(wxCommandEvent& event)
{
    // // Implement necessary button press logic here
    // //this refresh button click will have similar logic to the creation of the original feFrame,
    // //interacting with the system manager to fetch all the new data that might not be displayed on screen.
    // //For example, after adding a new robot, the user will need to refresh this window

    // // wxMessageBox("Refresh", "Info", wxOK | wxICON_INFORMATION);

    // // std::vector<RobotData>& robots = GetRobots();

    // // Access the shared RobotData vector from DataManager and display each robot
    // //this is just used to display simple information (id, size, function) to user
    // std::vector<RobotData>& robots = dataManager->GetRobots();

    // std::vector<TaskData>& tasks = dataManager->GetTasks();

    // // Clear the existing display in the robotListBox (so same robot doesn't get added multiple times)
    // robotListBox->Clear();

    // // Clear the existing display in the taskListBox (so same task doesn't get added multiple times)
    // taskListBox->Clear();

    // // Iterate through the vector and display each robot's information
    // for (RobotData& robot : robots) {

    //     //creates string to hold status as color
    //     std::string statusBubble;
    //     //gets task status of each robot, sets status bubble accordingly
    //     //note: this may not be the best implementation moving forward, as this needs live updates from simulation, but it is proof of concept
    //     //could transfer to wxListCtrl if you want to use colored text
    //     robots::Robots localRobot = dataManager->GetAllRobotInfo(std::stoi(robot.robotID));
    //     std::string robotStatus = localRobot.get_task_status();
    //     if (robotStatus == "Available")
    //     {
    //         statusBubble = "🟢";
    //     }
    //     else if (robotStatus == "Ongoing")
    //     {
    //         statusBubble = "🟡";
    //     }
    //     else if (robotStatus == "Error")
    //     {
    //         statusBubble = "🔴";
    //     }


    //     wxString robotInfo = wxString::Format(statusBubble + " ID: " + robot.robotID + " (Size: " + robot.robotSize + ", Function: " + robot.robotFunction + ")"); //will be ugly for now a placeholder for ID or whatever else later
    //     robotListBox->Append(robotInfo);  // Adding each robot info to the ListBox
    // }

    // for (TaskData& task : tasks) {
    //     wxString taskInfo = wxString::Format("Room: " + task.taskRoom + ", Robot: " + task.taskRobot.robotID); //will be ugly for now a placeholder for ID or whatever else later
    //     taskListBox->Append(taskInfo);  // Adding each robot info to the ListBox
    // }

    // // // Pass the robots data to the controller
    // // if (dataManager) {
    // //     dataManager->SendRobotsData(robots);
    // // }
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

// void MyFEBaseFrame::SetText(const wxString& text)
// {
//     feTextControl->SetValue(text);  // Update text in feTextCtrl
// }

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
    // //retrieves the updated vector of RobotData
    // std::vector<RobotData>& robots = dataManager->GetRobots();

    // int selectionIndex = robotListBox->GetSelection(); //gets the selection index of whichever robot you clicked on in the wxListBox

    // //if selection index is found and smaller than vector of RobotData (should always be the case)
    // if (selectionIndex != wxNOT_FOUND && selectionIndex < robots.size()) {

    //     RobotData selectedRobot = robots[selectionIndex]; //finds the coordinated robot from the robots vector

    //     //converts robot ID to integer to use as key for database
    //     int robotId = std::stoi(selectedRobot.robotID);

    //     //complete robot information, accessed using the robot's ID
    //     const robots::Robots& completeRobot = dataManager->GetAllRobotInfo(robotId);

    //     // Create robotInfoFrame, passes through string to function as title to display robotID (not currently implemented visually)
    //     //also passed through the completed robot information (full robot class info) and instance of dataManager
    //     MyRobotInfoFrame* infoFrame = new MyRobotInfoFrame(this, "Robot ID: " + selectedRobot.robotID, completeRobot, dataManager);
    //     // Set the appropriate data and show the frame
    //     infoFrame->SetRobotData(completeRobot);
    //     infoFrame->Show();
    // }
    baseFrame->HandleRobotListBoxDClick(this, robotListBox, "FE");
}

void MyFEBaseFrame::OnTaskListBoxDClick(wxCommandEvent& event)
{
    // //implement logic to open task info window by double clicking task here
    // //retrieves the updated vector of RobotData
    // std::vector<TaskData>& tasks = dataManager->GetTasks();

    // int selectionIndex = taskListBox->GetSelection(); //gets the selection index of whichever robot you clicked on in the wxListBox

    // //if selection index is found and smaller than vector of RobotData (should always be the case)
    // if (selectionIndex != wxNOT_FOUND && selectionIndex < tasks.size()) {

    //     TaskData selectedTask = tasks[selectionIndex]; //finds the coordinated task from the tasks vector

    //     wxString taskStatus = "need to get task status here";

    //     // Create viewTaskFrame
    //     MyViewTaskFrame* taskInfoFrame = new MyViewTaskFrame(this);
    
    //     //converts robot ID to integer to use as key for database
    //     int robotId = std::stoi(selectedTask.taskRobot.robotID);

    //     //complete robot information, accessed using the robot's ID
    //     const robots::Robots& completeRobot = dataManager->GetAllRobotInfo(robotId);

    //     taskInfoFrame->SetTaskData(completeRobot);

    //     taskInfoFrame->Show();
    // }

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
    // //create robot with user-specified size and function. ID string created as 0, actually assigned in DataManager::AddRobot()
    // TaskData task = {roomSelection, robotSelection};

    // //adds created task to vector of TaskData in data manager
    // dataManager->AddTask(task);

    // wxMessageBox("Task created in room: " + roomSelection + ", using robot with ID: " + robotSelection.robotID, "Success!", wxOK | wxICON_INFORMATION);

    // //task is actually appended to the list on refresh button click, which is being called in the addTaskFrame

    baseFrame->AddTaskToList(roomSelection, robotSelection);
}

// // Getter for the vector of robots
// std::vector<RobotData>& MyFEBaseFrame::GetRobots() 
// {
//     // for (const RobotData& robot : robots) {
//     //     wxLogMessage(robot.robotPropertyData);
//     // }
//     return robots;
// }

/** 
// Method to bind GUI events for user interaction.
void MyFEBaseFrame::bindEvents() {
    // Bind refresh button to DataManager refresh method
    feRefreshButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [this](wxCommandEvent& event) {
        dataManager->refreshDataInGUI();
    });
}

// Updates the GUI display with new robot data.
void MyFEBaseFrame::updateRobotDisplay(const wxString& robotData) {
    feTextControl->SetValue(robotData);  // Update the text control with new data
}

*/
