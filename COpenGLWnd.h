// COpenGLWnd.h : interface of the COpenGLWnd class
//


#pragma once

#include <GL/gl.h>
#include <GL/glu.h>

// COpenGLWnd window

class COpenGLWnd : public CWnd
{
// Data members
protected:
	HGLRC glHrc;		// resource context
	HDC   glHdc;		// device context
	unsigned int fontDisplayListStart;

// Construction
public:
	COpenGLWnd();
	virtual ~COpenGLWnd();

// Implementation
private:
	void CreateGL();	// setup  GL context
	void DeleteGL();	// delete GL context

// Attributes
public:
	int   Width()  const;	// window client width  (pixels)
	int   Height() const;	// window client height (pixels)
	float Aspect() const;	// window client aspect ratio (w/h)

// Operations
public:
	virtual void GLSetup();			// override this to do your OpenGL one-time setup
	virtual void GLRender();		// override this to modify OpenGL rendering loop (per frame)
	virtual void GLResize(int,int);	// override this handle resize of OpenGL viewport

	void GLSwapBuffers();
	bool GLMakeCurrent(bool Current=true);
	void GLDrawText(const char *str);

// Overrides
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	// Generated message map functions
protected:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
};

