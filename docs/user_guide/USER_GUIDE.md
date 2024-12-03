# User Guide

## Startup: Building and Running the Application

In order to build the application, go to your terminal and navigate to the directory where the project is located. Once here, make a build folder by entering `mkdir build` into your terminal. Then, navigate to that directory using `cd build`. Now, type and enter `cmake ..`, which runs the main project CMake file. The output of this CMake, including the relevant makefile, will be placed into the build folder you created. Therefore, once CMake is complete, you can run `make` to build the project.

Once the project is built, you want to run the GUI executable in order to give the user a physical window to interface with. To achieve this, run `./wxWidgets/ProjectGUI`. After running this command in your terminal, a role-selection window should appear, which is the opening window of the application.

## How to Use the Application

Once you are viewing the role selection screen, you can make the choice between four user roles. Selecting any of these roles will open up another window with role-specific options and information. 

### Field Engineer Selection

Currently, only the field engineer has significant functionality. They may add robots to the system using the `Add Robot` button. When clicking this button, a new window will be presented with dropdowns that allow users to specify the size and function they want to create a robot with. The system mandates that both of these dropdowns are interacted with before allowing the user to actually create a robot, even if the user's selection is keeping the default size and function on their screen. Once a robot is successfully created, the user will view a success message, along with information about the ID number assigned to the created robot. The add robot window will be automatically closed upon robot creation. Now, the field engineer can see the robot's basic information (its ID, size, and function) from their main view. Every time a robot is added, it is appended to a list of robots at the bottom of their screen.

Added robots can then be selected with a double-click, which opens up a new window consisting of more detailed robot information. Here, the field engineer has access to the robot's status and error log, in addition to its basic properties. Lastly, they also have functionality to remove robots from the system using the `Remove` button. Upon removal, the user once again gets a confirmation message, and the robot will be automatically deleted from their robot list.

If a field engineer closes out their current main view and reopens another field engineer window from the role-selection window, they can use the `Refresh` button to retrieve the list of robots they were previously working with.

### Building Manager Selection

TBD

### Building Staff Selection

TBD

### Senior Management Selection

TBD