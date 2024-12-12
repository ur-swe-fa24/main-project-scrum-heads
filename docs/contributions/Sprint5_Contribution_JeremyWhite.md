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