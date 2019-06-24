#include "StdAfx.h"
#include "ccurve.h"
#include <GL/gl.h>
#include <GL/glu.h>



CCurve::CCurve(CMyOpenGLWnd *t_pparent)
{
	m_pparent = t_pparent;
	m_inumpoints = 0;
	m_bdisplay = false;
	m_bselected = false;
	
}

CCurve::~CCurve(void)
{
	m_point.clear();
}


//adds the control point in the list
void CCurve::AddPoint(const Vector3d & t_point)
{
	m_inumpoints++;
	m_point.push_back(t_point);
}


//deletes the selected control point
void CCurve::DeletePoint()
{
	m_inumpoints--;
	m_point.erase(m_selectedpoint);
}

//selects the point depending upon the viewport
//uses distance formula to calculate the selected point
bool CCurve::PointIsSelected(const Vector3d & t_point)
{
	//in side view
	if (t_point.x == 0.0)
	{
		for ( list<Vector3d>::iterator i=m_point.begin() ; i!=m_point.end() ; i++)
		{
			double t_dy =(*i).y - t_point.y;
			double t_dz = (*i).z - t_point.z;
			double t_ddist = sqrt(t_dy*t_dy + t_dz*t_dz);
			if ((t_ddist <= 1.0E-2))
			{
				m_selectedpoint = i;
				return true;	
			}
		}
	}
	//in top view
	else if (t_point.y == 0.0)
	{
		for ( list<Vector3d>::iterator i=m_point.begin() ; i!=m_point.end() ; i++)
		{
			double t_dx =(*i).x - t_point.x;
			double t_dz = (*i).z - t_point.z;
			double t_ddist = sqrt(t_dx*t_dx + t_dz*t_dz);
			if ((t_ddist <= 1.0E-2))
			{
				m_selectedpoint = i;
				return true;	
			}
		}	
	}
	//in front view
	else if (t_point.z == 0.0)
	{
		for ( list<Vector3d>::iterator i=m_point.begin() ; i!=m_point.end() ; i++)
		{
			double t_dx =(*i).x - t_point.x;
			double t_dy = (*i).y - t_point.y;
			double t_ddist = sqrt(t_dx*t_dx + t_dy*t_dy);
			if ((t_ddist <= 1.0E-2))
			{
				m_selectedpoint = i;
				return true;	
			}
		}	
	}
		return false;
}


//inserts point in the list between two control points
//inserts depending upon the viewport
void CCurve::InsertPoint(const Vector3d & t_point)
{
	if (m_inumpoints >= 2)
	{
		list<Vector3d>::iterator i = m_point.begin();
		for(int j=1; j<m_inumpoints; j++)
		{
			Vector3d t_p2 = (*i);	i++;
			Vector3d t_p1 = (*i);
			
			//if front view
			if (t_point.z == 0.0)
			{
				t_p2.z = 0.0;
				t_p1.z = 0.0;
			}
			//if side view
			else if (t_point.x == 0.0)
			{
				t_p2.x = 0.0;
				t_p1.x = 0.0;
			}
			//if top view
			else if (t_point.y == 0.0)
			{
				t_p2.y = 0.0;
				t_p1.y = 0.0;
			}
			//calculates the distance from point to the line
			Vector3d t_direction = t_p2 - t_p1;
			double u = (t_direction * (t_point - t_p1))/t_direction.LengthSqr();
			if (u>0 && u<1)
			{
				Vector3d t_projection = (t_p1 +  (u * (t_direction))) ;
				double t_ddistance = (t_point - t_projection).Length();
				if(t_ddistance <=1.0E-2)
				{
					m_point.insert(i,t_point);
					m_inumpoints++;
					break;
				}
			}
		}
	}
}


//updates the control points and curve
void CCurve::Update(Vector3d & t_point)
{
	
	if (!m_bselected)
	{
		if (m_imode == ADDPOINT)
		{
			AddPoint(t_point);
		}
		else if (m_imode == MODIFYPOINT)
		{
			if (PointIsSelected(t_point))
			{
				m_bselected = true;
			}
		}
		else if (m_imode == DELETEPOINT)
		{
			if (PointIsSelected(t_point))
			{
				DeletePoint();
			}
		}
		else if (m_imode == INSERTPOINT)
		{
			InsertPoint(t_point);
		}
	}
	else
	{
		//changes selected point depending upon the viewport
		if (t_point.x == 0.0)
		{
			(*m_selectedpoint).y = t_point.y;
			(*m_selectedpoint).z = t_point.z;
		}
		else if (t_point.y == 0.0)
		{
			(*m_selectedpoint).x = t_point.x;
			(*m_selectedpoint).z = t_point.z;
		}
		else if (t_point.z == 0.0)
		{
			(*m_selectedpoint).x = t_point.x;
			(*m_selectedpoint).y = t_point.y;
		}
	}
}

//highligts the selected point when modifying the point
void CCurve::DrawSelectedPoint()
{
	glColor3d(0.0,1.0,1.0);
	glPointSize((float)10.0);
	glBegin(GL_POINTS);

	int t_iviewport = m_pparent->GetViewport();
	if ( t_iviewport == CMyOpenGLWnd::XY)
		glVertex3d((*m_selectedpoint).x,(*m_selectedpoint).y,0.0);
	else if ( t_iviewport == CMyOpenGLWnd::YZ)
		glVertex3d(0.0,(*m_selectedpoint).y,(*m_selectedpoint).z);
	else if ( t_iviewport == CMyOpenGLWnd::ZX)
		glVertex3d((*m_selectedpoint).x,0.0,(*m_selectedpoint).z);
	else
		glVertex3d((*m_selectedpoint).x,(*m_selectedpoint).y,(*m_selectedpoint).z);

	glEnd();
}


//draws the control points
void CCurve::DrawPoints()
{
	if (m_bselected)
	{
		CCurve::DrawSelectedPoint();		
	}

	if (m_imode == ADDPOINT)
		glColor3d(0.5,1.0,0.75);
	else if (m_imode == MODIFYPOINT)
		glColor3d(0.0,0.0,1.0);
	else if (m_imode == INSERTPOINT)
		glColor3d(1.0,0.5,0.0);
	else if (m_imode == DELETEPOINT)
		glColor3d(0.5,0.7,0.3);
	else 
		glColor3d(0.1,0.4,0.6);

	list<Vector3d>::const_iterator i = m_point.begin();
	glPointSize((float)5.0);
	glBegin(GL_POINTS);
	while ( i != m_point.end())
	{
		//draws depending upon the view
		int t_iviewport = m_pparent->GetViewport();
		if ( t_iviewport == CMyOpenGLWnd::XY)
			glVertex3d((*i).x,(*i).y,0.0);
		else if ( t_iviewport == CMyOpenGLWnd::YZ)
			glVertex3d(0.0,(*i).y,(*i).z);
		else if ( t_iviewport == CMyOpenGLWnd::ZX)
			glVertex3d((*i).x,0.0,(*i).z);
		else
			glVertex3d((*i).x,(*i).y,(*i).z);
		i++;
	}
	glEnd();
	glPointSize(1.0);
	
}

//draws the control polygon
void CCurve::DrawControlPolygon()
{
	if (m_bdisplay)
	{
		glColor3d(0.0,0.5,0.0);
		glBegin(GL_LINE_STRIP);
		list<Vector3d>::const_iterator i = m_point.begin();
		while ( i != m_point.end())
		{
			//draws depending upon the view
			int t_iviewport = m_pparent->GetViewport();
			if ( t_iviewport == CMyOpenGLWnd::XY)
				glVertex3d((*i).x,(*i).y,0.0);
			else if ( t_iviewport == CMyOpenGLWnd::YZ)
				glVertex3d(0.0,(*i).y,(*i).z);
			else if ( t_iviewport == CMyOpenGLWnd::ZX)
				glVertex3d((*i).x,0.0,(*i).z);
			else
				glVertex3d((*i).x,(*i).y,(*i).z);
			i++;
		}
		glEnd();
	}
}


void CCurve::Draw()
{
	DrawPoints();
}


//clears the curve
void CCurve::Clear()
{
	m_point.clear();
	m_inumpoints=0;
}