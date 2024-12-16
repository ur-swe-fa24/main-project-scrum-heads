#include "baseFrame.hpp"
#include <wx/wx.h>

MyBaseFrame::MyBaseFrame(wxWindow* parent, DataManager* dataManager)
    : baseFrame(parent), dataManager(dataManager)  // Call the base class constructor
{
    // Connect the button event to the overridden method
    feSelectButton->Bind(wxEVT_BUTTON, &MyBaseFrame::OnFESelectButtonClick, this);
    smSelectButton->Bind(wxEVT_BUTTON, &MyBaseFrame::OnSMSelectButtonClick, this);
    bsSelectButton->Bind(wxEVT_BUTTON, &MyBaseFrame::OnBSSelectButtonClick, this);
    bmSelectButton->Bind(wxEVT_BUTTON, &MyBaseFrame::OnBMSelectButtonClick, this);
}

void MyBaseFrame::OnFESelectButtonClick(wxCommandEvent& event)
{
    MyFEBaseFrame* feFrame = new MyFEBaseFrame(nullptr, dataManager, this);
    
    feFrame->Show(true);
}

void MyBaseFrame::OnSMSelectButtonClick(wxCommandEvent& event)
{
    MySMBaseFrame* smFrame = new MySMBaseFrame(nullptr, dataManager, this);
    smFrame->Show(true);
}

void MyBaseFrame::OnBSSelectButtonClick(wxCommandEvent& event)
{
    MyBSBaseFrame* bsFrame = new MyBSBaseFrame(nullptr, dataManager, this);
    bsFrame->Show(true);
}

void MyBaseFrame::OnBMSelectButtonClick(wxCommandEvent& event)
{
    MyBMBaseFrame* bmFrame = new MyBMBaseFrame(nullptr, dataManager, this);
    bmFrame->Show(true);
}

void MyBaseFrame::HandleRobotListBoxDClick(wxWindow* parent, wxListBox* robotListBox, std::string userRole)
{
    //retrieves the updated vector of RobotData
    std::vector<RobotData>& robots = dataManager->GetRobots();

    int selectionIndex = robotListBox->GetSelection(); //gets the selection index of whichever robot you clicked on in the wxListBox

    //if selection index is found and smaller than vector of RobotData (should always be the case)
    if (selectionIndex != wxNOT_FOUND && selectionIndex < robots.size()) {

        RobotData selectedRobot = robots[selectionIndex]; //finds the coordinated robot from the robots vector

        //converts robot ID to integer to use as key for database
        int robotId = std::stoi(selectedRobot.robotID);

        //complete robot information, accessed using the robot's ID
        const robots::Robots& completeRobot = dataManager->GetAllRobotInfo(robotId);

        // Create robotInfoFrame, passes through string to function as title to display robotID (not currently implemented visually)
        //also passed through the completed robot information (full robot class info) and instance of dataManager
        MyRobotInfoFrame* infoFrame = new MyRobotInfoFrame(parent, "Robot ID: " + selectedRobot.robotID, completeRobot, dataManager, userRole);
        // Set the appropriate data and show the frame
        infoFrame->SetRobotData(completeRobot);
        infoFrame->Show();
    }
}

void MyBaseFrame::HandleTaskListBoxDClick(wxWindow* parent, wxListBox* taskListBox)
{
    //implement logic to open task info window by double clicking task here
    //retrieves the updated vector of RobotData
    std::vector<TaskData>& tasks = dataManager->GetTasks();

    int selectionIndex = taskListBox->GetSelection(); //gets the selection index of whichever robot you clicked on in the wxListBox

    //if selection index is found and smaller than vector of RobotData (should always be the case)
    if (selectionIndex != wxNOT_FOUND && selectionIndex < tasks.size()) {

        TaskData selectedTask = tasks[selectionIndex]; //finds the coordinated task from the tasks vector

        // Create viewTaskFrame
        MyViewTaskFrame* taskInfoFrame = new MyViewTaskFrame(parent);
    
        //converts robot ID to integer to use as key for database
        int robotId = std::stoi(selectedTask.taskRobot.robotID);

        //complete robot information, accessed using the robot's ID
        const robots::Robots& completeRobot = dataManager->GetAllRobotInfo(robotId);

        taskInfoFrame->SetTaskData(completeRobot);

        taskInfoFrame->Show();
    }
}

void MyBaseFrame::HandleRefreshButton(wxCommandEvent& event, wxListBox* robotListBox, wxListBox* taskListBox, wxListBox* roomListBox)
{
    // Access the shared RobotData vector from DataManager and display each robot
    //this is just used to display simple information (id, size, function) to user
    std::vector<RobotData>& robots = dataManager->GetRobots();

    // std::vector<TaskData>& tasks = dataManager->GetTasks();

    //updates the TaskData vector
    dataManager->UpdateTaskData();

    // Clear the existing display in the robotListBox (so same robot doesn't get added multiple times)
    robotListBox->Clear();

    // Clear the existing display in the taskListBox (so same task doesn't get added multiple times)
    taskListBox->Clear();

    // Clear the existing display in the roomListBox (so same task doesn't get added multiple times)
    roomListBox->Clear();

    // Iterate through the vector and display each robot's information
    for (RobotData& robot : robots) {

        //creates string to hold status as color
        std::string statusBubble;
        //gets task status of each robot, sets status bubble accordingly
        //note: this may not be the best implementation moving forward, as this needs live updates from simulation, but it is proof of concept
        //could transfer to wxListCtrl if you want to use colored text
        robots::Robots localRobot = dataManager->GetAllRobotInfo(std::stoi(robot.robotID));
        std::string robotStatus = localRobot.get_task_status();
        std::string errorStatus = localRobot.get_error_status();
        if (robotStatus == "Available")
        {
            statusBubble = "🟢";
        }
        else if (robotStatus == "Ongoing")
        {
            statusBubble = "🟡";
        }
        else if (errorStatus != "")
        {
            statusBubble = "🔴";
        }


        wxString robotInfo = wxString::Format(statusBubble + " ID: " + robot.robotID + " (Size: " + robot.robotSize + ", Function: " + robot.robotFunction + ")"); //will be ugly for now a placeholder for ID or whatever else later
        robotListBox->Append(robotInfo);  // Adding each robot info to the ListBox
    }

    //gets all tasks, ongoing or otherwise
    std::vector<robots::Robots> taskVector = dataManager->GetTasksTable();

    //iterate through robot vector to get all tasks
    for (robots::Robots task : taskVector) 
    {
        //creates string to hold status as color
        std::string statusBubble;

        //gets task status for each task
        std::string taskStatus = task.get_task_status();

        //sets appropriate visual cue
        if (taskStatus == "Ongoing")
        {
            statusBubble = "🟢";
        }
        else
        {
            statusBubble = "🔴";
        }

        //gets room ID
        Room taskRoom = task.get_task_room();
        std::string roomID = std::to_string(taskRoom.getRoomNumber());

        //gets robot ID
        std::string robotID = std::to_string(task.get_id());

        std::string taskInfo = statusBubble + " Room: " + roomID + ", Robot: " + robotID; //will be ugly for now a placeholder for ID or whatever else later
        taskListBox->Append(taskInfo);  // Adding each robot info to the ListBox
    }

    //gets rooms from dataManager
    std::vector<Room> rooms = dataManager->GetRooms();

    //iterate through rooms and append info to list box
    for (Room room : rooms)
    {
        //creates string to hold status as color
        std::string statusBubble;

        //note: these availabilities may not be the correct words
        std::string roomAvailability = room.getAvailability();
        if (roomAvailability == "Available")
        {
            statusBubble = "🟢";
        }
        else if (roomAvailability == "Busy")
        {
            statusBubble = "🟡";
        }
        else if (roomAvailability == "Unavailable")
        {
            statusBubble = "🔴";
        }

        std::string roomID = std::to_string(room.getRoomNumber());
        std::string roomSize = room.getRoomSize();
        std::string floorType = room.getFloorType();
        std::string roomInfo = statusBubble + " ID: " + roomID + " (Size: " + roomSize + ", Floor Type: " + floorType + ")";
        roomListBox->Append(roomInfo);
    }
}

void MyBaseFrame::AddTaskToList(const wxString& roomSelection, const RobotData& robotSelection)
{
    //create robot with user-specified size and function. ID string created as 0, actually assigned in DataManager::AddRobot()
    TaskData task = {roomSelection, robotSelection};

    //adds created task to vector of TaskData in data manager
    dataManager->AddTask(task);

    wxMessageBox("Task created in room: " + roomSelection + ", using robot with ID: " + robotSelection.robotID, "Success!", wxOK | wxICON_INFORMATION);
}

