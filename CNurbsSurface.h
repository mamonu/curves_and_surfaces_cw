#pragma once
#include "CBSplineSurface.h"

//inherits from bspline surface
class CNurbsSurface : public CBSplineSurface
{
private:
	list<int> m_iweight;
	list<int>::iterator m_selectedweight;
	void AddPoint(const Vector3d & t_point);
	void DeletePoint();
	bool PointIsSelected(const Vector3d & t_point);
public:
	CNurbsSurface(CMyOpenGLWnd *t_pparent,const int & t_iorder);
	~CNurbsSurface(void);
	void Draw();
	void Update(Vector3d & t_point);
	void Clear();
	bool CanChangeWeight()const {	return true;	}
};
