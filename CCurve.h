#pragma once
#include "Vector3d.h"
#include <list>
using namespace std;
#include "CMyOpenGLWnd.h"

class CMyOpenGLWnd;

class CCurve
{
public:
	static const int ADDPOINT         = 0;
	static const int MODIFYPOINT      = 1;
	static const int DELETEPOINT      = 2;
	static const int INSERTPOINT      = 3;
	static const int INCREASEWEIGHT   = 4;
	static const int DECREASEWEIGHT   = 5;
protected:
	CMyOpenGLWnd *m_pparent;
	list<Vector3d> m_point;
	list<Vector3d>::iterator m_selectedpoint;
	int m_imode;
	int m_inumpoints;
	bool m_bdisplay;
	bool m_bselected;
	virtual void AddPoint(const Vector3d & t_point);
	virtual void DeletePoint();
	virtual void InsertPoint(const Vector3d & t_point);
	virtual bool PointIsSelected(const Vector3d & t_point);
	void DrawPoints();
	void DrawControlPolygon();
	void DrawSelectedPoint();
public:
	CCurve(CMyOpenGLWnd *t_pparent);
	virtual ~CCurve(void);
	virtual void Draw();
	virtual void Update(Vector3d & t_point);
	virtual bool HasControlPolygon()const {	return true;	}
	virtual bool CanInsertPoint() const {	return true;	}
	virtual bool CanChangeWeight()const {	return false;	}
	void UnselectPoint() {	m_bselected = false;	}
	void SetMode(const int &t_imode )	{	m_imode = t_imode;	}
	bool IsSelected() {	return m_bselected;	}
	void SetPolygonDisplay(const bool t_bdisplay)	{	m_bdisplay = t_bdisplay;	}
	virtual void Clear();
};
