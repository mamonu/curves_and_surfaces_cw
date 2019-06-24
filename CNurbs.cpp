#include "StdAfx.h"
#include "cnurbs.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include "CBSplineHelpers.h"

CNurbs::CNurbs(CMyOpenGLWnd *t_pparent,const int & t_iorder):CBSpline(t_pparent,t_iorder)
{
}

CNurbs::~CNurbs(void)
{
	m_iweight.clear();
}

//adds the point and its weight in respective lists
void CNurbs::AddPoint(const Vector3d & t_point)
{
	CCurve::AddPoint(t_point);
	m_iweight.push_back(rand()%10 + 2);
}


//deletes the point and its weight from their respective lists
void CNurbs::DeletePoint()
{
	CCurve::DeletePoint();
	m_iweight.erase(m_selectedweight);
}


//selects the point depending upon viewport
bool CNurbs::PointIsSelected(const Vector3d & t_point)
{
	// in side view
	if (t_point.x == 0.0)
	{
		list<int>::iterator j = m_iweight.begin();
		for ( list<Vector3d>::iterator i=m_point.begin() ; i!=m_point.end() ; i++,j++)
		{
			double t_dy =(*i).y - t_point.y;
			double t_dz = (*i).z - t_point.z;
			double t_ddist = sqrt(t_dy*t_dy + t_dz*t_dz);
			if ((t_ddist <= 1.0E-2))
			{
				m_selectedpoint = i;
				m_selectedweight = j;
				return true;	
			}
		}
	}
	//in top view
	else if (t_point.y == 0.0)
	{
		list<int>::iterator j = m_iweight.begin();
		for ( list<Vector3d>::iterator i=m_point.begin() ; i!=m_point.end() ; i++,j++)
		{
			double t_dx =(*i).x - t_point.x;
			double t_dz = (*i).z - t_point.z;
			double t_ddist = sqrt(t_dx*t_dx + t_dz*t_dz);
			if ((t_ddist <= 1.0E-2))
			{
				m_selectedpoint = i;
				m_selectedweight = j;
				return true;	
			}
		}	
	}
	//in front view
	else if (t_point.z == 0.0)
	{
		list<int>::iterator j = m_iweight.begin();
		for ( list<Vector3d>::iterator i=m_point.begin() ; i!=m_point.end() ; i++,j++)
		{
			double t_dx =(*i).x - t_point.x;
			double t_dy = (*i).y - t_point.y;
			double t_ddist = sqrt(t_dx*t_dx + t_dy*t_dy);
			if ((t_ddist <= 1.0E-2))
			{
				m_selectedpoint = i;
				m_selectedweight = j;
				return true;	
			}
		}	
	}
		return false;
}



//inserts point and weight in between two control points depending upon viewport
void CNurbs::InsertPoint(const Vector3d & t_point)
{
	if (m_inumpoints >= 2)
	{
		list<Vector3d>::iterator i = m_point.begin();
		list<int>::iterator k= m_iweight.begin();
		for(int j=1; j<m_inumpoints; j++)
		{
			Vector3d t_p2 = (*i);	i++; k++;
			Vector3d t_p1 = (*i);
			
			// in front view
			if (t_point.z == 0.0)
			{
				t_p2.z = 0.0;
				t_p1.z = 0.0;
			}
			else if (t_point.x == 0.0)
			{
				t_p2.x = 0.0;
				t_p1.x = 0.0;
			}
			else if (t_point.y == 0.0)
			{
				t_p2.y = 0.0;
				t_p1.y = 0.0;
			}

			// uses distance formula from point to line and checks if distance is very close to line
			Vector3d t_direction = t_p2 - t_p1;
			double u = (t_direction * (t_point - t_p1))/t_direction.LengthSqr();
			if (u>0 && u<1)
			{
				Vector3d t_projection = (t_p1 +  (u * (t_direction))) ;
				double t_ddistance = (t_point - t_projection).Length();
				if(t_ddistance <=1.0E-2)
				{
					m_point.insert(i,t_point);
					m_iweight.insert(k,rand()%10+1);
					m_inumpoints++;
					break;
				}
			}
		}
	}	
}

//updates the curve and the weights
void CNurbs::Update(Vector3d & t_point)
{
	CCurve::Update(t_point);
	if (m_imode == CCurve::INCREASEWEIGHT)
	{
		if (CNurbs::PointIsSelected(t_point))
			(*m_selectedweight)+=1;
	}
	else if (m_imode == CCurve::DECREASEWEIGHT)
	{
		if (CNurbs::PointIsSelected(t_point))
			(*m_selectedweight)-=1;
			if ((*m_selectedweight)< 1)
				(*m_selectedweight) =1;
	}
		

}

//draws the curve
void CNurbs::Draw()
{
	CCurve::Draw();
	CCurve::DrawControlPolygon();

	if (m_inumpoints > m_iorder)
	{
		//creates standard knots only if the number of control points has changed
		if (m_iprevnumpoints != m_inumpoints)
		{
			m_iprevnumpoints = m_inumpoints;
			//uses helpers for creating standard knots
			CBSplineHelpers::Instance()->CreateStandardKnots(m_inumpoints,m_iorder,&m_piknot);
		}
			
		glColor3d(1.0,0.5,0.5);
		glBegin(GL_LINE_STRIP);
		//stores weight in a dynamic array
		double *t_pdwt = new double[m_inumpoints];
		double t_dmaxtime = m_inumpoints - m_iorder + 1.0;
		for(double t_dtime =0; t_dtime<= t_dmaxtime; t_dtime +=0.01  )
		{
			list<int>::const_iterator k = m_iweight.begin();
			double t_dsum = 0.0;
			for (int i=0; i<m_inumpoints; i++,k++)
			{
				double t_dweight = (*k) * CBSplineHelpers::Instance()->Weight(i,m_iorder,t_dtime,m_piknot);
				t_pdwt[i] = t_dweight;
				t_dsum += t_dweight;

			}
			
			list<Vector3d>::iterator j = m_point.begin();
			Vector3d t_vertex;
			for (int i=0; i<m_inumpoints; i++,j++)
			{
				t_vertex += (*j) * (t_pdwt[i]/t_dsum);
			}

			//draws the point depending upon the viewport
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
		glEnd();
		//clean up the array
		delete [] t_pdwt;
		
	}
}

//clears the curve
void CNurbs::Clear()
{
	CCurve::Clear();
	m_iweight.clear();
}

