# Customer Interview Document

## User Roles

- **Senior Management**: Upper-level managers do not care about accessing specifics such as individual robot error logs, but are concerned about big picture issues, primarily relating to robot efficiency. They will want to easily view data related to how robots are being utilized, how productive and energy-efficient they are, and what error rate the robots have. Additionally, they do not need the functionality of actually tasking robots.

- **Building Manager**: Building managers are mainly concerned about their fleet of robots (for a particular building) as a whole. They handle the primary functions of assigning tasks to a fleet of robots and viewing the status of that fleet so they can make informed decisions.

- **Building Staff/Operator**: These operators are similar to building managers but are focused more on individual robots. They also want to view robot status and assign cleaning tasks but are not managing an entire fleet for a building. These are the people who receive some training from Cobotiq to interface with the robots and be the first line of defense against a robot not performing its functionality correctly.

- **Field Engineer**: This would be someone from Cobotiq, who has far more training with repairing bugged robots. While they have the same abilities as the building managers, they also have access to a detailed error log and robot status database. Additional abilities include being able to “fix” bugged robots and being able to add and remove robots from the system.

## Simulation Engine

The simulation engine will be in discrete time. It will need to simulate how robots of different sizes and types (i.e., scrubbers) operate in different spatial and material (i.e., floor type) environments.

## Status Database

The status database will maintain the information about the robots (i.e., robot type, size). The database will also contain the tasks that are currently being performed and tasks that have been completed (i.e., job number, type). There will also be an error table that keeps track of all the errors that occurred during the operation of the robots. Lastly, a room table that contains all the information of the rooms. This information will be accessible by the system manager and the manager will be able to send data to the database to be added.

## System Manager

The System Manager is the connection point between the three other components. It will efficiently coordinate between the GUI, Simulation Engine, and Status Database, so that all components interact seamlessly, and the entire cleaning robot fleet operates smoothly and effectively. It will identify and address system faults or errors, synchronize data, and send tasks and receive status from the Simulation Engine.

## Graphical UI

The UI will be users' main point of interaction based upon customer role. It will allow the users to receive the varying appropriate information for each user role from the system manager. The UI will also allow users to assign tasks to groups of robots for building-encapsulating missions. It will also have a feature that shows general metrics about robot efficiency, utilization, and error rates. Lastly, the view for the field engineer will show detailed robot status, view detailed error logs, fix bugged robots, and add or remove robots from the system.

## Robots

- Robots come in three different sizes: small, medium, and large. These sizes have two important implications for our simulation. First of all, larger robots have larger batteries and can therefore clean for longer. However, depending on the layout of the room, larger robots may have difficulty in certain areas due to their size restrictions, and a smaller robot may be necessary.

- Robots are also equipped with one of three different functionalities: scrubbing, vacuuming, and shampooing. Certain functionalities are compatible with certain floor types and should not be used elsewhere.
  - **Scrubbers** should only operate on wood and tile floors.
  - **Vacuumers** are compatible with all floor types.
  - **Shampooers** should only operate on carpet floors.

- Robots also have three potential tasks that can be assigned.
  - Clean a specified room.
  - Return to the charging point.
  - Go offline.

## Building Features

The simulated buildings operate on a number of characteristic restraints.

- Any single building will have between 1 and 10 rooms, which should be specified at the start of the simulation.
- Any single room has three possible sizes: large, medium, and small. This will be important to consider when assigning robots with various battery lives.
- Any single room can have one of three floor types: wood, carpet, or tile. A single room will not have multiple floor types.
- Certain rooms may be indicated as off limits by the building manager. If this is the case, robots should not enter those rooms.

## Optional Bonus Features

- More precise error logs in general seem to be a particular issue for Cobotiq’s field engineers. When arriving at a scene of a bugged robot, it is difficult to piece together the error log to figure out what happened, where it happened, and why it happened. One specific feature they asked to be implemented was a map of the robot’s movement and activity up to the point of an error that is clearly timestamped, which would make it far easier to figure out the issue and prevent it from happening again.

- A robot communication system that allows them to work together more functionally. Currently, if two robots were within the same room, they would not acknowledge each other as cleaning parts of the room and would clean everything twice, unless an operator had manually programmed them to stick to one half of the room. If the robots could communicate amongst themselves to signal what parts of the job they each had done, they would be able to dynamically redistribute the work in the room as needed. For example, if a larger and smaller robot were tasked to a room together, the smaller robot could tackle the tighter spaces, while the larger robot could do the majority of the open space.

- Although the shampoo and scrubbing robots should only operate on their intended floor type, vacuum robots can work on all types of floors. Implementing a system to handle this transition between floor types is another optional feature.

- Cobotiq’s current typical use case is having a single operator deploy their cleaning robots on empty floors late at night when there is no foot traffic. The current robots would be inefficient in the presence of foot traffic. Theoretically, it would be nice to work towards a cleaning robot that could operate with humans moving unpredictably all around it. In addition to the simulation change of adding foot traffic, you could also implement some safety features such as a warning tone playing when a robot gets too close to a human.

- Depending on the nature of the dirtiness of a room, a real-life operator might adjust the cleaning settings on a robot, such as the rotational intensity of the brushes in a scrubber or the quantity of shampoo a shampooer is dispensing. Including this in the simulation is another optional feature for integration.

- Expanding on the previous point, the cleaning you do for the floor in general will likely differ from a particular spot that is particularly soiled, such as where someone spilled their coffee. We could include “spots” in our simulation that need extra attention and cleaning time, and the robots would have to recognize and treat these spots accordingly.

- The robots’ current functionality does not allow them to traverse floors, so instead of a building manager dropping the robot off on the front doorstep for it to clean the entire building, they have to stick around to bring it to each new floor. Cobotiq mentioned that some cleaning robots overseas have the ability to directly interface with elevators to traverse floors and solve this problem, which could be a possible implementation.

- When simulating foot traffic, certain areas could be blocked on a robot’s first bypass of that area. As it currently stands, there is no algorithm to have that robot circle back to a spot it missed on its cleaning cycle, so it would return to its localization point with potentially dirty areas. We could implement some sort of system to have robots double check areas that were previously inaccessible to them before returning home.

- A task prioritization system that allows the robot’s attention to be shifted to a higher priority task if assigned one.

- A user authentication to make sure a user has clearance for information access.
