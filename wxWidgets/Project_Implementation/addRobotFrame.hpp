#pragma once
#include "MyProjectBase.h" // Generated base class
#include "feBaseFrame.hpp"

class MyAddRobotFrame : public AddRobotFrame
{
public:
    MyAddRobotFrame(wxWindow* parent, MyFEBaseFrame* feFrame);

protected:
    // Event corresponding to user selecting something from size dropdown menu
    void OnRobotSizeChoice(wxCommandEvent& event) override;
    // Event corresponding to user selecting something from function dropdown menu
    void OnRobotFunctionChoice(wxCommandEvent& event) override;

    // Overriding virtual create robot button click method
    void OnCreateRobotButtonClick(wxCommandEvent& event) override;

    MyFEBaseFrame* my_feFrame;

private:
    // Variables to track whether the appropriate robot data has been initialized in dropdown menus
    bool isSizeSelected = false;
    bool isFunctionSelected = false;

    // Method that checks the above boolean values are both set to true
    void CheckSelections();
};
