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

    // Access the shared vector from DataManager and display each robot
    std::vector<RobotData>& robots = dataManager->GetRobots();

    // Clear the existing display in the wxListBox
    robotListBox->Clear();

    // Iterate through the vector and display each robot's information
    for (RobotData& robot : robots) {
        wxString robotInfo = wxString::Format(robot.robotPropertyData);
        robotListBox->Append(robotInfo);  // Adding each robot info to the ListBox
    }

    // Pass the robots data to the controller
    if (dataManager) {
        dataManager->SendRobotsData(robots);
    }
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

void MyFEBaseFrame::AddRobotToList(const wxString& robotDescription)
{
    // //add robotDescription (currently just properties, so size and function) to robots vector
    RobotData robot = {robotDescription};
    // robots.push_back(robot);

    dataManager->AddRobot(robot);

    // Add the robot description to the list of robots 
    // note: currently commented out because using refresh button to show functionality of GetRobots()
    // robotListBox->Append(robotDescription);
}

void MyFEBaseFrame::OnRobotListBoxDClick(wxCommandEvent& event)
{
    std::vector<RobotData>& robots = dataManager->GetRobots();
    //note: the exact logic here will change such that when a user clicks on a robot it accesses it's ID and then retrives the necessary data
    int selectionIndex = robotListBox->GetSelection(); //gets the selection index of whichever robot you clicked on in the wxListBox
    // std::cout << selectionIndex << std::endl;
    // std::cout << robots.size() << std::endl;
    if (selectionIndex != wxNOT_FOUND && selectionIndex < robots.size()) {
        // std::cout << selectionIndex << std::endl;
        // std::cout << robots.size() << std::endl;
        RobotData selectedRobot = robots[selectionIndex]; //finds the coordinated robot from the robots vector

        // Create robotInfoFrame
        MyRobotInfoFrame* infoFrame = new MyRobotInfoFrame(this, "Robot ID: ");
        // Set the appropriate data and show the frame
        infoFrame->SetRobotData(selectedRobot.robotPropertyData);
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
