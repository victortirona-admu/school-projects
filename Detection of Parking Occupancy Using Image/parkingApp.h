//---------------------------------------------------------------------------
//
// Name:        parkingApp.h
// Author:      Moshe Adique, Aaron Mandap, Victor Tirona
// Created:     08/10/2019 11:55:44 PM
// Description: 
//
//---------------------------------------------------------------------------

#ifndef __PARKINGFRMApp_h__
#define __PARKINGFRMApp_h__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#else
	#include <wx/wxprec.h>
#endif

class parkingFrmApp : public wxApp
{
	public:
		bool OnInit();
		int OnExit();
};

#endif
