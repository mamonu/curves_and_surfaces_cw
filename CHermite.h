#pragma once
#include "CCurve.h"

class CHermite:public CCurve
{
private:
	void AddPoint(const Vector3d & t_point);
	void DeletePoint();
public:
	CHermite(CMyOpenGLWnd *t_pparent);
	~CHermite(void);
	bool HasControlPolygon()const {	 return false;	}
	bool CanInsertPoint() const {	return false;	}
	void Draw();
};
