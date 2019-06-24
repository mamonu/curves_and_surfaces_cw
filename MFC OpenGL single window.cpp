// MFC OpenGL single window.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MFC OpenGL single window.h"
#include "MainFrm.h"

// CMFCOpenGLsinglewindowApp
BEGIN_MESSAGE_MAP(CMFCOpenGLsinglewindowApp, CWinApp)
END_MESSAGE_MAP()

// CMFCOpenGLsinglewindowApp construction
CMFCOpenGLsinglewindowApp::CMFCOpenGLsinglewindowApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CMFCOpenGLsinglewindowApp object
CMFCOpenGLsinglewindowApp theApp;

// CMFCOpenGLsinglewindowApp initialization
BOOL CMFCOpenGLsinglewindowApp::InitInstance()
{
	CWinApp::InitInstance();

	// To create the main window, this code creates a new frame window
	// object and then sets it as the application's main window object
	CMainFrame* pFrame = new CMainFrame;
	m_pMainWnd = pFrame;
	// create and load the frame with its resources
	pFrame->LoadFrame(IDR_MENU1, WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,NULL);
	// The one and only window has been initialized, so show and update it
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	return TRUE;
}