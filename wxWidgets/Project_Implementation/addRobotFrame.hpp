#pragma once
#include "MyProjectBase.h" // Generated base class

class MyAddRobotFrame : public AddRobotFrame
{
public:
    MyAddRobotFrame(wxWindow* parent);

protected:
    void OnRobotSizeChoice(wxCommandEvent& event) override;
    void OnRobotFunctionChoice(wxCommandEvent& event) override;
    void OnCreateRobotButtonClick(wxCommandEvent& event) override;

private:
    bool isSizeSelected = false;
    bool isFunctionSelected = false;

    void CheckSelections();
};
