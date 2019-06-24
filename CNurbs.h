#pragma once
#include "CBSpline.h"
#include <list>
#include "Vector3d.h"

using namespace std;

class CNurbs:public CBSpline
{
private:
	list<int> m_iweight;
	list<int>::iterator m_selectedweight;
	void AddPoint(const Vector3d & t_point);
	void DeletePoint();
	void InsertPoint(const Vector3d & t_point);
	bool PointIsSelected(const Vector3d & t_point);
public:
	CNurbs(CMyOpenGLWnd *t_pparent,const int & t_iorder);
	~CNurbs(void);
	void Draw();
	void Update(Vector3d & t_point);
	void Clear();
	bool CanChangeWeight()const {	return true;	}
	
};
