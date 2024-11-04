#pragma once
#include "MyProjectBase.h"

//generic MyRobotInfoFrame class that is used to populate frame with robot-specific data when robot is selected
class MyRobotInfoFrame : public robotInfoFrame {
public:
    MyRobotInfoFrame(wxWindow* parent, const wxString& title);

    // Method to set and display robot details
    void SetRobotData(const wxString& robotProperties);
};
