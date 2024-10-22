#pragma once
#include "MyProjectBase.h"  // Include the generated base class

class MyDerivedFrame : public MyFrame1
{
public:
    MyDerivedFrame(wxWindow* parent);

protected:
    // Override the virtual method
    void testButtonOnButtonClick(wxCommandEvent& event) override;
};
