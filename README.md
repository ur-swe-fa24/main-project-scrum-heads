# (Our Awesome Product) Overview

## Goal

The goal of the present product is to provide a system in which users can interact with a live simulation of autonomous cleaning robots. These robots have various sizes and functions, and can be assigned to different types of tasks across virtual rooms in need of cleaning. Different users interact with the application in unique ways, as specified further in the [user guide](docs/user_guide/USER_GUIDE.md). There are four major components that make up the application, as specified in the following section.

## Features

There are explicit instructions on how to build and run the application in the aforementioned user guide. Once the user is running the application, they interact directly with the **graphical user interface (GUI)**. The resultant data from their interactions with this interface are taken by the **data manager**. The data manager then handles further communication with the **database** and **simulation** components of the software. The database is responsible for logging and maintaining information about robots (properties, error status, etc.), tasks (completion status, etc.), and rooms (cleanliness, availability, etc.). The simulation is responsible for providing a virtual representation of the work autonomous cleaning robots do, providing live updates on robots' battery levels and water levels, simulating the work and completion of cleaning tasks the robots have been assigned to, and more. For further information on how these four components interact with one another to result in a functioning application, check out our `docs` folder, as specified below.

## Navigation

+ `docs` - this [folder](docs) maintains our project's documentation, including [design documents](docs/design/DESIGN.md), [contribution statements](docs/contributions) from team members, and a [user guide](docs/user_guide/USER_GUIDE.md) for how to use our software. 
+ `include` - this [folder](include) contains the included libraries for our software, for example our [Robot class](include/robot.hpp).
+ `src` - this [folder](src) provides the source files for the project, and are implementations of the header files from the included libraries. 
+ `wxWidgets/Project_Implementation` - this [folder](wxWidgets/Project_Implementation) consists of the files making up the GUI that users interface with. For general wxWidgets information, [see here](wxWidgets/README.md). For further project GUI information, [see here](wxWidgets/Project_Implementation/README.md).
+ `tests` - this [folder](tests) consists of a testing suite used to ensure the efficacy of our libraries and application.

## Changes Since Last Submission

+ Full implementation of add robot and remove robot functionality for field engineer, such that when a user makes the respective input, the robots are added or removed from the database itself, with the data manager handling some of the communication. 
+ Partial implementation of view robot status functionality, such that when a user double-clicks on a target robot, they can view robot properties that are saved in the database and retrieved using methods from the robot class in the simulation. 
+ RobotData struct, along with a vector of RobotData, moved to the data manager, where that vector is maintained for certain GUI interactions. Also, a string version of the robot's ID is added to this struct in order for simple confirmation messages to be printed when the user adds or deletes a robot. 
+ Refresh button functionality called automatically when adding robots to update user view seamlessly (as opposed to them manually needing to do it).
+ Refresh button functionality called automatically when deleting robots to make sure the user doesn't attempt to interact with a deleted robot.
+ Updated the Mongo_Adapter class to return robots when the robot collection is being read from in order to pass information from the database to the system manager. This then allows the GUI to easily access the data.
+ Updated the Mongo_Adapter class to have a function that returns all current robot ids in the database, so when the program is finished and exited the database can reinstantiate it's old state.
+ Updated the Mongo_Adapter test suite so that it fully tests all functionality of the class.
+ Changed Mongo_Adapter documentation and diagrams to represent the most recent version of the class.
+ Added README and User Guide documentation.
+ Updated the Data Manager class to integrate GUI, Simulation and Database.
+ Created a unit test for Data Manager.
+ Updated robot class for no longer store location, time length, add a new component task percent(how many percentage progress has the robot made). 
+ Updated robot do task loop(different sizes of robots and rooms result in different water and battery usage) and passed the unit test.
+ Created charge robot loop, robots can charge while not working. Passed unit tests on this stage, more unit tests for the future.
+ Updated the structure for simulation, all .cpp files for simulation is in simulation folder.




+ Finished implementation of view robot status, including integration throughout.
+ Shifted refresh button functionality to parent base class so all children can use it.
+ Added automatic refresh button calls in many places, including fixing a robot.
+ Added fixing robot functionality.
+ Added all task allocation funcionality, including ensuring the user can only assign valid tasks.
+ Added BM and FE-specific functionality of assigning cleaning task without specifying robot.
+ Added comprehensive error log functionality.
+ Added logic for differentiating both views and functionality across different user roles.
+ Added a number of functions to the Data Manager to facilitate integration between database and UI.
+ Created room text file and added functionality to read it into a vector of our Room class, and pass those rooms to database.
+ Added functionality for BM to make rooms available or unavailable.
