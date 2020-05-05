///-----------------------------------------------------------------
///
/// @file      parkingFrm.h
/// @author    Moshe Adique, Aaron Mandap, Victor Tirona
/// Created:   08/10/2019 11:55:44 PM
/// @section   DESCRIPTION
///            parkingFrm class declaration
///
///------------------------------------------------------------------

#ifndef __PARKINGFRM_H__
#define __PARKINGFRM_H__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include <wx/frame.h>
#else
	#include <wx/wxprec.h>
#endif

//Do not add custom headers between 
//Header Include Start and Header Include End.
//wxDev-C++ designer will remove them. Add custom headers after the block.
////Header Include Start
#include <wx/msgdlg.h>
#include <wx/filedlg.h>
#include <wx/textctrl.h>
#include <wx/statbmp.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/button.h>
////Header Include End

////Dialog Style Start
#undef parkingFrm_STYLE
#define parkingFrm_STYLE wxCAPTION | wxSYSTEM_MENU | wxMINIMIZE_BOX | wxCLOSE_BOX
////Dialog Style End

class parkingFrm : public wxFrame
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		parkingFrm(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("parking"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = parkingFrm_STYLE);
		virtual ~parkingFrm();
		void WxButton1Click(wxCommandEvent& event);
		void edt_browseBufferReset(wxRichTextEvent& event);
		void parkingFrmActivate(wxActivateEvent& event);
		void WxButton2Click(wxCommandEvent& event);
		void WxButton4Click(wxCommandEvent& event);
		void WxButton3Click(wxCommandEvent& event);
		void WxButton5Click(wxCommandEvent& event);
		void WxButton6Click(wxCommandEvent& event);
		void WxButton7Click(wxCommandEvent& event);
		void WxButton8Click(wxCommandEvent& event);
		void outputTextBufferReset(wxRichTextEvent& event);
		void WxButton5Click0(wxCommandEvent& event);
		void WxEdit1Updated(wxCommandEvent& event);
		void WxRichTextCtrl1BufferReset(wxRichTextEvent& event);
		void WxButton6Click0(wxCommandEvent& event);

		
	private:
		//Do not add custom control declarations between
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxMessageDialog *WxMessageDialog1;
		wxFileDialog *dlg_browse;
		wxButton *WxButton6;
		wxTextCtrl *WxEdit1;
		wxButton *WxButton2;
		wxStaticBitmap *WxStaticBitmap1;
		wxStaticBitmap *BmpOutput;
		wxStaticBitmap *BmpInput;
		wxRichTextCtrl *edt_browse;
		wxButton *WxButton1;
		////GUI Control Declaration End
		wxImage input;
        wxImage output;
        wxImage refImg;
        wxImage inpImg;

		
	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
		enum
		{
			////GUI Enum Control ID Start
			ID_WXBUTTON6 = 1015,
			ID_WXEDIT1 = 1014,
			ID_WXBUTTON2 = 1006,
			ID_WXSTATICBITMAP1 = 1005,
			ID_BMPOUTPUT = 1004,
			ID_BMPINPUT = 1003,
			ID_EDT_BROWSE = 1002,
			ID_WXBUTTON1 = 1001,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
		
	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
};

#endif
