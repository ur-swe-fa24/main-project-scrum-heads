#pragma once
#include "MyProjectBase.h" // Generated base class
#include "feBaseFrame.hpp"

class MyViewTaskFrame : public viewTaskFrame
{
public:
    MyViewTaskFrame(wxWindow* parent, MyFEBaseFrame* feFrame);

    //sets task data, provided robot from previous user frame
    void SetTaskData(robots::Robots robot);

protected:

    MyFEBaseFrame* my_feFrame;

private:

};