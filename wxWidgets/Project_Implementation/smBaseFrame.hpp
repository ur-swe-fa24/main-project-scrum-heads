#pragma once
#include "MyProjectBase.h"  // Include the generated base class

class MySMBaseFrame : public smBaseFrame
{
public:
    MySMBaseFrame(wxWindow* parent);

protected:
    // Override the virtual method
    void OnSMButtonClick(wxCommandEvent& event) override;
};
