# User Guide

## Startup: Building and Running the Application

In order to build the application, go to your terminal and navigate to the directory where the project is located. Once here, make a build folder by entering `mkdir build` into your terminal. Then, navigate to that directory using `cd build`. Now, type and enter `cmake ..`, which runs the main project CMake file. The output of this CMake, including the relevant makefile, will be placed into the build folder you created. Therefore, once CMake is complete, you can run `make` to build the project.

Once the project is built, you want to run the GUI executable in order to give the user a physical window to interface with. To achieve this, run `./wxWidgets/ProjectGUI`. After running this command in your terminal, a role-selection window should appear, which is the opening window of the application.

## How to Use the Application

Once you are viewing the role selection screen, you can make the choice between four user roles. Selecting any of these roles will open up another window with role-specific options and information. 

### Field Engineer Selection

The field engineer may add robots to the system using the `Add Robot` button. When clicking this button, a new window will be presented with dropdowns that allow users to specify the size and function they want to create a robot with. The system mandates that both of these dropdowns are interacted with before allowing the user to actually create a robot, even if the user's selection is keeping the default size and function on their screen. Once a robot is successfully created, the user will view a success message, along with information about the ID number assigned to the created robot. The add robot window will be automatically closed upon robot creation. Now, the field engineer can see the robot's basic information (its availability, ID, size, and function) from their main view. Every time a robot is added, it is appended to a list of robots on their screen.

Added robots can then be selected with a double-click, which opens up a new window consisting of more detailed robot information. Here, the field engineer has access to the robot's status and error log, in addition to its basic properties. Lastly, they also have functionality to remove robots from the system using the `Remove` button. Upon removal, the user once again gets a confirmation message, and the robot will be automatically deleted from their robot list. In this same window, the field enginer can also fix a bugged robot with the `Fix` button. This button is only accessible if the robot is bugged or has an error. Once a field engineer fixes the robot, this window automatically closes, and the robot's status is updated. Even after the robot is fixed, its error history will be maintained in the error log, which shows comprehensive information about the robot at the time of the error.

If a field engineer closes out their current main view and reopens another field engineer window from the role-selection window, they can use the `Refresh` button to retrieve the list of robots they were previously working with.

The field engineer can also assign tasks to robots using the `Add Task` button. This button opens a new window, where the user can see the rooms and robots that are currently available. Once the user selects a room, only the available robots that can complete a task in that room are displayed (i.e., they have the correct cleaning type, along with adequate water and battery). Therefore, the user can only assign a robot to a task if it can complete that task. The field engineer may either specify the robot for a cleaning task, or allow the software to choose for them. Regardless, they will only be able to create a task if there is a possible robot to complete the robot, because the `Create Task` button only becomes accessible when the task is completable.

Once a task is created, it becomes accessible in a box on the field engineer's main view frame, and the robot and room's status get updated accordingly. The task can be selected with a double-click, which pops up a new window showing the robot and room that are active in the task, along with the task completion percentage. Once tasks are complete, they no longer show up in this window.

### Building Manager Selection

The building manager can view robots in the same manner as the field engineer, but they cannot create new robots, as that task is the sole responsibility of the field engineer. However, their robot viewing doesn't include the comprehensive error log status that the field engineer has access to, so they cannot view error history. Further, they have no ability to remove or fix robots, as that is the responsibility of the field engineer. Building managers have identical add task functionality to field engineers. Further, their views of robots, tasks, and rooms on their main view frame is identical. Their unique trait is that they can change the availability of rooms by selecting a room and clicking the `Change Room Availability` button. They can only change rooms to and from available, and cannot change the availability of a room that is busy being cleaned.

### Building Staff Selection

The building staff has mostly the same functionality as a building manager, with a few key differences. Firstly, they must select both a room and a robot when creating a task. Secondly, they have no ability to change room availabilities. Similar to the building manager, they cannot remove or fix robots, nor do they have access to a comprehensive error log. Their capabilities are limited to assigning cleaning tasks to specific rooms and robots, and viewing basic information about tasks and robots.

### Senior Management Selection

Senior management functionality was not fully implemented during this project.