#pragma once
#include "CBezier.h"

class CRevolutionSurface : public CBezier
{
public:
	CRevolutionSurface(CMyOpenGLWnd * t_pparent);
	~CRevolutionSurface(void);
	void Draw();
};
