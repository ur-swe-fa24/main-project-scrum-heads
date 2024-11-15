#include "robotInfoFrame.hpp"

MyRobotInfoFrame::MyRobotInfoFrame(wxWindow* parent, const wxString& title) //set title to "Robot: " + robotId
    :robotInfoFrame(parent) //call base class constructor
{

}

//note: can easily add more parameters for status, errors, whatever
//CHANGE THIS to work by retrieving data from database using robot ID number!!
void MyRobotInfoFrame::SetRobotData(const RobotData& robot) {
    robotPropertiesText->SetLabel("ID: " + robot.robotID + " (Size: " + robot.robotSize + ", Function: " + robot.robotFunction + ")"); //ugly for now just a placeholder
    robotStatusText->SetLabel("Status");
    robotErrorLogText->SetLabel("Errors");
    Layout();
}
