#include "smBaseFrame.hpp"
#include <wx/wx.h>

MySMBaseFrame::MySMBaseFrame(wxWindow* parent, DataManager* dataManager, MyBaseFrame* baseFrame)
    : smBaseFrame(parent), dataManager(dataManager), baseFrame(baseFrame)  // Call the base class constructor
{
    // Connect the button event to the overridden method
    smRefreshButton->Bind(wxEVT_BUTTON, &MySMBaseFrame::OnSMRefreshButtonClick, this);

    //this is just to refresh the info when opening a new window
    //right now its cutting off the text, not sure why, doesn't happen when automatically refreshing when adding/removing robots/tasks
    wxCommandEvent dummyEvent; // Create a dummy event
    OnSMRefreshButtonClick(dummyEvent); // Call the method with the dummy event
}

void MySMBaseFrame::OnSMRefreshButtonClick(wxCommandEvent& event)
{
    //get all the updated business metrics from the dataManager
}