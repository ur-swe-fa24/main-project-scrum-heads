#include "baseFrame.hpp"
#include <wx/wx.h>

// DataManager dataManager; //create single shared instance of dataManager

MyBaseFrame::MyBaseFrame(wxWindow* parent, DataManager* dataManager)
    : baseFrame(parent), dataManager(dataManager)  // Call the base class constructor
{
    // Connect the button event to the overridden method
    feSelectButton->Bind(wxEVT_BUTTON, &MyBaseFrame::OnFESelectButtonClick, this);
    smSelectButton->Bind(wxEVT_BUTTON, &MyBaseFrame::OnSMSelectButtonClick, this);
    bsSelectButton->Bind(wxEVT_BUTTON, &MyBaseFrame::OnBSSelectButtonClick, this);
    bmSelectButton->Bind(wxEVT_BUTTON, &MyBaseFrame::OnBMSelectButtonClick, this);
}

void MyBaseFrame::OnFESelectButtonClick(wxCommandEvent& event)
{
    // Implement necessary button press logic here
    // wxMessageBox("Field Engineer Frame", "Info", wxOK | wxICON_INFORMATION);
    // DataManager dataManager; //create single shared instance of dataManager
    MyFEBaseFrame* feFrame = new MyFEBaseFrame(nullptr, dataManager, this);

    //here is where I would interact with the system manager to fetch all the necessary data I need,
    //since it's here that the feFrame is created

    // wxString sampleText = "Hello, Field Engineer!";
    // feFrame->SetText(sampleText);  // Set the text in feFrame’s text control
    
    feFrame->Show(true);
}

void MyBaseFrame::OnSMSelectButtonClick(wxCommandEvent& event)
{
    // Implement necessary button press logic here
    // wxMessageBox("Senior Management Frame", "Info", wxOK | wxICON_INFORMATION);
    MySMBaseFrame* smFrame = new MySMBaseFrame(nullptr);
    smFrame->Show(true);
}

void MyBaseFrame::OnBSSelectButtonClick(wxCommandEvent& event)
{
    // Implement necessary button press logic here
    // wxMessageBox("Building Staff Frame", "Info", wxOK | wxICON_INFORMATION);
    MyBSBaseFrame* bsFrame = new MyBSBaseFrame(nullptr);
    bsFrame->Show(true);
}

void MyBaseFrame::OnBMSelectButtonClick(wxCommandEvent& event)
{
    // Implement necessary button press logic here
    // wxMessageBox("Building Manager Frame", "Info", wxOK | wxICON_INFORMATION);
    MyBMBaseFrame* bmFrame = new MyBMBaseFrame(nullptr);
    bmFrame->Show(true);
}

void MyBaseFrame::HandleRobotListBoxDClick(wxWindow* parent, wxListBox* robotListBox)
{
    //retrieves the updated vector of RobotData
    std::vector<RobotData>& robots = dataManager->GetRobots();

    int selectionIndex = robotListBox->GetSelection(); //gets the selection index of whichever robot you clicked on in the wxListBox

    //if selection index is found and smaller than vector of RobotData (should always be the case)
    if (selectionIndex != wxNOT_FOUND && selectionIndex < robots.size()) {

        RobotData selectedRobot = robots[selectionIndex]; //finds the coordinated robot from the robots vector

        //converts robot ID to integer to use as key for database
        int robotId = std::stoi(selectedRobot.robotID);

        //complete robot information, accessed using the robot's ID
        const robots::Robots& completeRobot = dataManager->GetAllRobotInfo(robotId);

        // Create robotInfoFrame, passes through string to function as title to display robotID (not currently implemented visually)
        //also passed through the completed robot information (full robot class info) and instance of dataManager
        MyRobotInfoFrame* infoFrame = new MyRobotInfoFrame(parent, "Robot ID: " + selectedRobot.robotID, completeRobot, dataManager);
        // Set the appropriate data and show the frame
        infoFrame->SetRobotData(completeRobot);
        infoFrame->Show();
    }
}

void MyBaseFrame::HandleTaskListBoxDClick(wxWindow* parent, wxListBox* taskListBox)
{
    //implement logic to open task info window by double clicking task here
    //retrieves the updated vector of RobotData
    std::vector<TaskData>& tasks = dataManager->GetTasks();

    int selectionIndex = taskListBox->GetSelection(); //gets the selection index of whichever robot you clicked on in the wxListBox

    //if selection index is found and smaller than vector of RobotData (should always be the case)
    if (selectionIndex != wxNOT_FOUND && selectionIndex < tasks.size()) {

        TaskData selectedTask = tasks[selectionIndex]; //finds the coordinated task from the tasks vector

        wxString taskStatus = "need to get task status here";

        // Create viewTaskFrame
        MyViewTaskFrame* taskInfoFrame = new MyViewTaskFrame(parent);
    
        //converts robot ID to integer to use as key for database
        int robotId = std::stoi(selectedTask.taskRobot.robotID);

        //complete robot information, accessed using the robot's ID
        const robots::Robots& completeRobot = dataManager->GetAllRobotInfo(robotId);

        taskInfoFrame->SetTaskData(completeRobot);

        taskInfoFrame->Show();
    }
}

