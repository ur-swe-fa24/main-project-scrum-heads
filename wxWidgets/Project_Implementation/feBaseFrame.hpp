#pragma once
#include "MyProjectBase.h"  // Include the generated base class
#include "../include/DataManager.h"
#include "baseFrame.hpp"


//placeholder for database/system manager later
// struct RobotData {
//     wxString robotSize;
//     wxString robotFunction;
// };
class DataManager;

class MyBaseFrame;

class MyFEBaseFrame : public feBaseFrame
{
public:
    MyFEBaseFrame(wxWindow* parent, DataManager* dataManager, MyBaseFrame* baseFrame);

    // Method to set the text to write into the field engineer window
    // void SetText(const wxString& text);

    // Method to add a robot to the wxListBox that holds robot info
    void AddRobotToList(const wxString& robotSize, const wxString& robotFunction);

    // Method to add a task to the wxListBox that holds task info
    void AddTaskToList(const wxString& taskRoom, const RobotData& taskRobot);

    // Event for selecting a robot from wxListBox
    void OnRobotSelected(wxCommandEvent& event);

    // Getter for the vector of robots
    std::vector<RobotData>& GetRobots();
    
    void OnFERefreshButtonClick(wxCommandEvent& event) override;

protected:
    // Override virtual method for various button clicks
    // void OnFEButtonClick(wxCommandEvent& event) override;
    void OnAddRobotButtonClick(wxCommandEvent& event) override;

    // Override virtual method for double clicking robot in wxListBox
    void OnRobotListBoxDClick(wxCommandEvent& event) override;

    //Override virtual method for clicking add task button
    void OnAddTaskButtonClick(wxCommandEvent& event) override;

    // Override virtual method for double clicking task in wxListBox
    void OnTaskListBoxDClick(wxCommandEvent& event) override;

private:
    DataManager* dataManager;  // Pointer to the data manager

    MyBaseFrame* baseFrame;  // Pointer to the baseFrame
};
