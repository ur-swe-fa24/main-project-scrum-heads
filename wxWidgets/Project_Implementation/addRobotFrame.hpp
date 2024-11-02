#pragma once
#include "MyProjectBase.h" // Generated base class
#include "feBaseFrame.hpp"

class MyAddRobotFrame : public AddRobotFrame
{
public:
    MyAddRobotFrame(wxWindow* parent, MyFEBaseFrame* feFrame);

protected:
    void OnRobotSizeChoice(wxCommandEvent& event) override;
    void OnRobotFunctionChoice(wxCommandEvent& event) override;
    void OnCreateRobotButtonClick(wxCommandEvent& event) override;

    MyFEBaseFrame* my_feFrame;

private:
    bool isSizeSelected = false;
    bool isFunctionSelected = false;

    void CheckSelections();
};
