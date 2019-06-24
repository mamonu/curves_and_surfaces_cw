#pragma once
#include "CCurve.h"

class CBezier : public CCurve
{
private:
	static const double MINTIME;
	static const double MAXTIME;
	double m_dtimestep;
public:
	CBezier(CMyOpenGLWnd *t_pparent);
	~CBezier(void);
	void Draw();
};
