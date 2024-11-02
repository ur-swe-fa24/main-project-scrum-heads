#pragma once
#include "MyProjectBase.h"  // Include the generated base class

class MyFEBaseFrame : public feBaseFrame
{
public:
    MyFEBaseFrame(wxWindow* parent);

    // Method to set the text content
    void SetText(const wxString& text);

protected:
    // Override the virtual method
    void OnFEButtonClick(wxCommandEvent& event) override;
    void OnFERefreshButtonClick(wxCommandEvent& event) override;
};
