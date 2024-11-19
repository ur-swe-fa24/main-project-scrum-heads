+ Full implementation of add robot and remove robot functionality for field engineer, such that when a user makes the respective input, the robots are added or removed from the database itself, with the data manager handling some of the communication. 
    + I did the UI-specific work, and collaborated with Kay to get the data manager functional.
+ Partial implementation of view robot status functionality, such that when a user double-clicks on a target robot, they can view robot properties that are saved in the database and retrieved using methods from the robot class in the simulation. 
    + I did the UI-specific work, and collaborated with Kay to get the data manager functional.
+ RobotData struct, along with a vector of RobotData, moved to the data manager, where that vector is maintained for certain GUI interactions. Also, a string version of the robot's ID is added to this struct in order for simple confirmation messages to be printed when the user adds or deletes a robot. 
+ Refresh button functionality called automatically when adding robots to update user view seamlessly (as opposed to them manually needing to do it).
+ Refresh button functionality called automatically when deleting robots to make sure the user doesn't attempt to interact with a deleted robot.
+ README and User Guide documentation.