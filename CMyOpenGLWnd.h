// MFC OpenGL sampleView.h : interface of the CMFCOpenGLsampleView class
//

#pragma once
#include "CCurve.h"
#include <string>

using namespace std;

#include "COpenGLWnd.h"
#include "perspectivecamera.h"
#include "Orthocamera.h"
#include "textureloader.h"

//TODO: Move the const to static const within the class - then they inherit the class 
// scope and can be referenced elsewhere, if required

 


class CCurve;

class CMyOpenGLWnd : public COpenGLWnd
{
public:		
	CMyOpenGLWnd();
	virtual ~CMyOpenGLWnd(); //TODO: Remove virtual

// Data members
private:
	textureloader m_texture[3];
	CCurve *m_pcurve;
	string m_string;
	Perspectivecamera *m_pcamera2;
	Orthocamera *m_pcamera;
	int m_iselectdisplay;
	double m_dmodel[16];
	double m_dproj[16];
	int m_ivp[4];
	bool m_bfourviewports;
	int m_ivewport;
	bool m_bperspective;
// Overrides
public:
	static const int XY = 0;
	static const int YZ = 1;
	static const int ZX = 2;
	static const int PERSPECTIVE = 3;
	virtual void GLSetup();			// override this to do your OpenGL one-time setup
	virtual void GLRender();		// override this to modify OpenGL rendering loop (per frame)
	void DrawGridXY(const int t_iwidth,const int t_iheight);
	void DrawGridYZ(const int t_iwidth,const int t_iheight);
	void DrawGridZX(const int t_iwidth,const int t_iheight);
	void DrawSelectionXY();
	void DrawSelectionYZ();
	void DrawSelectionZX();
	void DrawFontXY();
	void DrawFontYZ();
	void DrawFontZX();
	void DrawGridPerspective(const int t_iwidth,const int t_iheight);
	void DisplayText();
	void Draw();
	void ConvertToWorld(Vector3d & t_point);
	int GetViewport() {	return m_ivewport;	}

// Generated message map functions
protected:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags,CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnUpdateCurveAddPoint(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCurveModifyPoint(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCurveDeletePoint(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePointsInsertPoint(CCmdUI *pCmdUI);
	afx_msg void OnSelectBeziercurve();
	afx_msg void OnCurveAddpoint();
	afx_msg void OnCurveModify();
	afx_msg void OnCurveDelete();
	afx_msg void OnSelectQuadraticBSplinecurve();
	afx_msg void OnSelectCubicBSplinecurve();
	afx_msg void OnUpdatePolygondisplayOnOff(CCmdUI *pCmdUI);
	afx_msg void SetPolygondisplayOn();
	
	afx_msg void SetPolygondisplayOff();
	afx_msg void OnSelectHermitecurve();
	afx_msg void OnPointsInsert();
	afx_msg void OnDisplayClear();
	afx_msg void OnUpdateDisplayClear(CCmdUI *pCmdUI);
	afx_msg void OnSelectcurveNurbs();
	afx_msg void OnUpdatePointsWeight(CCmdUI *pCmdUI);
	afx_msg void OnPointsIncreaseweight();
	afx_msg void OnPointsDecreaseweight();
	afx_msg void OnSelectcurveBeziersurface3();
	afx_msg void OnSelectcurveBeziersurface4();
	afx_msg void OnSelectCubicbsplinesurface();
	afx_msg void OnSelectQuadraticbsplinesurface();
	afx_msg void OnSelectNurbssurface();
	afx_msg void OnViewportFront();
	afx_msg void OnViewportTop();
	afx_msg void OnViewportSide();
	afx_msg void OnViewportPerspective();
	afx_msg void OnViewportAll();
	afx_msg void OnSelectRevolutionsurface();
};