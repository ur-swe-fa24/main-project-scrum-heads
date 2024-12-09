///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-47-gcc2739ad)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "MyProjectBase.h"

///////////////////////////////////////////////////////////////////////////

baseFrame::baseFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* baseFrameSizer;
	baseFrameSizer = new wxBoxSizer( wxVERTICAL );

	feSelectButton = new wxButton( this, wxID_ANY, _("Field Engineer"), wxDefaultPosition, wxDefaultSize, 0 );
	baseFrameSizer->Add( feSelectButton, 0, wxALL, 5 );

	bmSelectButton = new wxButton( this, wxID_ANY, _("Building Manager"), wxDefaultPosition, wxDefaultSize, 0 );
	baseFrameSizer->Add( bmSelectButton, 0, wxALL, 5 );

	bsSelectButton = new wxButton( this, wxID_ANY, _("Building Staff"), wxDefaultPosition, wxDefaultSize, 0 );
	baseFrameSizer->Add( bsSelectButton, 0, wxALL, 5 );

	smSelectButton = new wxButton( this, wxID_ANY, _("Senior Management"), wxDefaultPosition, wxDefaultSize, 0 );
	baseFrameSizer->Add( smSelectButton, 0, wxALL, 5 );


	this->SetSizer( baseFrameSizer );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	feSelectButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( baseFrame::OnFESelectButtonClick ), NULL, this );
	bmSelectButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( baseFrame::OnBMSelectButtonClick ), NULL, this );
	bsSelectButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( baseFrame::OnBSSelectButtonClick ), NULL, this );
	smSelectButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( baseFrame::OnSMSelectButtonClick ), NULL, this );
}

baseFrame::~baseFrame()
{
}

feBaseFrame::feBaseFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* feBaseFrameSizer;
	feBaseFrameSizer = new wxBoxSizer( wxVERTICAL );

	feRefreshButton = new wxButton( this, wxID_ANY, _("Refresh"), wxDefaultPosition, wxDefaultSize, 0 );
	feBaseFrameSizer->Add( feRefreshButton, 0, wxALL, 5 );

	feTitleText = new wxStaticText( this, wxID_ANY, _("FIeld Engineer"), wxDefaultPosition, wxDefaultSize, 0 );
	feTitleText->Wrap( -1 );
	feBaseFrameSizer->Add( feTitleText, 0, wxALIGN_CENTER|wxALL, 5 );

	addRobotButton = new wxButton( this, wxID_ANY, _("Add Robot"), wxDefaultPosition, wxDefaultSize, 0 );
	feBaseFrameSizer->Add( addRobotButton, 0, wxALL, 5 );

	robotListBox = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	robotListBox->SetMinSize( wxSize( 500,100 ) );

	feBaseFrameSizer->Add( robotListBox, 0, wxALL, 5 );

	addTaskButton = new wxButton( this, wxID_ANY, _("Add Task"), wxDefaultPosition, wxDefaultSize, 0 );
	feBaseFrameSizer->Add( addTaskButton, 0, wxALL, 5 );

	taskListBox = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	taskListBox->SetMinSize( wxSize( 500,100 ) );

	feBaseFrameSizer->Add( taskListBox, 0, wxALL, 5 );

	roomLabelText = new wxStaticText( this, wxID_ANY, _("Rooms:"), wxDefaultPosition, wxDefaultSize, 0 );
	roomLabelText->Wrap( -1 );
	feBaseFrameSizer->Add( roomLabelText, 0, wxALL, 5 );

	roomListBox = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	roomListBox->SetMinSize( wxSize( 500,100 ) );

	feBaseFrameSizer->Add( roomListBox, 0, wxALL, 5 );


	this->SetSizer( feBaseFrameSizer );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	feRefreshButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( feBaseFrame::OnFERefreshButtonClick ), NULL, this );
	addRobotButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( feBaseFrame::OnAddRobotButtonClick ), NULL, this );
	robotListBox->Connect( wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, wxCommandEventHandler( feBaseFrame::OnRobotListBoxDClick ), NULL, this );
	addTaskButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( feBaseFrame::OnAddTaskButtonClick ), NULL, this );
	taskListBox->Connect( wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, wxCommandEventHandler( feBaseFrame::OnTaskListBoxDClick ), NULL, this );
}

feBaseFrame::~feBaseFrame()
{
}

bmBaseFrame::bmBaseFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bmBaseFrameSizer;
	bmBaseFrameSizer = new wxBoxSizer( wxVERTICAL );

	bmRefreshButton = new wxButton( this, wxID_ANY, _("Refresh"), wxDefaultPosition, wxDefaultSize, 0 );
	bmBaseFrameSizer->Add( bmRefreshButton, 0, wxALL, 5 );

	bmTitleText = new wxStaticText( this, wxID_ANY, _("Building Manager"), wxDefaultPosition, wxDefaultSize, 0 );
	bmTitleText->Wrap( -1 );
	bmBaseFrameSizer->Add( bmTitleText, 0, wxALIGN_CENTER|wxALL, 5 );

	robotsLabelText = new wxStaticText( this, wxID_ANY, _("Robots:"), wxDefaultPosition, wxDefaultSize, 0 );
	robotsLabelText->Wrap( -1 );
	bmBaseFrameSizer->Add( robotsLabelText, 0, wxALL, 5 );

	robotListBox = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	robotListBox->SetMinSize( wxSize( 500,100 ) );

	bmBaseFrameSizer->Add( robotListBox, 0, wxALL, 5 );

	addTaskButton = new wxButton( this, wxID_ANY, _("Add Task"), wxDefaultPosition, wxDefaultSize, 0 );
	bmBaseFrameSizer->Add( addTaskButton, 0, wxALL, 5 );

	taskListBox = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	taskListBox->SetMinSize( wxSize( 500,100 ) );

	bmBaseFrameSizer->Add( taskListBox, 0, wxALL, 5 );

	roomLabelText = new wxStaticText( this, wxID_ANY, _("Rooms:"), wxDefaultPosition, wxDefaultSize, 0 );
	roomLabelText->Wrap( -1 );
	bmBaseFrameSizer->Add( roomLabelText, 0, wxALL, 5 );

	roomListBox = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	roomListBox->SetMinSize( wxSize( 500,100 ) );

	bmBaseFrameSizer->Add( roomListBox, 0, wxALL, 5 );

	changeAvailabilityButton = new wxButton( this, wxID_ANY, _("Change Room Availability"), wxDefaultPosition, wxDefaultSize, 0 );
	changeAvailabilityButton->Enable( false );

	bmBaseFrameSizer->Add( changeAvailabilityButton, 0, wxALL, 5 );


	this->SetSizer( bmBaseFrameSizer );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	bmRefreshButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( bmBaseFrame::OnFERefreshButtonClick ), NULL, this );
	robotListBox->Connect( wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, wxCommandEventHandler( bmBaseFrame::OnRobotListBoxDClick ), NULL, this );
	addTaskButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( bmBaseFrame::OnAddTaskButtonClick ), NULL, this );
	taskListBox->Connect( wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, wxCommandEventHandler( bmBaseFrame::OnTaskListBoxDClick ), NULL, this );
	roomListBox->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( bmBaseFrame::OnRoomTaskSelect ), NULL, this );
	changeAvailabilityButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( bmBaseFrame::OnChangeRoomAButtonClick ), NULL, this );
}

bmBaseFrame::~bmBaseFrame()
{
}

bsBaseFrame::bsBaseFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bsBaseFrameSizer;
	bsBaseFrameSizer = new wxBoxSizer( wxVERTICAL );

	bsRefreshButton = new wxButton( this, wxID_ANY, _("Refresh"), wxDefaultPosition, wxDefaultSize, 0 );
	bsBaseFrameSizer->Add( bsRefreshButton, 0, wxALL, 5 );

	bsTitleText = new wxStaticText( this, wxID_ANY, _("Building Staff"), wxDefaultPosition, wxDefaultSize, 0 );
	bsTitleText->Wrap( -1 );
	bsBaseFrameSizer->Add( bsTitleText, 0, wxALIGN_CENTER|wxALL, 5 );

	robotsLabelText = new wxStaticText( this, wxID_ANY, _("Robots:"), wxDefaultPosition, wxDefaultSize, 0 );
	robotsLabelText->Wrap( -1 );
	bsBaseFrameSizer->Add( robotsLabelText, 0, wxALL, 5 );

	robotListBox = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	robotListBox->SetMinSize( wxSize( 500,100 ) );

	bsBaseFrameSizer->Add( robotListBox, 0, wxALL, 5 );

	addTaskButton = new wxButton( this, wxID_ANY, _("Add Task"), wxDefaultPosition, wxDefaultSize, 0 );
	bsBaseFrameSizer->Add( addTaskButton, 0, wxALL, 5 );

	taskListBox = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	taskListBox->SetMinSize( wxSize( 500,100 ) );

	bsBaseFrameSizer->Add( taskListBox, 0, wxALL, 5 );

	roomLabelText = new wxStaticText( this, wxID_ANY, _("Rooms:"), wxDefaultPosition, wxDefaultSize, 0 );
	roomLabelText->Wrap( -1 );
	bsBaseFrameSizer->Add( roomLabelText, 0, wxALL, 5 );

	roomListBox = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	roomListBox->SetMinSize( wxSize( 500,100 ) );

	bsBaseFrameSizer->Add( roomListBox, 0, wxALL, 5 );


	this->SetSizer( bsBaseFrameSizer );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	bsRefreshButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( bsBaseFrame::OnFERefreshButtonClick ), NULL, this );
	robotListBox->Connect( wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, wxCommandEventHandler( bsBaseFrame::OnRobotListBoxDClick ), NULL, this );
	addTaskButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( bsBaseFrame::OnAddTaskButtonClick ), NULL, this );
	taskListBox->Connect( wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, wxCommandEventHandler( bsBaseFrame::OnTaskListBoxDClick ), NULL, this );
}

bsBaseFrame::~bsBaseFrame()
{
}

smBaseFrame::smBaseFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* smBaseFrameSizer;
	smBaseFrameSizer = new wxBoxSizer( wxVERTICAL );

	smRefreshButton = new wxButton( this, wxID_ANY, _("Refresh"), wxDefaultPosition, wxDefaultSize, 0 );
	smBaseFrameSizer->Add( smRefreshButton, 0, wxALL, 5 );

	smTitleText = new wxStaticText( this, wxID_ANY, _("Senior Management"), wxDefaultPosition, wxDefaultSize, 0 );
	smTitleText->Wrap( -1 );
	smBaseFrameSizer->Add( smTitleText, 0, wxALIGN_CENTER|wxALL, 5 );


	this->SetSizer( smBaseFrameSizer );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	smRefreshButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( smBaseFrame::OnSMRefreshButtonClick ), NULL, this );
}

smBaseFrame::~smBaseFrame()
{
}

AddRobotFrame::AddRobotFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* addRobotFrameSizer;
	addRobotFrameSizer = new wxBoxSizer( wxVERTICAL );

	robotSizeText = new wxStaticText( this, wxID_ANY, _("Robot Size:"), wxDefaultPosition, wxDefaultSize, 0 );
	robotSizeText->Wrap( -1 );
	addRobotFrameSizer->Add( robotSizeText, 0, wxALL, 5 );

	wxString robotSizeDropdownChoices[] = { _("Small"), _("Medium"), _("Large") };
	int robotSizeDropdownNChoices = sizeof( robotSizeDropdownChoices ) / sizeof( wxString );
	robotSizeDropdown = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, robotSizeDropdownNChoices, robotSizeDropdownChoices, 0 );
	robotSizeDropdown->SetSelection( 0 );
	addRobotFrameSizer->Add( robotSizeDropdown, 0, wxALL, 5 );

	robotFunctionText = new wxStaticText( this, wxID_ANY, _("Robot Function:"), wxDefaultPosition, wxDefaultSize, 0 );
	robotFunctionText->Wrap( -1 );
	addRobotFrameSizer->Add( robotFunctionText, 0, wxALL, 5 );

	wxString robotFunctionDropdownChoices[] = { _("Scrub"), _("Vacuum"), _("Shampoo") };
	int robotFunctionDropdownNChoices = sizeof( robotFunctionDropdownChoices ) / sizeof( wxString );
	robotFunctionDropdown = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, robotFunctionDropdownNChoices, robotFunctionDropdownChoices, 0 );
	robotFunctionDropdown->SetSelection( 0 );
	addRobotFrameSizer->Add( robotFunctionDropdown, 0, wxALL, 5 );

	createRobotButton = new wxButton( this, wxID_ANY, _("Create Robot"), wxDefaultPosition, wxDefaultSize, 0 );
	createRobotButton->Enable( false );

	addRobotFrameSizer->Add( createRobotButton, 0, wxALL, 5 );


	this->SetSizer( addRobotFrameSizer );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	robotSizeDropdown->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( AddRobotFrame::OnRobotSizeChoice ), NULL, this );
	robotFunctionDropdown->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( AddRobotFrame::OnRobotFunctionChoice ), NULL, this );
	createRobotButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AddRobotFrame::OnCreateRobotButtonClick ), NULL, this );
}

AddRobotFrame::~AddRobotFrame()
{
}

robotInfoFrame::robotInfoFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* robotInfoFrameSizer;
	robotInfoFrameSizer = new wxBoxSizer( wxVERTICAL );

	titleText = new wxStaticText( this, wxID_ANY, _("Title Placeholder"), wxDefaultPosition, wxDefaultSize, 0 );
	titleText->Wrap( -1 );
	robotInfoFrameSizer->Add( titleText, 0, wxALIGN_CENTER|wxALIGN_TOP|wxALL, 5 );

	propertiesLabelText = new wxStaticText( this, wxID_ANY, _("Properties:"), wxDefaultPosition, wxDefaultSize, 0 );
	propertiesLabelText->Wrap( -1 );
	robotInfoFrameSizer->Add( propertiesLabelText, 0, wxALL, 5 );

	robotPropertiesText = new wxStaticText( this, wxID_ANY, _("Properties Placeholder"), wxDefaultPosition, wxDefaultSize, 0 );
	robotPropertiesText->Wrap( -1 );
	robotInfoFrameSizer->Add( robotPropertiesText, 0, wxALL, 5 );

	statusLabelText = new wxStaticText( this, wxID_ANY, _("Status:"), wxDefaultPosition, wxDefaultSize, 0 );
	statusLabelText->Wrap( -1 );
	robotInfoFrameSizer->Add( statusLabelText, 0, wxALL, 5 );

	robotStatusText = new wxStaticText( this, wxID_ANY, _("Status Placeholder"), wxDefaultPosition, wxDefaultSize, 0 );
	robotStatusText->Wrap( -1 );
	robotInfoFrameSizer->Add( robotStatusText, 0, wxALL, 5 );

	errorLogLabelText = new wxStaticText( this, wxID_ANY, _("Error Log:"), wxDefaultPosition, wxDefaultSize, 0 );
	errorLogLabelText->Wrap( -1 );
	robotInfoFrameSizer->Add( errorLogLabelText, 0, wxALL, 5 );

	robotErrorLogTextBox = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	robotErrorLogTextBox->SetMinSize( wxSize( 720,100 ) );

	robotInfoFrameSizer->Add( robotErrorLogTextBox, 0, wxALL, 5 );

	removeRobotButton = new wxButton( this, wxID_ANY, _("Remove"), wxDefaultPosition, wxDefaultSize, 0 );
	robotInfoFrameSizer->Add( removeRobotButton, 0, wxALL, 5 );

	fixRobotButton = new wxButton( this, wxID_ANY, _("Fix"), wxDefaultPosition, wxDefaultSize, 0 );
	fixRobotButton->Enable( false );

	robotInfoFrameSizer->Add( fixRobotButton, 0, wxALL, 5 );


	this->SetSizer( robotInfoFrameSizer );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	removeRobotButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( robotInfoFrame::OnRemoveRobotButtonClick ), NULL, this );
	fixRobotButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( robotInfoFrame::OnFixRobotButtonClick ), NULL, this );
}

robotInfoFrame::~robotInfoFrame()
{
}

addTaskFrame::addTaskFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* addTaskFrameSizer;
	addTaskFrameSizer = new wxBoxSizer( wxVERTICAL );

	selectRoomsTitleText = new wxStaticText( this, wxID_ANY, _("Select Room:"), wxDefaultPosition, wxDefaultSize, 0 );
	selectRoomsTitleText->Wrap( -1 );
	addTaskFrameSizer->Add( selectRoomsTitleText, 0, wxALL, 5 );

	roomSelectionListBox = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	roomSelectionListBox->SetMinSize( wxSize( 500,100 ) );

	addTaskFrameSizer->Add( roomSelectionListBox, 0, wxALL, 5 );

	selectRobotsTitleText = new wxStaticText( this, wxID_ANY, _("Select Robot:"), wxDefaultPosition, wxDefaultSize, 0 );
	selectRobotsTitleText->Wrap( -1 );
	addTaskFrameSizer->Add( selectRobotsTitleText, 0, wxALL, 5 );

	robotSelectionListBox = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	robotSelectionListBox->SetMinSize( wxSize( 500,100 ) );

	addTaskFrameSizer->Add( robotSelectionListBox, 0, wxALL, 5 );

	createTaskButton = new wxButton( this, wxID_ANY, _("Create Task"), wxDefaultPosition, wxDefaultSize, 0 );
	createTaskButton->Enable( false );

	addTaskFrameSizer->Add( createTaskButton, 0, wxALL, 5 );


	this->SetSizer( addTaskFrameSizer );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	roomSelectionListBox->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( addTaskFrame::OnRoomTaskSelect ), NULL, this );
	robotSelectionListBox->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( addTaskFrame::OnRobotTaskSelect ), NULL, this );
	createTaskButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( addTaskFrame::OnCreateTaskButtonClick ), NULL, this );
}

addTaskFrame::~addTaskFrame()
{
}

viewTaskFrame::viewTaskFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* viewTaskFrameSizer;
	viewTaskFrameSizer = new wxBoxSizer( wxVERTICAL );

	taskStatusTitleText = new wxStaticText( this, wxID_ANY, _("Task Status:"), wxDefaultPosition, wxDefaultSize, 0 );
	taskStatusTitleText->Wrap( -1 );
	viewTaskFrameSizer->Add( taskStatusTitleText, 0, wxALL, 5 );

	taskStatusPlaceholderText = new wxStaticText( this, wxID_ANY, _("Task status placeholder"), wxDefaultPosition, wxDefaultSize, 0 );
	taskStatusPlaceholderText->Wrap( -1 );
	viewTaskFrameSizer->Add( taskStatusPlaceholderText, 0, wxALL, 5 );

	roomTitleText = new wxStaticText( this, wxID_ANY, _("Room:"), wxDefaultPosition, wxDefaultSize, 0 );
	roomTitleText->Wrap( -1 );
	viewTaskFrameSizer->Add( roomTitleText, 0, wxALL, 5 );

	roomTaskListBox = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	viewTaskFrameSizer->Add( roomTaskListBox, 0, wxALL, 5 );

	robotTitleText = new wxStaticText( this, wxID_ANY, _("Robot:"), wxDefaultPosition, wxDefaultSize, 0 );
	robotTitleText->Wrap( -1 );
	viewTaskFrameSizer->Add( robotTitleText, 0, wxALL, 5 );

	robotTaskListBox = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	viewTaskFrameSizer->Add( robotTaskListBox, 0, wxALL, 5 );


	this->SetSizer( viewTaskFrameSizer );
	this->Layout();

	this->Centre( wxBOTH );
}

viewTaskFrame::~viewTaskFrame()
{
}
