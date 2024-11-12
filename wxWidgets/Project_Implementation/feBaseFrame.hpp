#pragma once
#include "MyProjectBase.h"  // Include the generated base class
#include "../include/DataManager.h"

class DataManager;

class MyFEBaseFrame : public feBaseFrame
{
public:
    MyFEBaseFrame(wxWindow* parent, DataManager* dataManager);

    // Method to set the text to write into the field engineer window
    void SetText(const wxString& text);
    // Method to add a robot to the wxListBox that holds robot info
    void AddRobotToList(const wxString& robotSize, const wxString& robotFunction);
    // Event for selecting a robot from wxListBox
    void OnRobotSelected(wxCommandEvent& event);

    // Getter for the vector of robots
    std::vector<RobotData>& GetRobots();

protected:
    // Override virtual method for various button clicks
    void OnFEButtonClick(wxCommandEvent& event) override;
    void OnFERefreshButtonClick(wxCommandEvent& event) override;
    void OnAddRobotButtonClick(wxCommandEvent& event) override;

    // Override virtual method for double clicking robot in wxListBox
    void OnRobotListBoxDClick(wxCommandEvent& event) override;

private:
    // std::vector<RobotData> robots;

    DataManager* dataManager;  // Pointer to the data manager
};
