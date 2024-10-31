#pragma once
#include "MyProjectBase.h"  // Include the generated base class

class MyFEBaseFrame : public feBaseFrame
{
public:
    MyFEBaseFrame(wxWindow* parent);

protected:
    // Override the virtual method
    void OnFEButtonClick(wxCommandEvent& event) override;
};
