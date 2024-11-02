#pragma once
#include "MyProjectBase.h"  // Include the generated base class

class MyBMBaseFrame : public bmBaseFrame
{
public:
    MyBMBaseFrame(wxWindow* parent);

protected:
    // Override the virtual method
    void OnBMButtonClick(wxCommandEvent& event) override;
};
