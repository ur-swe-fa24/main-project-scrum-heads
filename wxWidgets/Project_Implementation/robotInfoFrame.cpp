#include "robotInfoFrame.hpp"
#include "feBaseFrame.hpp"
#include <wx/wx.h>

MyRobotInfoFrame::MyRobotInfoFrame(wxWindow* parent, const wxString& title, robots::Robots robot, DataManager* dataManager) //set title to "Robot: " + robotId
    :robotInfoFrame(parent), localRobot(robot), dataManager(dataManager) //call base class constructor
{
    //need to add necessary text display in wxFormBuilder, can then assign this title parameter to it
}

//method for removing a robot from the database by a button click
void MyRobotInfoFrame::OnRemoveRobotButtonClick(wxCommandEvent& event)
{
    // Implement necessary button press logic here
    int robotId = localRobot.get_id();
    dataManager->DeleteRobot(robotId);
    
    //GetParent() retrieves the parent frame, which is the FEBaseFrame that was passed in as parameter
    //necessary to call refresh button click method to automatically refresh page so robot is visually deleted
    //dynamic cast to ensure correct type
    MyFEBaseFrame* parentFrame = dynamic_cast<MyFEBaseFrame*>(GetParent());
    parentFrame->OnFERefreshButtonClick(event); // Trigger refresh event using the same event as remove robot button click (to mimic user pressing refresh button)

    //close frame automatically
    Close();

    //convert robot id to string and print success message for user
    std::string idString = std::to_string(robotId);
    wxMessageBox("Robot removed with ID: " + idString, "Success!", wxOK | wxICON_INFORMATION);
}

//note: could change this to just use localRobot instead of taking the robot as a parameter again, but leaving for now
//in case other classes would benefit from example
void MyRobotInfoFrame::SetRobotData(robots::Robots robot) {
    // robotPropertiesText->SetLabel("ID: " + robot.robotID + " (Size: " + robot.robotSize + ", Function: " + robot.robotFunction + ")"); //ugly for now just a placeholder
    robotPropertiesText->SetLabel("(Size: " + robot.get_size() + ", Function: " + robot.get_function_type() + ")"); //ugly for now just a placeholder
    robotStatusText->SetLabel("Status");
    robotErrorLogText->SetLabel("Errors");
    Layout();
}
