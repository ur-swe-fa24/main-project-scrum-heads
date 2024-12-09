///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-47-gcc2739ad)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/button.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/frame.h>
#include <wx/stattext.h>
#include <wx/listbox.h>
#include <wx/choice.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class baseFrame
///////////////////////////////////////////////////////////////////////////////
class baseFrame : public wxFrame
{
	private:

	protected:
		wxButton* feSelectButton;
		wxButton* bmSelectButton;
		wxButton* bsSelectButton;
		wxButton* smSelectButton;

		// Virtual event handlers, override them in your derived class
		virtual void OnFESelectButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBMSelectButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBSSelectButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSMSelectButtonClick( wxCommandEvent& event ) { event.Skip(); }


	public:

		baseFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~baseFrame();

};

///////////////////////////////////////////////////////////////////////////////
/// Class feBaseFrame
///////////////////////////////////////////////////////////////////////////////
class feBaseFrame : public wxFrame
{
	private:

	protected:
		wxButton* feRefreshButton;
		wxStaticText* feTitleText;
		wxButton* addRobotButton;
		wxListBox* robotListBox;
		wxButton* addTaskButton;
		wxListBox* taskListBox;
		wxStaticText* roomLabelText;
		wxListBox* roomListBox;

		// Virtual event handlers, override them in your derived class
		virtual void OnFERefreshButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAddRobotButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRobotListBoxDClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAddTaskButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTaskListBoxDClick( wxCommandEvent& event ) { event.Skip(); }


	public:

		feBaseFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 764,524 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~feBaseFrame();

};

///////////////////////////////////////////////////////////////////////////////
/// Class bmBaseFrame
///////////////////////////////////////////////////////////////////////////////
class bmBaseFrame : public wxFrame
{
	private:

	protected:
		wxButton* bmRefreshButton;
		wxStaticText* bmTitleText;
		wxStaticText* robotsLabelText;
		wxListBox* robotListBox;
		wxButton* addTaskButton;
		wxListBox* taskListBox;
		wxStaticText* roomLabelText;
		wxListBox* roomListBox;
		wxButton* changeAvailabilityButton;

		// Virtual event handlers, override them in your derived class
		virtual void OnFERefreshButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRobotListBoxDClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAddTaskButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTaskListBoxDClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRoomTaskSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnChangeRoomAButtonClick( wxCommandEvent& event ) { event.Skip(); }


	public:

		bmBaseFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 725,538 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~bmBaseFrame();

};

///////////////////////////////////////////////////////////////////////////////
/// Class bsBaseFrame
///////////////////////////////////////////////////////////////////////////////
class bsBaseFrame : public wxFrame
{
	private:

	protected:
		wxButton* bsRefreshButton;
		wxStaticText* bsTitleText;
		wxStaticText* robotsLabelText;
		wxListBox* robotListBox;
		wxButton* addTaskButton;
		wxListBox* taskListBox;
		wxStaticText* roomLabelText;
		wxListBox* roomListBox;

		// Virtual event handlers, override them in your derived class
		virtual void OnFERefreshButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRobotListBoxDClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAddTaskButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTaskListBoxDClick( wxCommandEvent& event ) { event.Skip(); }


	public:

		bsBaseFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 711,528 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~bsBaseFrame();

};

///////////////////////////////////////////////////////////////////////////////
/// Class smBaseFrame
///////////////////////////////////////////////////////////////////////////////
class smBaseFrame : public wxFrame
{
	private:

	protected:
		wxButton* smRefreshButton;
		wxStaticText* smTitleText;

		// Virtual event handlers, override them in your derived class
		virtual void OnSMRefreshButtonClick( wxCommandEvent& event ) { event.Skip(); }


	public:

		smBaseFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~smBaseFrame();

};

///////////////////////////////////////////////////////////////////////////////
/// Class AddRobotFrame
///////////////////////////////////////////////////////////////////////////////
class AddRobotFrame : public wxFrame
{
	private:

	protected:
		wxStaticText* robotSizeText;
		wxChoice* robotSizeDropdown;
		wxStaticText* robotFunctionText;
		wxChoice* robotFunctionDropdown;
		wxButton* createRobotButton;

		// Virtual event handlers, override them in your derived class
		virtual void OnRobotSizeChoice( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRobotFunctionChoice( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCreateRobotButtonClick( wxCommandEvent& event ) { event.Skip(); }


	public:

		AddRobotFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~AddRobotFrame();

};

///////////////////////////////////////////////////////////////////////////////
/// Class robotInfoFrame
///////////////////////////////////////////////////////////////////////////////
class robotInfoFrame : public wxFrame
{
	private:

	protected:
		wxStaticText* titleText;
		wxStaticText* propertiesLabelText;
		wxStaticText* robotPropertiesText;
		wxStaticText* statusLabelText;
		wxStaticText* robotStatusText;
		wxStaticText* errorLogLabelText;
		wxListBox* robotErrorLogTextBox;
		wxButton* removeRobotButton;
		wxButton* fixRobotButton;

		// Virtual event handlers, override them in your derived class
		virtual void OnRemoveRobotButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnFixRobotButtonClick( wxCommandEvent& event ) { event.Skip(); }


	public:

		robotInfoFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 733,492 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~robotInfoFrame();

};

///////////////////////////////////////////////////////////////////////////////
/// Class addTaskFrame
///////////////////////////////////////////////////////////////////////////////
class addTaskFrame : public wxFrame
{
	private:

	protected:
		wxStaticText* selectRoomsTitleText;
		wxListBox* roomSelectionListBox;
		wxStaticText* selectRobotsTitleText;
		wxListBox* robotSelectionListBox;
		wxButton* createTaskButton;

		// Virtual event handlers, override them in your derived class
		virtual void OnRoomTaskSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRobotTaskSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCreateTaskButtonClick( wxCommandEvent& event ) { event.Skip(); }


	public:

		addTaskFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 687,462 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~addTaskFrame();

};

///////////////////////////////////////////////////////////////////////////////
/// Class viewTaskFrame
///////////////////////////////////////////////////////////////////////////////
class viewTaskFrame : public wxFrame
{
	private:

	protected:
		wxStaticText* taskStatusTitleText;
		wxStaticText* taskStatusPlaceholderText;
		wxStaticText* roomTitleText;
		wxListBox* roomTaskListBox;
		wxStaticText* robotTitleText;
		wxListBox* robotTaskListBox;

	public:

		viewTaskFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~viewTaskFrame();

};

