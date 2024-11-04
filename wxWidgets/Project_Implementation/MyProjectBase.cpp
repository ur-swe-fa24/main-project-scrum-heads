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

	feButton = new wxButton( this, wxID_ANY, _("Field Engineer Info"), wxDefaultPosition, wxDefaultSize, 0 );
	feBaseFrameSizer->Add( feButton, 0, wxALL, 5 );

	feTextControl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY );
	feBaseFrameSizer->Add( feTextControl, 0, wxALL, 5 );

	feRefreshButton = new wxButton( this, wxID_ANY, _("Refresh"), wxDefaultPosition, wxDefaultSize, 0 );
	feBaseFrameSizer->Add( feRefreshButton, 0, wxALL, 5 );

	addRobotButton = new wxButton( this, wxID_ANY, _("Add Robot"), wxDefaultPosition, wxDefaultSize, 0 );
	feBaseFrameSizer->Add( addRobotButton, 0, wxALL, 5 );

	robotListBox = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	feBaseFrameSizer->Add( robotListBox, 0, wxALL, 5 );


	this->SetSizer( feBaseFrameSizer );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	feButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( feBaseFrame::OnFEButtonClick ), NULL, this );
	feRefreshButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( feBaseFrame::OnFERefreshButtonClick ), NULL, this );
	addRobotButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( feBaseFrame::OnAddRobotButtonClick ), NULL, this );
	robotListBox->Connect( wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, wxCommandEventHandler( feBaseFrame::OnRobotListBoxDClick ), NULL, this );
}

feBaseFrame::~feBaseFrame()
{
}

bmBaseFrame::bmBaseFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bmBaseFrameSizer;
	bmBaseFrameSizer = new wxBoxSizer( wxVERTICAL );

	bmButton = new wxButton( this, wxID_ANY, _("Building Manager Info"), wxDefaultPosition, wxDefaultSize, 0 );
	bmBaseFrameSizer->Add( bmButton, 0, wxALL, 5 );


	this->SetSizer( bmBaseFrameSizer );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	bmButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( bmBaseFrame::OnBMButtonClick ), NULL, this );
}

bmBaseFrame::~bmBaseFrame()
{
}

bsBaseFrame::bsBaseFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bsBaseFrameSizer;
	bsBaseFrameSizer = new wxBoxSizer( wxVERTICAL );

	bsButton = new wxButton( this, wxID_ANY, _("Building Staff Info"), wxDefaultPosition, wxDefaultSize, 0 );
	bsBaseFrameSizer->Add( bsButton, 0, wxALL, 5 );


	this->SetSizer( bsBaseFrameSizer );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	bsButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( bsBaseFrame::OnBSButtonClick ), NULL, this );
}

bsBaseFrame::~bsBaseFrame()
{
}

smBaseFrame::smBaseFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* smBaseFrameSizer;
	smBaseFrameSizer = new wxBoxSizer( wxVERTICAL );

	smButton = new wxButton( this, wxID_ANY, _("Senior Management Info"), wxDefaultPosition, wxDefaultSize, 0 );
	smBaseFrameSizer->Add( smButton, 0, wxALL, 5 );


	this->SetSizer( smBaseFrameSizer );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	smButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( smBaseFrame::OnSMButtonClick ), NULL, this );
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

	robotErrorLogText = new wxStaticText( this, wxID_ANY, _("Errors Placeholder"), wxDefaultPosition, wxDefaultSize, 0 );
	robotErrorLogText->Wrap( -1 );
	robotInfoFrameSizer->Add( robotErrorLogText, 0, wxALL, 5 );


	this->SetSizer( robotInfoFrameSizer );
	this->Layout();

	this->Centre( wxBOTH );
}

robotInfoFrame::~robotInfoFrame()
{
}
