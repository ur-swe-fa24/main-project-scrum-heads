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
#include <wx/textctrl.h>
#include <wx/stattext.h>
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
		wxButton* feButton;
		wxTextCtrl* feTextControl;
		wxButton* feRefreshButton;
		wxButton* addRobotButton;

		// Virtual event handlers, override them in your derived class
		virtual void OnFEButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnFERefreshButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAddRobotButtonClick( wxCommandEvent& event ) { event.Skip(); }


	public:

		feBaseFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~feBaseFrame();

};

///////////////////////////////////////////////////////////////////////////////
/// Class bmBaseFrame
///////////////////////////////////////////////////////////////////////////////
class bmBaseFrame : public wxFrame
{
	private:

	protected:
		wxButton* bmButton;

		// Virtual event handlers, override them in your derived class
		virtual void OnBMButtonClick( wxCommandEvent& event ) { event.Skip(); }


	public:

		bmBaseFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~bmBaseFrame();

};

///////////////////////////////////////////////////////////////////////////////
/// Class bsBaseFrame
///////////////////////////////////////////////////////////////////////////////
class bsBaseFrame : public wxFrame
{
	private:

	protected:
		wxButton* bsButton;

		// Virtual event handlers, override them in your derived class
		virtual void OnBSButtonClick( wxCommandEvent& event ) { event.Skip(); }


	public:

		bsBaseFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~bsBaseFrame();

};

///////////////////////////////////////////////////////////////////////////////
/// Class smBaseFrame
///////////////////////////////////////////////////////////////////////////////
class smBaseFrame : public wxFrame
{
	private:

	protected:
		wxButton* smButton;

		// Virtual event handlers, override them in your derived class
		virtual void OnSMButtonClick( wxCommandEvent& event ) { event.Skip(); }


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

