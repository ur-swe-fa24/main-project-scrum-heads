# Introduction
This folder provides the basic structure of developing a UI project with wxFormBuilder. `MyProjectBase.h` and `MyProjectBase.cpp` were both generated using wxFormBuilder and left unedited. `derivedFrame.hpp` and `derivedFrame.cpp` work together to inherit the frame defined in `MyProjectBase.h` and override the button press method to allow custom logic. `main.cpp` initializes the frame. This structure of having separate classes for derived frames, along with main, is important, as it allows the continuous regeneration of files using wxFormBuilder. No edits can be made to the files generated from wxFormBuilder because those edits would be overwritten whenever making adjustments to the user interface and generating new code. 

# How to Use
+ Use `cmake` to build the project while in the root directory.
+ `./WxFormBuilderTest` to run the executable.
+ Once the application is running, it should display an application with a single button. If you click this button, demo text will be displayed.

# References
+ [wxFormBuilder 1 - Create Frame](https://www.youtube.com/watch?v=YC5G96CkiFc)
+ [Using wxWidgets and wxFormBuilder to create GUI on macOS](https://www.youtube.com/watch?v=kbRCQj4j4yw)