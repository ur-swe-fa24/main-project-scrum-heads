#pragma once
#include "MyProjectBase.h"  // Include the generated base class

//placeholder for database/system manager later
struct RobotData {
    wxString robotPropertyData;
};

class MyFEBaseFrame : public feBaseFrame
{
public:
    MyFEBaseFrame(wxWindow* parent);

    // Method to set the text to write into the field engineer window
    void SetText(const wxString& text);
    // Method to add a robot to the wxListBox that holds robot info
    void AddRobotToList(const wxString& robotDescription);
    // Event for selecting a robot from wxListBox
    void OnRobotSelected(wxCommandEvent& event);

protected:
    // Override virtual method for various button clicks
    void OnFEButtonClick(wxCommandEvent& event) override;
    void OnFERefreshButtonClick(wxCommandEvent& event) override;
    void OnAddRobotButtonClick(wxCommandEvent& event) override;

    // Override virtual method for double clicking robot in wxListBox
    void OnRobotListBoxDClick(wxCommandEvent& event) override;

private:
    std::vector<RobotData> robots;
};
