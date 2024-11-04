#include "robotInfoFrame.hpp"

MyRobotInfoFrame::MyRobotInfoFrame(wxWindow* parent, const wxString& title) //set title to "Robot: " + robotId
    :robotInfoFrame(parent) //call base class constructor
{

}

//note: can easily add more parameters for status, errors, whatever
void MyRobotInfoFrame::SetRobotData(const wxString& robotProperties) {
    robotPropertiesText->SetLabel(robotProperties);
    robotStatusText->SetLabel("Status");
    robotErrorLogText->SetLabel("Errors");
    Layout();
}
