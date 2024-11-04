#pragma once
#include "MyProjectBase.h"  // Include the generated base class

class MyBaseFrame : public baseFrame
{
public:
    MyBaseFrame(wxWindow* parent);

protected:
    // Override the virtual method for various button clicks
    void OnFESelectButtonClick(wxCommandEvent& event) override;
    void OnBMSelectButtonClick(wxCommandEvent& event) override;
    void OnBSSelectButtonClick(wxCommandEvent& event) override;
    void OnSMSelectButtonClick(wxCommandEvent& event) override;
};
