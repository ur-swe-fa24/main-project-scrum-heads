#include "feBaseFrame.hpp"
#include "addRobotFrame.hpp"
#include "robotInfoFrame.hpp"
#include <wx/wx.h>

// #include "DataManager.hpp"  // need for data manager

MyFEBaseFrame::MyFEBaseFrame(wxWindow* parent, DataManager* dataManager)
    : feBaseFrame(parent), dataManager(dataManager)  // Call the base class constructor
{
    // Connect the button event to the overridden method
    feButton->Bind(wxEVT_BUTTON, &MyFEBaseFrame::OnFEButtonClick, this);
    
    // Connect the button event to the overridden method
    feRefreshButton->Bind(wxEVT_BUTTON, &MyFEBaseFrame::OnFERefreshButtonClick, this);

    // Pass this frame instance to DataManager
    // DataManager* dataManager = new DataManager(this); 
    // bindEvents();
}

void MyFEBaseFrame::OnFEButtonClick(wxCommandEvent& event)
{
    // Implement necessary button press logic here
    wxMessageBox("Field Engineer Frame", "Info", wxOK | wxICON_INFORMATION);
}

void MyFEBaseFrame::OnFERefreshButtonClick(wxCommandEvent& event)
{
    // Implement necessary button press logic here
    //this refresh button click will have similar logic to the creation of the original feFrame,
    //interacting with the system manager to fetch all the new data that might not be displayed on screen.
    //For example, after adding a new robot, the user will need to refresh this window

    // wxMessageBox("Refresh", "Info", wxOK | wxICON_INFORMATION);

    // std::vector<RobotData>& robots = GetRobots();

    // Access the shared RobotData vector from DataManager and display each robot
    //this is just used to display simple information (id, size, function) to user
    std::vector<RobotData>& robots = dataManager->GetRobots();

    // Clear the existing display in the wxListBox
    robotListBox->Clear();

    // Iterate through the vector and display each robot's information
    for (RobotData& robot : robots) {
        wxString robotInfo = wxString::Format("ID: " + robot.robotID + " (Size: " + robot.robotSize + ", Function: " + robot.robotFunction + ")"); //will be ugly for now a placeholder for ID or whatever else later
        robotListBox->Append(robotInfo);  // Adding each robot info to the ListBox
    }

    // // Pass the robots data to the controller
    // if (dataManager) {
    //     dataManager->SendRobotsData(robots);
    // }
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

void MyFEBaseFrame::SetText(const wxString& text)
{
    feTextControl->SetValue(text);  // Update text in feTextCtrl
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

    //robot is actually appended to the list on refresh button click
}

void MyFEBaseFrame::OnRobotListBoxDClick(wxCommandEvent& event)
{
    std::vector<RobotData>& robots = dataManager->GetRobots();

    int selectionIndex = robotListBox->GetSelection(); //gets the selection index of whichever robot you clicked on in the wxListBox

    if (selectionIndex != wxNOT_FOUND && selectionIndex < robots.size()) {

        RobotData selectedRobot = robots[selectionIndex]; //finds the coordinated robot from the robots vector

        //converts robot ID to integer to use as key for database
        int robotId = std::stoi(selectedRobot.robotID);

        const robots::Robots& completeRobot = dataManager->GetAllRobotInfo(robotId);

        // Create robotInfoFrame, passes through string to function as title
        MyRobotInfoFrame* infoFrame = new MyRobotInfoFrame(this, "Robot ID: " + selectedRobot.robotID, completeRobot, dataManager);
        // Set the appropriate data and show the frame
        infoFrame->SetRobotData(completeRobot);
        infoFrame->Show();
    }
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
