#include "StdAfx.h"
#include "csurface.h"

CSurface::CSurface(CMyOpenGLWnd *t_pparent,const int & t_ivpoints): CCurve(t_pparent)
{
	m_ivpoints = t_ivpoints;
	m_iupoints = 0;
}

CSurface::~CSurface(void)
{
}


//adds control point and the neighbouring control points in the list
void CSurface::AddPoint(const Vector3d & t_point)
{
	CCurve::AddPoint(t_point);
	if (t_point.z == 0.0)
	{
		for (int i=1; i<m_ivpoints; i++)
			CCurve::AddPoint(Vector3d(t_point.x,t_point.y - 0.1*i,t_point.z));
	}
	else if (t_point.x == 0.0)
	{
		for (int i=1; i<m_ivpoints; i++)
			CCurve::AddPoint(Vector3d(t_point.x,t_point.y - 0.1*i,t_point.z));
	}
	else if (t_point.y == 0.0)
	{
		for (int i=1; i<m_ivpoints; i++)
			CCurve::AddPoint(Vector3d(t_point.x,t_point.y,t_point.z + 0.1*i));
	}
	m_iupoints++;
}



//deletes the selected point
void CSurface::DeletePoint()
{
	Vector3d t_point = (*m_selectedpoint);
	int j=0;
	for(list<Vector3d>::iterator i = m_point.begin(); i!= m_point.end(); i++,j++)
	{
		if (((*i).x==t_point.x) && ((*i).y==t_point.y) && ((*i).z==t_point.z))
		{
			for (int k=0; k< m_ivpoints; k++)
			{
				if ((j % m_ivpoints) == k)
				{
					int l=0;
					while(l<k)
					{
						i--; 
						l++;
					}
					for (int m = m_ivpoints -k; m>0; m--)
						++m_selectedpoint;
					m_point.erase(i,m_selectedpoint);	//deletes the appropriate neighbouring points
					m_inumpoints -=4;
					m_iupoints--;
					return;
				}
			}
		}
	}
}

//draws the control points
void CSurface::Draw()
{
	CCurve::DrawPoints();
	//CCurve::DrawControlPolygon();
}


//clears the display
void CSurface::Clear()
{
	CCurve::Clear();
	m_iupoints=0;
}