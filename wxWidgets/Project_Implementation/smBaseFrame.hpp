#pragma once
#include "MyProjectBase.h"  // Include the generated base class
#include "../include/DataManager.h"
#include "baseFrame.hpp"

class MySMBaseFrame : public smBaseFrame
{
public:
    MySMBaseFrame(wxWindow* parent, DataManager* dataManager, MyBaseFrame* baseFrame);

    void OnSMRefreshButtonClick(wxCommandEvent& event);

protected:

private:

    DataManager* dataManager;  // Pointer to the data manager

    MyBaseFrame* baseFrame;  // Pointer to the baseFrame

};
