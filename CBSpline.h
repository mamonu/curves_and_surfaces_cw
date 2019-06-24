#pragma once
#include "CCurve.h"

class CBSpline: public CCurve
{
protected:
	int m_iorder;
	int m_iprevnumpoints;
	int *m_piknot;
	/*void CreateStandardKnots(const int &t_inumpoints,const int &t_iorder,int **t_piknot);
	double Weight(const int & t_ik,const int & t_iorder,const double & t_dtime,int *t_piknot);*/
public:
	CBSpline(CMyOpenGLWnd *t_pparent);
	CBSpline(CMyOpenGLWnd *t_pparent,const int & t_iorder);
	~CBSpline(void);
	void Draw();
	
};
