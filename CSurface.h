#pragma once
#include "CCurve.h"
#include "textureloader.h"

class CSurface : public CCurve
{
protected:
	int m_iupoints;
	int m_ivpoints;
	void AddPoint(const Vector3d & t_point);
	void DeletePoint();
public:
	CSurface(CMyOpenGLWnd *t_pparent,const int & t_ivpoints);
	~CSurface(void);
	bool CanInsertPoint() const {	return false;	}
	bool HasControlPolygon()const {	return false;	}
	void Clear();
	void Draw();
};
