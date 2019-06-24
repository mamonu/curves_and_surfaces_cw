#pragma once
#include "CBezier.h"
#include <GL/gl.h>
#include <GL/glu.h>


//enum {Bezier,QuadraticBSpline,Hermite};

class CManager
{
public:
	static const int BEZIER           = 0;
	static const int QUADRATICBSPLINE = 1;
	static const int CUBICBSPLINE	  = 2;
	static const int HERMITE		  = 3;	
private:
	CCurve *m_pcurve;
public:
	CManager(void);
	~CManager(void);
	void Create(const int t_icurve);
	void Update(const int t_iscreenx,const int t_iscreeny);
	void Draw();
	void UnselectPoint();
	void SetCurveMode(const int & t_imode);

};

inline void CManager::Update(const int t_iscreenx,const int t_iscreeny)
{
	if (m_pcurve)
	{
		double t_dmodel[16];
		double t_dproj[16];
		int t_ivp[4];
		glGetDoublev(GL_MODELVIEW_MATRIX,t_dmodel);
		glGetDoublev(GL_PROJECTION_MATRIX,t_dproj);
		glGetIntegerv(GL_VIEWPORT,t_ivp);
		GLdouble t_dx,t_dy,t_dz;
		gluUnProject(t_iscreenx,t_iscreeny,0.0,t_dmodel,t_dproj,t_ivp,&t_dx,&t_dy,&t_dz);
		m_pcurve->Update(Vector3d(t_dx,-t_dy,0.0));
		
	}
}


inline void CManager::Draw()
{
	if (m_pcurve)
	{
		m_pcurve->Draw();
	}
}

inline void CManager::UnselectPoint()
{
	if (m_pcurve)
	{
		m_pcurve->UnselectPoint();
	}
}

inline void CManager::SetCurveMode(const int & t_imode)
{
	if (m_pcurve)
	{
		m_pcurve->SetMode(t_imode);
	}
}