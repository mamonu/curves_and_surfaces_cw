#pragma once
#include "CSurface.h"

//inherits from surface
class CBezierSurface: public CSurface
{

public:
	CBezierSurface(CMyOpenGLWnd *t_pparent,const int t_ivpoints);
	~CBezierSurface(void);
	void Draw();
};
