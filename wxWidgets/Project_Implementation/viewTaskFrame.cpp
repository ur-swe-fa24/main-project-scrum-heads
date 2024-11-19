#include "viewTaskFrame.hpp"
#include <wx/wx.h>

// Takes feBaseFrame as both a parent and a pointer to the frame so it can pass it data from the created robots
MyViewTaskFrame::MyViewTaskFrame(wxWindow* parent, MyFEBaseFrame* feFrame)
    : viewTaskFrame(parent), my_feFrame(feFrame) // Initializes values
{

}