#pragma once
#include "MyProjectBase.h"
#include "../include/DataManager.h"

//generic MyRobotInfoFrame class that is used to populate frame with robot-specific data when robot is selected
class MyRobotInfoFrame : public robotInfoFrame {
public:
    MyRobotInfoFrame(wxWindow* parent, const wxString& title, robots::Robots robot, DataManager* dataManager);

    // Method to set and display robot details
    //CHANGE THIS to work by retrieving data from database using robot ID number!!
    void SetRobotData(robots::Robots robot);

protected:
    // Override the virtual button press methods
    void OnRemoveRobotButtonClick(wxCommandEvent& event) override;
    void OnFixRobotButtonClick(wxCommandEvent& event) override;
    
    robots::Robots localRobot;
    DataManager* dataManager;
};
