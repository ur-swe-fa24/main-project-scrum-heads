#pragma once
#include "MyProjectBase.h"  // Include the generated base class

class MyFEBaseFrame : public feBaseFrame
{
public:
    MyFEBaseFrame(wxWindow* parent);

    // Method to set the text to write into the field engineer window
    void SetText(const wxString& text);
    // Method to add a robot to the wxListBox that holds robot info
    void AddRobotToList(const wxString& robotDescription);

protected:
    // Override virtual method for various button clicks
    void OnFEButtonClick(wxCommandEvent& event) override;
    void OnFERefreshButtonClick(wxCommandEvent& event) override;
    void OnAddRobotButtonClick(wxCommandEvent& event) override;
};
