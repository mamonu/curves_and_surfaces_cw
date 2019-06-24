#pragma once
#include "CBSpline.h"
#include "CSurface.h"


class CBSplineSurface : public CSurface
{
protected:
	int m_iuprevpoints;
	int m_ivprevpoints;
	int *m_piuknot;
	int *m_pivknot;
	int m_iorder;
public:
	CBSplineSurface(CMyOpenGLWnd *t_pparent,const int & t_iorder);
	~CBSplineSurface(void);
	void Draw();
};
