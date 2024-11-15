#pragma once
#include "MyProjectBase.h"
#include "../include/DataManager.h"

//generic MyRobotInfoFrame class that is used to populate frame with robot-specific data when robot is selected
class MyRobotInfoFrame : public robotInfoFrame {
public:
    MyRobotInfoFrame(wxWindow* parent, const wxString& title);

    // Method to set and display robot details
    //CHANGE THIS to work by retrieving data from database using robot ID number!!
    void SetRobotData(const robots::Robots& robot);
};
