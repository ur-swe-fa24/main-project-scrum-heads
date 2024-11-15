#include "robotInfoFrame.hpp"

MyRobotInfoFrame::MyRobotInfoFrame(wxWindow* parent, const wxString& title) //set title to "Robot: " + robotId
    :robotInfoFrame(parent) //call base class constructor
{
    //need to add necessary text display in wxFormBuilder, can then assign this title parameter to it
}

//note: can easily add more parameters for status, errors, whatever
//CHANGE THIS to work by retrieving data from database using robot ID number!!
void MyRobotInfoFrame::SetRobotData(robots::Robots robot) {
    // robotPropertiesText->SetLabel("ID: " + robot.robotID + " (Size: " + robot.robotSize + ", Function: " + robot.robotFunction + ")"); //ugly for now just a placeholder
    std::string robotSize = robot.get_size();
    std::cout << robotSize << std::endl;
    robotPropertiesText->SetLabel("(Size: " + robot.get_size() + ", Function: " + robot.get_function_type() + ")"); //ugly for now just a placeholder
    robotStatusText->SetLabel("Status");
    robotErrorLogText->SetLabel("Errors");
    Layout();
}
