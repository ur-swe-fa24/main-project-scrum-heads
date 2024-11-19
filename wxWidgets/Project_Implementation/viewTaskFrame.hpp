#pragma once
#include "MyProjectBase.h" // Generated base class
#include "feBaseFrame.hpp"

class MyViewTaskFrame : public viewTaskFrame
{
public:
    MyViewTaskFrame(wxWindow* parent, MyFEBaseFrame* feFrame);

protected:

    MyFEBaseFrame* my_feFrame;

private:

};