#include "StdAfx.h"
#include "chermite.h"
#include <GL/gl.h>
#include <GL/glu.h>

CHermite::CHermite(CMyOpenGLWnd *t_pparent):CCurve(t_pparent)
{
}

CHermite::~CHermite(void)
{
}

//adds point. adds the tangent as the second point depending upon the view 
void CHermite::AddPoint(const Vector3d & t_point)
{
	CCurve::AddPoint(t_point);
	m_inumpoints++;
	int t_iviewport = m_pparent->GetViewport();
	if ( t_point.z == 0.0)
		m_point.push_back(Vector3d(t_point.x,t_point.y + 0.1,t_point.z));
	else if ( t_point.x == 0.0)
		m_point.push_back(Vector3d(t_point.x,t_point.y + 0.1,t_point.z));
	else if ( t_point.y == 0.0)
		m_point.push_back(Vector3d(t_point.x,t_point.y,t_point.z - 0.1));
}

//deletes the point and its tangent
void CHermite::DeletePoint()
{
	Vector3d t_point = (*m_selectedpoint);
	int j=0;
	for(list<Vector3d>::iterator i = m_point.begin(); i!= m_point.end(); i++,j++)
	{
		if (((*i).x==t_point.x) && ((*i).y==t_point.y) && ((*i).z==t_point.z))
		{

			if((j%2) == 0)
			{
				++m_selectedpoint;
				m_point.erase(i,++m_selectedpoint);
				
			}
			else
			{
				i--;
				m_selectedpoint++;
				m_point.erase(i,m_selectedpoint);
			}
			break;
		}
	}
	m_inumpoints-=2;
	
}


//draws the hermite curve
void CHermite::Draw()
{
	CCurve::Draw();
	if ((m_inumpoints >= 4))
	{
		glColor3d(1.0,0.5,0.5);
		glBegin(GL_POINTS);

		list<Vector3d>::const_iterator j = m_point.begin();
		int k=0;
		while( k < m_inumpoints)
		{
			Vector3d t_vertex;
			Vector3d t_point1 = (*j++);
			Vector3d t_point2 = (*j++);
			Vector3d t_point3 = (*j++);
			Vector3d t_point4 = (*j--);
			Vector3d t_tangent1 = (t_point2 - t_point1) ;
			Vector3d t_tangent2 = (t_point4 - t_point3) ;
			for (double t_dtime=0.0; t_dtime < 1.0; t_dtime+=0.001)
			{
				double t_dt2 = pow(t_dtime,2);
				double t_dt3 = t_dt2 * t_dtime;
				
				double t_dh1 = 2 * t_dt3 - 3 * t_dt2  + 1;
				double t_dh2 = -2 * t_dt3 + 3 * t_dt2 ;
				double t_dh3 = t_dt3 - 2 * t_dt2 + t_dtime;
				double t_dh4 = t_dt3 - t_dt2;

				t_vertex = t_point1 * t_dh1 + t_tangent1 * t_dh3 + t_tangent2 * t_dh4 + t_point3 * t_dh2;

				//draws depending upon the viewport
				int t_iviewport = m_pparent->GetViewport();
				if ( t_iviewport == CMyOpenGLWnd::XY)
					glVertex3d(t_vertex.x,t_vertex.y,0.0);
				else if ( t_iviewport == CMyOpenGLWnd::YZ)
					glVertex3d(0.0,t_vertex.y,t_vertex.z);
				else if ( t_iviewport == CMyOpenGLWnd::ZX)
					glVertex3d(t_vertex.x,0.0,t_vertex.z);
				else
					glVertex3d(t_vertex.x,t_vertex.y,t_vertex.z);
			}
			k+=2;
		}
		glEnd();
	}

	//draws the lines connecting the points and their tangents depending upon the view
	glColor3d(0.5,0.5,0.5);
	glBegin(GL_LINES);
	list<Vector3d>::const_iterator i = m_point.begin();
	while (i != m_point.end())
	{
		int t_iviewport = m_pparent->GetViewport();
		if ( t_iviewport == CMyOpenGLWnd::XY)
		{
			glVertex3d((*i).x,(*i).y,0.0); i++;
			glVertex3d((*i).x,(*i).y,0.0); i++;
		}
		else if ( t_iviewport == CMyOpenGLWnd::YZ)
		{
			glVertex3d(0.0,(*i).y,(*i).z); i++;
			glVertex3d(0.0,(*i).y,(*i).z); i++;
		}
		else if ( t_iviewport == CMyOpenGLWnd::ZX)
		{
			glVertex3d((*i).x,0.0,(*i).z); i++;
			glVertex3d((*i).x,0.0,(*i).z); i++;
		}
		else
		{
			glVertex3d((*i).x,(*i).y,(*i).z); i++;
			glVertex3d((*i).x,(*i).y,(*i).z); i++;
		}
	}
	glEnd();
	
}