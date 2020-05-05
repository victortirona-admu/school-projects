//---------------------------------------------------------------------------
//
// Name:        parkingApp.cpp
// Author:      Moshe Adique, Aaron Mandap, Victor Tirona
// Created:     08/10/2019 11:55:44 PM
// Description: 
//
//---------------------------------------------------------------------------

#include "parkingApp.h"
#include "parkingFrm.h"

IMPLEMENT_APP(parkingFrmApp)

bool parkingFrmApp::OnInit()
{
    parkingFrm* frame = new parkingFrm(NULL);
    SetTopWindow(frame);
    frame->Show();
    return true;
}
 
int parkingFrmApp::OnExit()
{
	return 0;
}
