# Introduction
This folder contains a test trial of wxWidgets that implements the ["Hello World" Introduction](https://docs.wxwidgets.org/latest/overview_helloworld.html) from wxWidgets' website. All code was copied directly from the provided source, but there is additional documentation in the form of thorough commenting taken from information within the tutorial. 

# CMake
CMake was used to link the wxWidgets library to `hello_world.cpp`. This CMake file was constructed using the references below, in addition to class instruction.

# Required Setup
+ [Install wxWidgets](https://www.wxwidgets.org/downloads/), taking note of where you put the directory.
+ Go into WxAppTest/CMakeLists.txt, and change the location of wxWidgets to the location on your local machine, as noted in the previous step.

# How to Use
+ `Command + shift + p` to open the command line
+ `CMake: Configure`
+ `CMake: Build`
+ `CMake: Debug` or `CMake: Run`
+ Once the application is running, it should display a window that says "Welcome to wxWidgets!"
+ With the application open, you can use the toolbar on the top of your screen to interact with it. File -> Hello... displays a message, and so does WxAppTest -> About.

# References
+ [wxWidgets C++ GUI | how-to | getting started | tutorial | guide](https://www.youtube.com/watch?v=L3IXsa9Yyr4)
+ [wxWidgets: Visual Studio Code setup for C++ and cmake](https://www.youtube.com/watch?v=zdHqoyG73Jk)
+ [Single Codebase UI Apps in C++ for Linux, Windows and MacOS - building with wxWidgets and CMake](https://www.youtube.com/watch?v=MfuBS9n5_aY&t=4s)
+ [Easy C++ Dependency Management with CMake's FetchContent: Quick Tutorial](https://www.youtube.com/watch?v=zjNg5HdgNO0)