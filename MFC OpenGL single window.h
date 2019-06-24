// MFC OpenGL single window.h : main header file for the MFC OpenGL single window application
//
#pragma once

#include "resource.h"       // main symbols

// CMFCOpenGLsinglewindowApp:

class CMFCOpenGLsinglewindowApp : public CWinApp
{
public:
	CMFCOpenGLsinglewindowApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
public:
	DECLARE_MESSAGE_MAP()
};

extern CMFCOpenGLsinglewindowApp theApp;