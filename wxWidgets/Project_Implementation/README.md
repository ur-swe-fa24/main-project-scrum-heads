# GUI Implementation
This project's GUI is developed entirely using wxWidgets and wxFormBuilder. For introductions to these tools, along with a "Hello World"-level implementation, view their respective documentation [here](../WxAppTest/README.md) and [here](../wxFormBuilder/hello_world_trial/README.md). Each frame that is created has its own respective class, which are documented below.

## Project Base
`MyProjectBase.hpp` and `MyProjectBase.cpp` were generated using wxFormBuilder. These files establish the base classes for the various classes that will be used for other frames. They declare the necessary buttons, text boxes, and other various GUI elements that are created using the wxFormBuilder tool, along with their properties, such as where they are positioned on the screen, how large they are, and what color they are. The actual project that is being developed in wxFormBuilder is `SWE_Project_GUI.fbp`, which can also be found in this directory. These files will continuously change throughout the project as more things are added to the GUI.

## Main
`main.cpp` currently has very little functionality. Its only role is to show the initial base user selection frame when the program starts.

## User Selection Frame
The user selection frame is specified in `baseFrame.hpp` and `baseFrame.cpp`. This is the first window that the user will see when starting up the application. Currently, its only purpose is to allow the user to select one of four user roles (with a click of a button). Later, any additional verification logic would be added at this point.

## Specific User View Frames
Once the user selects their user role, they are displayed with one of four frames corresponding to their selected role. Currently, three of the user roles (building staff, building manager, and senior management) have minimal functionality, with just a button to indicate they are in the correct user view. The field engineer has further functionality, as specified in `feBaseFrame.hpp` and `feBaseFrame.cpp`. The other specific user view frames follow the same naming convention, substituting the "fe" (for "field engineer") with the replacement for the other user roles ("bs", "bm", and "sm", respectively.) The field engineer has an additional text box containing "Hello, Field Engineer!" as proof of concept for writing data into a frame on its creation. The field engineer can add robots using an "Add Robot" button, which, if done succesfully (specified below), will then append those robots to the text box below it. This functionality is currently commeneted out for proof of a working refresh button, which is currently mocking the retrieval of data from the system manager, and functionally appends the added robots to the text box. Once robots are added to this text box, the field engineer can click on them to view their data. 

## Add Robot Frame
This frame, specified in `addRobotFrame.hpp` and `addRobotFrame.cpp`, is what a field engineer sees when clicking the "Add Robot" button. It consists of two dropdown menus, one for robot size, and one for robot function. Once the user interacts with these dropdown menus to make a selection, the "Create Robot" button, which is originally grayed out and non-clickable, becomes accessible to the user. After creating a robot, the window closes automatically. 

## Robot Info Frame
This frame, specified in `robotInfoFrame.hpp` and `robotInfoFrame.cpp`, is accessible after adding at least one robot to the text box in the field engineer base frame. Once a robot is added here, a user can double-click on it to get a pop-up window of robot-specific information.

# Intended Usage
After using CMake to generate a makefile and running make, while in the build folder use `./wxWidgets/ProjectGUI` to run the application.