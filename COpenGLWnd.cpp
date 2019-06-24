// COpenGLWnd.cpp : implementation of the COpenGLWnd class
//

#include "stdafx.h"
#include "MFC OpenGL single window.h"
#include "COpenGLWnd.h"

#pragma comment (lib, "opengl32")
#pragma comment (lib, "glu32")


// COpenGLWnd

COpenGLWnd::COpenGLWnd()
{
	glHrc = NULL;
	glHdc = NULL;
	fontDisplayListStart = 0;
}

COpenGLWnd::~COpenGLWnd()
{
}


//---- CreateGL ---------------------------------------------------------------

void COpenGLWnd::CreateGL()
{
	// Delete any existing context first
    DeleteGL();

    // Get hold of device context for window
    glHdc = GetDC()->m_hDC;

	// Setup Pixel Format Descriptor
	PIXELFORMATDESCRIPTOR pfd;
    memset(&pfd,0,sizeof(pfd));		// zero fill
    pfd.nSize      = sizeof(pfd);	// structure size
    pfd.nVersion   = 1;
    pfd.dwFlags    = PFD_DRAW_TO_WINDOW |
					 PFD_SUPPORT_OPENGL |
					 PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 32;			// nice fat depth buffer please
    pfd.iLayerType = PFD_MAIN_PLANE;

	// Choose best pixel format and set it up
    int glPixelFormat = ChoosePixelFormat(glHdc, &pfd);
    SetPixelFormat(glHdc, glPixelFormat, &pfd);

	// Create OpenGL context
    glHrc = wglCreateContext(glHdc);
    if (glHrc == NULL) {
		MessageBox("Could not create GL context");
        DeleteGL();
        return;
    }

    // Try making our context current
	if (!GLMakeCurrent()) {
        MessageBox("Could not make GL context current");
        DeleteGL();
        return;
    }

	// call users setup code: note that GL context is current
	GLSetup();

	// make the system font the device context's selected font 
	SelectObject (glHdc, GetStockObject (SYSTEM_FONT)); 
	 
	// create the bitmap display lists 
	// making images of glyphs 0 thru 255 
	// the display list numbering start is returned by opengl
	fontDisplayListStart = glGenLists(256);
	wglUseFontBitmaps (glHdc, 0, 255, fontDisplayListStart); 
 
	GLMakeCurrent(false);
}

//---- DeleteGL ---------------------------------------------------------------

void COpenGLWnd::DeleteGL()
{
	if (glHrc) {
		GLMakeCurrent(false);		// Release before we destroy
		wglDeleteContext(glHrc);    // DeStROy tHe ConTeXT!
		glHrc = NULL;               // (glHrc == NULL) indicates no GL context
	}
}

//-----------------------------------------------------------------------------

BOOL COpenGLWnd::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW),
		NULL,	// null background brush to prevent flicker on window erase
		NULL);
	return TRUE;
}

//-----------------------------------------------------------------------------

BEGIN_MESSAGE_MAP(COpenGLWnd, CWnd)
	ON_WM_DESTROY()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COpenGLWnd message handlers

//-----------------------------------------------------------------------------


void COpenGLWnd::OnDestroy() 
{
	// Delete OpenGL drawing context
	DeleteGL();

	CWnd::OnDestroy();
}

//-----------------------------------------------------------------------------

int COpenGLWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Create OpenGL drawing context
	CreateGL();
	return 0;
}

//-----------------------------------------------------------------------------

void COpenGLWnd::OnPaint() 
{
	CPaintDC dc(this);
	if (GLMakeCurrent()) {
		GLRender();
		Invalidate(false);
		GLMakeCurrent(false);
	}
}

//-----------------------------------------------------------------------------

void COpenGLWnd::OnSize(UINT nType, int cx, int cy)
{
	if (GLMakeCurrent()) {
		GLResize(cx,cy);
		GLMakeCurrent(false);
	}
}

//-----------------------------------------------------------------------------

// window client width (pixels)
int COpenGLWnd::Width() const {
	CRect rect;
	GetClientRect(&rect);
	return rect.Width();
}

// window client height (pixels)
int COpenGLWnd::Height() const {
	CRect rect;
	GetClientRect(&rect);
	return rect.Height();
}

// window client aspect ratio (w/h)
float COpenGLWnd::Aspect() const {
	int h=Height();
	return (float)Width() / (float)(h?h:1);
}

//---- GLDrawText -------------------------------------------------------------

void COpenGLWnd::GLDrawText(const char *str) {
	// indicate start of glyph display lists 
	glListBase (fontDisplayListStart); 
	// now draw the characters in a string 
	glCallLists ((GLsizei)strlen(str), GL_UNSIGNED_BYTE, str); 
}

//---- GLSetup ----------------------------------------------------------------

void COpenGLWnd::GLSetup() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-100.0, 100.0, -100.0, 100.0, -1.0, 1.0);
	//glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	//glOrtho(0.0, Width(), 0.0,-Height() , -1.0, 1.0);
	glFrustum(-1.0,1.0,-0.75,0.75,1.0,1000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glViewport(0, 0, Width(), Height());
}

//---- GLRender ---------------------------------------------------------------

void COpenGLWnd::GLRender() {
	// default implementation just clears window
	glDrawBuffer (GL_BACK);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// default implementation do nothing
	GLSwapBuffers();
}

//---- GLResize ---------------------------------------------------------------

void COpenGLWnd::GLResize(int w, int h) {
	// default implementation resizes OpenGL viewport
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-100.0, 100.0, -100.0, 100.0, -1.0, 1.0);
	//glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
//	glOrtho(0.0, w, 0.0,-h , -1.0, 1.0);
	glFrustum(-1.0,1.0,-0.75,0.75,1.0,1000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport(0,0,w,h);

	GLRender();
}

//---- GLSwapBuffers ----------------------------------------------------------

void COpenGLWnd::GLSwapBuffers()
{
	SwapBuffers(glHdc);
}

//---- GLMakeCurrent ----------------------------------------------------------

bool COpenGLWnd::GLMakeCurrent(bool Current)
{
	if (Current)
		return (glHrc!=NULL) && wglMakeCurrent(glHdc, glHrc);
	else {
		wglMakeCurrent(NULL, NULL);
		return true;
	}
	
}
