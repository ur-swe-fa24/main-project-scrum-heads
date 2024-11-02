#pragma once
#include "MyProjectBase.h"  // Include the generated base class

class MyBSBaseFrame : public bsBaseFrame
{
public:
    MyBSBaseFrame(wxWindow* parent);

protected:
    // Override the virtual method
    void OnBSButtonClick(wxCommandEvent& event) override;
};
