#include "robotInfoFrame.hpp"
#include "feBaseFrame.hpp"
#include <wx/wx.h>

MyRobotInfoFrame::MyRobotInfoFrame(wxWindow* parent, const wxString& title, robots::Robots robot, DataManager* dataManager, std::string userRole) //set title to "Robot: " + robotId
    :robotInfoFrame(parent), localRobot(robot), dataManager(dataManager), userRole(userRole) //localRobot and dataManager can now be used to call respective functions
{
    //sets title text to robot ID
    titleText->SetLabel(title);

    if (userRole != "FE")
    {
        //remove the remove and fix robot buttons for non-FE so they don't see it
        removeRobotButton->Show(false);
        fixRobotButton->Show(false);

        //remove error info for non-FE
        errorLogLabelText->Show(false);
        robotErrorLogTextBox->Show(false);
    }

    //if robot has error, enable robot fix button
    if (localRobot.get_error_status() != "")
    {
        fixRobotButton->Enable();
    }

    //only allow robot to be removed if it is healthy and not working on a task
    if (localRobot.get_task_status() != "Available")
    {
        removeRobotButton->Disable();
    }
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
    robotPropertiesText->SetLabel("Size: " + robot.get_size() + ", Function: " + robot.get_function_type()); //ugly for now just a placeholder

    //errorStatus is being logged as "" if there is no error, so change to a more informative message for user
    std::string errorStatus = robot.get_error_status();
    if (errorStatus == "")
    {
        errorStatus = "None";
    }

    //set total water and battery levels for robots, so presented levels are more descriptive as fraction
    std::string totalAmount;
    std::string robotSize = robot.get_size();
    if (robotSize == "Large")
    {
        totalAmount = "/140";
    }
    else if (robotSize == "Medium")
    {
        totalAmount = "/120";
    }
    else
    {
        totalAmount = "/100";
    }

    std::string robotInfo = robot.get_task_status() + ", Battery Level: " + std::to_string(robot.get_battery_level()) + totalAmount + ", Water Level: " + std::to_string(robot.get_water_level()) + totalAmount;
    std::vector<std::string> errorInfo = dataManager->getErrorLog(robot.get_id());

    if (userRole == "FE")
    {
        robotStatusText->SetLabel(robotInfo + ", Error Status: " + errorStatus);
        // robotErrorLogText->SetLabel(errorInfo);
        for (std::string errorString : errorInfo)
        {
            robotErrorLogTextBox->Append(errorString);
        }
    }
    else
    {
        robotStatusText->SetLabel(robotInfo + ", Error Status: " + errorStatus);
    }
    Layout();
}

void MyRobotInfoFrame::OnFixRobotButtonClick(wxCommandEvent& event)
{
    dataManager->FixRobot(localRobot.get_id());
    Close();
    wxMessageBox("The robot was fixed." , "Success!", wxOK | wxICON_INFORMATION);

    //GetParent() retrieves the parent frame, which is the FEBaseFrame that was passed in as parameter
    //necessary to call refresh button click method to automatically refresh page so robot is visually deleted
    //dynamic cast to ensure correct type
    MyFEBaseFrame* parentFrame = dynamic_cast<MyFEBaseFrame*>(GetParent());
    parentFrame->OnFERefreshButtonClick(event); // Trigger refresh event using the same event as remove robot button click (to mimic user pressing refresh button)
}
