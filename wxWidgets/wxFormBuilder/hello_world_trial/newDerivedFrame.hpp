#pragma once
#include "MyProjectBase.h"  // Include the generated base class

class MyNewDerivedFrame : public MyFrame2
{
public:
    MyNewDerivedFrame(wxWindow* parent);

protected:
    // Override the virtual method
    void testButtonOnButtonClick(wxCommandEvent& event) override;
};
