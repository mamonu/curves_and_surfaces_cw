// CMyOpenGLWnd.cpp : implementation of the CMyOpenGLWnd class
//

#include "stdafx.h"
#include "CMyOpenGLWnd.h"
#include "CBezier.h"
#include "CQuadraticBSpline.h"
#include "CCubicBSpline.h"
#include "CNurbs.h"
#include "CHermite.h"
#include "CBezierSurface.h"
#include "CBSplineSurface.h"
#include "CNurbsSurface.h"
#include "CRevolutionSurface.h"
#include "resource.h"
#include <strstream>
using namespace std;

// CMyOpenGLWnd


CMyOpenGLWnd::CMyOpenGLWnd()
{
	m_pcurve = NULL;
	m_string = "Curves and Surfaces";
	m_pcamera = new Orthocamera;
	m_pcamera2 = new Perspectivecamera();
	m_iselectdisplay = XY;
	m_ivewport = XY;
	m_bfourviewports = true;
	m_bperspective = false;
}	

CMyOpenGLWnd::~CMyOpenGLWnd()
{
	if(m_pcurve)
		delete m_pcurve;
	delete m_pcamera;
	delete m_pcamera2;
}

//-----------------------------------------------------------------------------
// CMyOpenGLWnd GLSetup

void CMyOpenGLWnd::GLSetup() {
	
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glEnable(GL_DEPTH_TEST);
	COpenGLWnd::GLSetup();
	m_pcamera->SetClippingPlane(-1.0,1.0,-1.0,1.0,0.0,0.0);
	m_pcamera2->SetClippingPlane(-1.0,1.0,-0.75,0.75,1.0,50.0);
	m_pcamera2->SetCamera(Vector3d(0.0,2.0,1.0),Vector3d(0.0,0.0,0.0),Vector3d(0.0,1.0,0.0));
	m_pcamera2->Pitch(-60.0);
	m_pcamera2->Yaw(30.0);
	m_pcamera->SetCamera(Vector3d(0.0,0.0,1.0),Vector3d(0.0,0.0,0.0),Vector3d(0.0,1.0,0.0));//y-up x-right
	m_texture[0].LoadTextureData("front.bmp");
	m_texture[1].LoadTextureData("top.bmp");
	m_texture[2].LoadTextureData("side.bmp");
}

//-----------------------------------------------------------------------------
// CMyOpenGLWnd GLRender

void CMyOpenGLWnd::GLRender() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	DisplayText();
	if (m_bfourviewports)
	{
		//top left
		m_pcamera->SetCamera(Vector3d(0.0,0.0,1.0),Vector3d(0.0,0.0,0.0),Vector3d(0.0,1.0,0.0));//y-up x-right
		m_pcamera->SetViewport(0,Height()/2,Width()/2,Height()/2);
		m_pcamera->ProjectionMode();
		m_pcamera->StartCamera();
		m_ivewport = XY;
		Draw();
		if (m_iselectdisplay == XY)
		{
			glGetDoublev(GL_MODELVIEW_MATRIX,m_dmodel);
			glGetDoublev(GL_PROJECTION_MATRIX,m_dproj);
			glGetIntegerv(GL_VIEWPORT,m_ivp);
			DrawSelectionXY();
		}
		DrawFontXY();
		DrawGridXY(Width(),Height());
		


		//bottom left
		m_pcamera->SetCamera(Vector3d(0.0,1.0,0.0),Vector3d(0.0,0.0,0.0),Vector3d(0.0,-1.0,-1.0));//x-right z-up
		m_pcamera->SetViewport(0,0,Width()/2,Height()/2);
		m_pcamera->ProjectionMode();
		m_pcamera->StartCamera();
		m_ivewport = ZX;
		if (m_iselectdisplay == ZX)
		{
			glGetDoublev(GL_MODELVIEW_MATRIX,m_dmodel);
			glGetDoublev(GL_PROJECTION_MATRIX,m_dproj);
			glGetIntegerv(GL_VIEWPORT,m_ivp);
			DrawSelectionZX();
		}
		Draw(); 
		DrawFontZX();
		DrawGridZX(Width(),Height());
		
		

		//top-right
		m_pcamera->SetCamera(Vector3d(1.0,0.0,0.0),Vector3d(0.0,0.0,0.0),Vector3d(0.0,1.0,0.0));//y-up z-right
		m_pcamera->SetViewport(Width()/2,Height()/2,Width()/2,Height()/2);
		m_pcamera->ProjectionMode();
		m_pcamera->StartCamera();
		m_ivewport = YZ;
		if (m_iselectdisplay == YZ)
		{
			glGetDoublev(GL_MODELVIEW_MATRIX,m_dmodel);
			glGetDoublev(GL_PROJECTION_MATRIX,m_dproj);
			glGetIntegerv(GL_VIEWPORT,m_ivp);
			DrawSelectionYZ();
		}
		Draw();    
		DrawFontYZ();
		DrawGridYZ(Width(),Height());


		//bottom right perspective
		m_pcamera2->SetViewport(Width()/2,0,Width()/2,Height()/2);
		m_pcamera2->ProjectionMode();
		m_pcamera2->StartCamera();

		m_ivewport = PERSPECTIVE;
		Draw();    
		DrawGridPerspective(Width()/2,Height()/2);

	}
	else
	{
		if (!m_bperspective)
		{
			m_pcamera->SetViewport(0,0,Width(),Height());
			m_pcamera->ProjectionMode();
			m_pcamera->StartCamera();
		}
		else 
		{
			m_pcamera2->SetViewport(0,0,Width(),Height());
			m_pcamera2->ProjectionMode();
			m_pcamera2->StartCamera();
		}
		glGetDoublev(GL_MODELVIEW_MATRIX,m_dmodel);
		glGetDoublev(GL_PROJECTION_MATRIX,m_dproj);
		glGetIntegerv(GL_VIEWPORT,m_ivp);
		
		Draw();
		if (m_ivewport == XY)
		{
			DrawFontXY();
			DrawGridXY(Width(),Height());
		}
		else if (m_ivewport == YZ)
		{
			DrawFontYZ();
			DrawGridYZ(Width(),Height());
		}
		else if (m_ivewport == ZX)
		{
			DrawFontZX();
			DrawGridZX(Width(),Height());
		}
		else 
			DrawGridPerspective(Width(),Height());
	}
	
	glFlush();
	GLSwapBuffers();

}

void CMyOpenGLWnd::Draw()
{
	glPushMatrix();
	if (m_pcurve)
	{
		m_pcurve->Draw();
	}
	
	glPopMatrix();
}

void CMyOpenGLWnd::DrawGridPerspective(const int t_iwidth,const int t_iheight)
{
    DrawGridZX(t_iwidth,t_iheight);
}

void CMyOpenGLWnd::DrawFontXY()
{
	glEnable(GL_TEXTURE_2D);
	glColor3d(1.0,1.0,1.0);
	m_texture[0].ApplyTexture();
	glBegin(GL_QUADS);
	glTexCoord2d(0.0,0.0); glVertex3d(-1.0,-1.0,0.0);
	glTexCoord2d(0.0,1.0); glVertex3d(-1.0,-0.7,0.0);
	glTexCoord2d(1.0,1.0); glVertex3d(-0.7,-0.7,0.0);
	glTexCoord2d(1.0,0.0); glVertex3d(-0.7,-1.0,0.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void CMyOpenGLWnd::DrawFontZX()
{
	glEnable(GL_TEXTURE_2D);
	glColor3d(1.0,1.0,1.0);
	m_texture[1].ApplyTexture();
	glBegin(GL_QUADS);
	glTexCoord2d(0.0,0.0); glVertex3d(-1.0,0.0,1.0);
	glTexCoord2d(0.0,1.0); glVertex3d(-1.0,0.0,0.7);
	glTexCoord2d(1.0,1.0); glVertex3d(-0.7,0.0,0.7);
	glTexCoord2d(1.0,0.0); glVertex3d(-0.7,0.0,1.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}


void CMyOpenGLWnd::DrawFontYZ()
{
	glEnable(GL_TEXTURE_2D);
	glColor3d(1.0,1.0,1.0);
	m_texture[2].ApplyTexture();
	glBegin(GL_QUADS);
	glTexCoord2d(1.0,0.0); glVertex3d(0.0,-1.0,-1.0);
	glTexCoord2d(0.0,0.0); glVertex3d(0.0,-1.0,-0.7);
	glTexCoord2d(0.0,1.0); glVertex3d(0.0,-0.7,-0.7);
	glTexCoord2d(1.0,1.0); glVertex3d(0.0,-0.7,-1.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void CMyOpenGLWnd::DrawGridXY(const int t_iwidth,const int t_iheight)
{
	glColor3d(1.0,0.0,0.0);
	glLineWidth(2.0);
	glBegin(GL_LINES);
		glVertex3d(-1.0,0.0,0.0);
		glVertex3d(1.0,0.0,0.0);

		glVertex3d(0.0,-1.0,0.0);
		glVertex3d(0.0,1.0,0.0);
	glEnd();
	glLineWidth(1.0);

	int t_iw = t_iwidth /2;
	int t_ih = t_iheight/2;

	glColor3d(0.35,0.0,0.0);
	glBegin(GL_LINES);
	for (double i=-1.0; i<1.0; i+=10.0/(t_ih))
	{
		glVertex3d(-1.0,i,0.0);
		glVertex3d(1.0,i,0.0);
	}
	glEnd();

	glBegin(GL_LINES);
	for (double i=-1.0; i<1.0; i+=10.0/(t_iw))
	{
		glVertex3d(i,-1.0,0.0);
		glVertex3d(i,1.0,0.0);
	}
	glEnd();
}

void CMyOpenGLWnd::DrawGridYZ(const int t_iwidth,const int t_iheight)
{
	glColor3d(1.0,0.0,0.0);
	glLineWidth(2.0);
	glBegin(GL_LINES);
		glVertex3d(0.0,-1.0,0.0);
		glVertex3d(0.0,1.0,0.0);

		glVertex3d(0.0,0.0,-1.0);
		glVertex3d(0.0,0.0,1.0);
	glEnd();
	glLineWidth(1.0);

	int t_iw = t_iwidth /2;
	int t_ih = t_iheight/2;

	glColor3d(0.35,0.0,0.0);
	glBegin(GL_LINES);
	for (double i=-1.0; i<1.0; i+=10.0/(t_iw))
	{
		glVertex3d(0.0,-1.0,i);
		glVertex3d(0.0,1.0,i);
	}
	glEnd();

	glBegin(GL_LINES);
	for (double i=-1.0; i<1.0; i+=10.0/(t_ih))
	{
		glVertex3d(0.0,i,-1.0);
		glVertex3d(0.0,i,1.0);
	}
	glEnd();
}


void CMyOpenGLWnd::DrawGridZX(const int t_iwidth,const int t_iheight)
{
	glColor3d(1.0,0.0,0.0);
	glLineWidth(2.0);
	glBegin(GL_LINES);
		glVertex3d(-1.0,0.0,0.0);
		glVertex3d(1.0,0.0,0.0);

		glVertex3d(0.0,0.0,-1.0);
		glVertex3d(0.0,0.0,1.0);
	glEnd();
	glLineWidth(1.0);

	int t_iw = t_iwidth/2;
	int t_ih = t_iheight/2;

	glColor3d(0.35,0.0,0.0);
	glBegin(GL_LINES);
	for (double i=-1.0; i<1.0; i+=10.0/(t_ih))
	{
		glVertex3d(-1.0,0.0,i);
		glVertex3d(1.0,0.0,i);
	}
	glEnd();

	glBegin(GL_LINES);
	for (double i=-1.0; i<1.0; i+=10.0/(t_iw))
	{
		glVertex3d(i,0.0,-1.0);
		glVertex3d(i,0.0,1.0);
	}
	glEnd();
}

void CMyOpenGLWnd::DisplayText()
{
	char buffer [80];
	ostrstream sout (buffer, sizeof(buffer));
	sout<<m_string<<ends;
	if (GetParentFrame())
			GetParentFrame()->SetWindowText((buffer));

}

void CMyOpenGLWnd::ConvertToWorld(Vector3d & t_point)
{
	GLdouble t_dx,t_dy,t_dz;
	gluUnProject(t_point.x,t_point.y,t_point.z,m_dmodel,m_dproj,m_ivp,&t_dx,&t_dy,&t_dz);
	t_point.x = t_dx;
	t_point.y = t_dy;
	t_point.z = t_dz;
	return ;
}

void CMyOpenGLWnd::DrawSelectionXY()
{
	glColor3d(1.0,1.0,1.0);
	glLineWidth(5.0);
	glBegin(GL_LINE_STRIP);
		glVertex3d(-1.0,1.0,0.0);
		glVertex3d(1.0,1.0,0.0);
		glVertex3d(1.0,-1.0,0.0);
		glVertex3d(-1.0,-1.0,0.0);
		glVertex3d(-1.0,1.0,0.0);
	glEnd();
	glLineWidth(1.0);
}

void CMyOpenGLWnd::DrawSelectionYZ()
{
	glColor3d(1.0,1.0,1.0);
	glLineWidth(5.0);
	glBegin(GL_LINE_STRIP);
		glVertex3d(0.0,-1.0,1.0);
		glVertex3d(0.0,1.0,1.0);
		glVertex3d(0.0,1.0,-1.0);
		glVertex3d(0.0,-1.0,-1.0);
		glVertex3d(0.0,-1.0,1.0);
	glEnd();
	glLineWidth(1.0);
}

void CMyOpenGLWnd::DrawSelectionZX()
{
	glColor3d(1.0,1.0,1.0);
	glLineWidth(5.0);
	glBegin(GL_LINE_STRIP);
		glVertex3d(-1.0,0.0,1.0);
		glVertex3d(1.0,0.0,1.0);
		glVertex3d(1.0,0.0,-1.0);
		glVertex3d(-1.0,0.0,-1.0);
		glVertex3d(-1.0,0.0,1.0);
	glEnd();
	glLineWidth(1.0);
}


//-----------------------------------------------------------------------------
// CMyOpenGLWnd message handlers

BEGIN_MESSAGE_MAP(CMyOpenGLWnd, COpenGLWnd)
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_UPDATE_COMMAND_UI(ID_CURVE_ADDPOINT, OnUpdateCurveAddPoint)
	ON_UPDATE_COMMAND_UI(ID_CURVE_MODIFY, OnUpdateCurveModifyPoint)
	ON_UPDATE_COMMAND_UI(ID_CURVE_DELETE, OnUpdateCurveDeletePoint)
	ON_UPDATE_COMMAND_UI(ID_POINTS_INSERT, OnUpdatePointsInsertPoint)
	ON_COMMAND(ID_SELECT_BEZIERCURVE, OnSelectBeziercurve)
	ON_COMMAND(ID_CURVE_ADDPOINT, OnCurveAddpoint)
	ON_COMMAND(ID_CURVE_MODIFY, OnCurveModify)
	ON_COMMAND(ID_CURVE_DELETE, OnCurveDelete)
	ON_COMMAND(ID_SELECT_QUADRATICBSPLINECURVE, OnSelectQuadraticBSplinecurve)
	ON_COMMAND(ID_SELECT_CUBICBSPLINECURVE, OnSelectCubicBSplinecurve)
	ON_UPDATE_COMMAND_UI(ID_POLYGONDISPLAY_ON, OnUpdatePolygondisplayOnOff)
	ON_UPDATE_COMMAND_UI(ID_POLYGONDISPLAY_OFF, OnUpdatePolygondisplayOnOff)
	ON_COMMAND(ID_POLYGONDISPLAY_ON, SetPolygondisplayOn)
	ON_COMMAND(ID_POLYGONDISPLAY_OFF, SetPolygondisplayOff)
	ON_COMMAND(ID_SELECT_HERMITECURVE, OnSelectHermitecurve)
	ON_COMMAND(ID_POINTS_INSERT, OnPointsInsert)
	ON_COMMAND(ID_DISPLAY_CLEAR, OnDisplayClear)
	ON_UPDATE_COMMAND_UI(ID_DISPLAY_CLEAR, OnUpdateDisplayClear)
	ON_COMMAND(ID_SELECTCURVE_NURBS, OnSelectcurveNurbs)
	ON_UPDATE_COMMAND_UI(ID_POINTS_INCREASEWEIGHT, OnUpdatePointsWeight)
	ON_UPDATE_COMMAND_UI(ID_POINTS_DECREASEWEIGHT, OnUpdatePointsWeight)
	ON_COMMAND(ID_POINTS_INCREASEWEIGHT, OnPointsIncreaseweight)
	ON_COMMAND(ID_POINTS_DECREASEWEIGHT, OnPointsDecreaseweight)
	ON_COMMAND(ID_SELECTCURVE_BEZIERSURFACE_3, OnSelectcurveBeziersurface3)
	ON_COMMAND(ID_SELECTCURVE_BEZIERSURFACE4, OnSelectcurveBeziersurface4)
	ON_COMMAND(ID_SELECT_CUBICBSPLINESURFACE, OnSelectCubicbsplinesurface)
	ON_COMMAND(ID_SELECT_QUADRATICBSPLINESURFACE, OnSelectQuadraticbsplinesurface)
	ON_COMMAND(ID_SELECT_NURBSSURFACE, OnSelectNurbssurface)
	ON_COMMAND(ID_VIEWPORT_FRONT, OnViewportFront)
	ON_COMMAND(ID_VIEWPORT_TOP, OnViewportTop)
	ON_COMMAND(ID_VIEWPORT_SIDE, OnViewportSide)
	ON_COMMAND(ID_VIEWPORT_PERSPECTIVE, OnViewportPerspective)
	ON_COMMAND(ID_VIEWPORT_ALL, OnViewportAll)
	ON_COMMAND(ID_SELECT_REVOLUTIONSURFACE, OnSelectRevolutionsurface)
END_MESSAGE_MAP()

void CMyOpenGLWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (m_pcurve)
	{
		switch(nChar)
		{
		case '1': m_pcamera2->Move(0.1); break;
		case '2': m_pcamera2->Move(-0.1); break;
		case '3': m_pcamera2->Yaw(1.0); break;
		case '4': m_pcamera2->Yaw(-1.0); break;
		case '5':  m_pcamera2->Pitch(1.0); break;
		case '6':  m_pcamera2->Pitch(-1.0); break;
		}
	}
}

void CMyOpenGLWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (GLMakeCurrent())
	{
		if (m_pcurve)
		{
			if (m_bfourviewports)
			{
				int t_ihalfwidth = Width()/2 ;
				int t_ihalfheight = Height()/2;
				if (((point.x < t_ihalfwidth) && (point.y < t_ihalfheight) && m_iselectdisplay == XY )||
					((point.x < t_ihalfwidth) && (point.y > t_ihalfheight) && m_iselectdisplay == ZX )||
					((point.x > t_ihalfwidth) && (point.y < t_ihalfheight) && m_iselectdisplay == YZ ))
				{
					Vector3d t_point = Vector3d(point.x,Height()-point.y,0.0);
					ConvertToWorld(t_point);
					m_pcurve->Update(t_point);
				}
			}
			else if (!m_bperspective)
			{
				Vector3d t_point = Vector3d(point.x,Height()-point.y,0.0);
				ConvertToWorld(t_point);
				m_pcurve->Update(t_point);
			}
		}
			//m_pcurve->Update(Vector3d(point.x,0.0,point.y));
		GLMakeCurrent(false);
	}
	
}

void CMyOpenGLWnd::OnRButtonDown(UINT nFlags, CPoint point)
{
	int t_ihalfwidth = Width()/2 ;
	int t_ihalfheight = Height()/2;
	if ((point.x < t_ihalfwidth)&&(point.y < t_ihalfheight))
		m_iselectdisplay = XY;
	else if ((point.x < t_ihalfwidth)&&(point.y > t_ihalfheight))
		m_iselectdisplay = ZX;
	else if ((point.x > t_ihalfwidth)&&(point.y < t_ihalfheight))
		m_iselectdisplay = YZ;

}

void CMyOpenGLWnd::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	
}

void CMyOpenGLWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	if (GLMakeCurrent())
	{
		if (m_pcurve)
		{
			if (nFlags == VK_LBUTTON && m_pcurve->IsSelected())
            {
				if (m_bfourviewports)
				{
					int t_ihalfwidth = Width()/2 ;
					int t_ihalfheight = Height()/2;
					if (((point.x < t_ihalfwidth) && (point.y < t_ihalfheight) && m_iselectdisplay == XY )||
						((point.x < t_ihalfwidth) && (point.y > t_ihalfheight) && m_iselectdisplay == ZX )||
						((point.x > t_ihalfwidth) && (point.y < t_ihalfheight) && m_iselectdisplay == YZ ))
					{
						Vector3d t_point = Vector3d(point.x,Height()-point.y,0.0);
						ConvertToWorld(t_point);
						m_pcurve->Update(t_point);
					}					
				}
				else if (!m_bperspective)
				{
					Vector3d t_point = Vector3d(point.x,Height()-point.y,0.0);
					ConvertToWorld(t_point);
					m_pcurve->Update(t_point);
				
				}
			}
		}
		GLMakeCurrent(false);
	}
}

void CMyOpenGLWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_pcurve)
		m_pcurve->UnselectPoint();
}
void CMyOpenGLWnd::OnUpdateCurveAddPoint(CCmdUI *pCmdUI)
{
	if(m_pcurve)
		pCmdUI->Enable(true);
	else
		pCmdUI->Enable(false);
}

void CMyOpenGLWnd::OnUpdateCurveModifyPoint(CCmdUI *pCmdUI)
{
	if(m_pcurve)
		pCmdUI->Enable(true);
	else
		pCmdUI->Enable(false);
}

void CMyOpenGLWnd::OnUpdateCurveDeletePoint(CCmdUI *pCmdUI)
{
	if(m_pcurve)
		pCmdUI->Enable(true);
	else
		pCmdUI->Enable(false);
}

void CMyOpenGLWnd::OnUpdatePointsInsertPoint(CCmdUI *pCmdUI)
{
	if(m_pcurve)
		pCmdUI->Enable(m_pcurve->CanInsertPoint());
	else
		pCmdUI->Enable(false);
}

void CMyOpenGLWnd::OnSelectBeziercurve()
{
	if (m_pcurve)
		delete m_pcurve;
	m_pcurve = new CBezier(this);
	m_string = "Bezier Curve";

}

void CMyOpenGLWnd::OnCurveAddpoint()
{
	m_pcurve->SetMode(CCurve::ADDPOINT);
}

void CMyOpenGLWnd::OnCurveModify()
{
	m_pcurve->SetMode(CCurve::MODIFYPOINT);
}

void CMyOpenGLWnd::OnCurveDelete()
{
	m_pcurve->SetMode(CCurve::DELETEPOINT);
}

void CMyOpenGLWnd::OnPointsInsert()
{
	m_pcurve->SetMode(CCurve::INSERTPOINT);
}

void CMyOpenGLWnd::OnSelectQuadraticBSplinecurve()
{
	if (m_pcurve)
		delete m_pcurve;
	m_pcurve = new CQuadraticBSpline(this);
	m_string = "Quadratic BSpline Curve";
	
}

void CMyOpenGLWnd::OnSelectCubicBSplinecurve()
{
	if (m_pcurve)
		delete m_pcurve;
	m_pcurve = new CCubicBSpline(this);
	m_string = "Cubic BSpline Curve";
	
}

void CMyOpenGLWnd::OnUpdatePolygondisplayOnOff(CCmdUI *pCmdUI)
{
	if (m_pcurve)
		pCmdUI->Enable(m_pcurve->HasControlPolygon());
	else
		pCmdUI->Enable(false);
}

void CMyOpenGLWnd::SetPolygondisplayOn()
{
	m_pcurve->SetPolygonDisplay(true);
}

void CMyOpenGLWnd::SetPolygondisplayOff()
{
	m_pcurve->SetPolygonDisplay(false);
}

void CMyOpenGLWnd::OnSelectHermitecurve()
{
	if (m_pcurve)
		delete m_pcurve;
	m_pcurve = new CHermite(this);
	m_string = "Hermite Curve";
	
}



void CMyOpenGLWnd::OnDisplayClear()
{
	m_pcurve->Clear();
}

void CMyOpenGLWnd::OnUpdateDisplayClear(CCmdUI *pCmdUI)
{
	if(m_pcurve)
		pCmdUI->Enable(true);
	else
		pCmdUI->Enable(false);
}

void CMyOpenGLWnd::OnSelectcurveNurbs()
{
	if (m_pcurve)
		delete m_pcurve;
	m_pcurve = new CNurbs(this,3);
	m_string = "Nurbs Curve";
	
}

void CMyOpenGLWnd::OnUpdatePointsWeight(CCmdUI *pCmdUI)
{
	if(m_pcurve)
		pCmdUI->Enable(m_pcurve->CanChangeWeight());
	else
		pCmdUI->Enable(false);
}

void CMyOpenGLWnd::OnPointsIncreaseweight()
{
	m_pcurve->SetMode(CCurve::INCREASEWEIGHT);
}

void CMyOpenGLWnd::OnPointsDecreaseweight()
{
	m_pcurve->SetMode(CCurve::DECREASEWEIGHT);
}


void CMyOpenGLWnd::OnSelectcurveBeziersurface3()
{
	if (m_pcurve)
		delete m_pcurve;
	m_pcurve = new CBezierSurface(this,3);
	m_string = "Bezier Surface 3";
}

void CMyOpenGLWnd::OnSelectcurveBeziersurface4()
{
	if (m_pcurve)
		delete m_pcurve;
	m_pcurve = new CBezierSurface(this,4);
	m_string = "Bezier Surface 4";
}

void CMyOpenGLWnd::OnSelectCubicbsplinesurface()
{
	if (m_pcurve)
		delete m_pcurve;
	m_pcurve = new CBSplineSurface(this,4);
	m_string = "Cubic BSpline Surface";
}

void CMyOpenGLWnd::OnSelectQuadraticbsplinesurface()
{
	if (m_pcurve)
		delete m_pcurve;
	m_pcurve = new CBSplineSurface(this,3);
	m_string = "Quadratic BSpline Surface";
}

void CMyOpenGLWnd::OnSelectNurbssurface()
{
	if (m_pcurve)
		delete m_pcurve;
	m_pcurve = new CNurbsSurface(this,4);
	m_string = "Nurbs Surface";
}

void CMyOpenGLWnd::OnViewportFront()
{
	m_bfourviewports = false;
	m_bperspective = false;
	m_ivewport = XY;
	m_pcamera->SetCamera(Vector3d(0.0,0.0,1.0),Vector3d(0.0,0.0,0.0),Vector3d(0.0,1.0,0.0));//x-right y-up
}

void CMyOpenGLWnd::OnViewportTop()
{
	m_bfourviewports = false;
	m_bperspective = false;
	m_ivewport = ZX;
	m_pcamera->SetCamera(Vector3d(0.0,1.0,0.0),Vector3d(0.0,0.0,0.0),Vector3d(0.0,-1.0,-1.0));//x-right z-up
}

void CMyOpenGLWnd::OnViewportSide()
{
	m_bfourviewports = false;
	m_bperspective = false;
	m_ivewport = YZ;
	m_pcamera->SetCamera(Vector3d(1.0,0.0,0.0),Vector3d(0.0,0.0,0.0),Vector3d(0.0,1.0,0.0));//y-up z-right
}

void CMyOpenGLWnd::OnViewportPerspective()
{
	m_bfourviewports = false;
	m_bperspective = true;
	m_ivewport = PERSPECTIVE;
}

void CMyOpenGLWnd::OnViewportAll()
{
	m_bfourviewports = true;
	m_bperspective = false;
}

void CMyOpenGLWnd::OnSelectRevolutionsurface()
{
	if (m_pcurve)
		delete m_pcurve;
	m_pcurve = new CRevolutionSurface(this);
	m_string = "Revolution Surface";
}
