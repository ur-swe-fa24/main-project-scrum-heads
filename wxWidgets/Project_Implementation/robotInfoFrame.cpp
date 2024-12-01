#include "robotInfoFrame.hpp"
#include "feBaseFrame.hpp"
#include <wx/wx.h>

MyRobotInfoFrame::MyRobotInfoFrame(wxWindow* parent, const wxString& title, robots::Robots robot, DataManager* dataManager) //set title to "Robot: " + robotId
    :robotInfoFrame(parent), localRobot(robot), dataManager(dataManager) //localRobot and dataManager can now be used to call respective functions
{
    //sets title text to robot ID
    titleText->SetLabel(title);
}

//method for removing a robot from the database by a button click
void MyRobotInfoFrame::OnRemoveRobotButtonClick(wxCommandEvent& event)
{
    //get ID as integer from localRobot
    int robotId = localRobot.get_id();
    //uses ID to delete robot from database using dataManager
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
    robotStatusText->SetLabel(robot.get_task_status());
    robotErrorLogText->SetLabel("Errors");
    Layout();
}

void MyRobotInfoFrame::OnFixRobotButtonClick(wxCommandEvent& event)
{
    //fix robot here
    //need to figure out how you're going to receive bugged robot signal in order to enable button
    //also need to figure out how to update this so the user can actually view bugged status (maybe change the color of the text of the robots in the display window?)
    //also need to figure out how to hide this button (along with the remove robot button) in other user views (to avoid making different frames for everyone)
}
