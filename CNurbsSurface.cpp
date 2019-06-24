#include "StdAfx.h"
#include "cnurbssurface.h"
#include "CBSplineHelpers.h"
#include <GL/gl.h>

CNurbsSurface::CNurbsSurface(CMyOpenGLWnd *t_pparent,const int & t_iorder): CBSplineSurface(t_pparent,t_iorder)
{
}


CNurbsSurface::~CNurbsSurface(void)
{
	m_iweight.clear();
}


//adds the control point and adds the associated weight in the weight list for that point
void CNurbsSurface::AddPoint(const Vector3d & t_point)
{
	CSurface::AddPoint(t_point);
	for (int i=0; i<m_ivpoints; i++)
		m_iweight.push_back(rand()%10 + 2);
}

//deletes the control point and its weight from their respective lists
void CNurbsSurface::DeletePoint()
{
	Vector3d t_point = (*m_selectedpoint);
	int j=0;
	list<int>::iterator w = m_iweight.begin();
	for(list<Vector3d>::iterator i = m_point.begin(); i!= m_point.end(); i++,j++,w++)
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
						w--;
                        l++;
					}
					for (int m = m_ivpoints -k; m>0; m--)
					{
						++m_selectedpoint;
						++m_selectedweight;
					}
					//deletes the appropriate neighbours
					m_point.erase(i,m_selectedpoint);	
					m_iweight.erase(w,m_selectedweight);
					m_inumpoints -=4;
					m_iupoints--;
					return;
				}
			}
		}
	}
}


//selects the control point and its weight from their respective lists
//selects depending on which viewport it is in
bool CNurbsSurface::PointIsSelected(const Vector3d & t_point)
{
	// in side view
	if (t_point.x == 0.0)
	{
		list<int>::iterator j = m_iweight.begin();
		for ( list<Vector3d>::iterator i=m_point.begin() ; i!=m_point.end() ; i++,j++)
		{
			//uses distance formula to calculate the distance
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


//updates the surface and also updates the weight 
void CNurbsSurface::Update(Vector3d & t_point)
{
	CBSplineSurface::Update(t_point);
	if (m_imode == CCurve::INCREASEWEIGHT)
	{
		if (CNurbsSurface::PointIsSelected(t_point))
			(*m_selectedweight)+=1;
	}
	else if (m_imode == CCurve::DECREASEWEIGHT)
	{
		if (CNurbsSurface::PointIsSelected(t_point))
			(*m_selectedweight)-=1;
			if ((*m_selectedweight)< 1)
				(*m_selectedweight) =1;
	}
}


//clears the surface 
void CNurbsSurface::Clear()
{
	CBSplineSurface::Clear();
	m_iweight.clear();	
}

//draws the surface
void CNurbsSurface::Draw()
{
	CSurface::Draw();
	if (m_iupoints > m_iorder)
	{
		list<int>::const_iterator w = m_iweight.begin();
		list<Vector3d>::const_iterator k = m_point.begin();

		//stores control point and weight in the dynamic arrays respectively
		int **t_piweight = new int* [m_iupoints];
		Vector3d **t_ppoints = new Vector3d* [m_iupoints];
		double **t_pdwt = new double* [m_iupoints];
		for (int i=0; i< m_iupoints; i++)
		{
			t_piweight[i] = new int[m_ivpoints];
			t_ppoints[i] = new Vector3d[m_ivpoints];
			t_pdwt[i]= new double[m_ivpoints];
			for (int j=0; j< m_ivpoints; j++,k++,w++)
			{
				t_piweight[i][j] = (*w);
				t_ppoints[i][j] = (*k);
			}
		}

		//check whether to create standard knots or not
		if (m_iuprevpoints != m_iupoints)
		{
			m_iuprevpoints = m_iupoints;
			CBSplineHelpers::Instance()->CreateStandardKnots(m_iupoints,m_iorder,&m_piuknot);
		}

		if (m_ivprevpoints != m_ivpoints)
		{
			m_ivprevpoints = m_ivpoints;
			CBSplineHelpers::Instance()->CreateStandardKnots(m_ivpoints,m_iorder,&m_pivknot);
		}

		double ui = m_iupoints - m_iorder + 1.0;
		double vj = m_ivpoints - m_iorder + 1.0;

		glColor3d(1.0,0.5,0.5);
	
		for(double u=0.0; u<ui; u+=0.1)
		{
			for (double v=0.0; v<vj; v+=0.1)
			{
				glBegin(GL_LINE_STRIP);
				double t_dsum = 0.0;
				for(int i=0; i< m_iupoints; i++)
				{
					//uses helpers to calculate the bspline weight
					double t_duweight = CBSplineHelpers::Instance()->Weight(i,m_iorder,u,m_piuknot);
					for (int j=0; j< m_ivpoints; j++)
					{
						double t_dvweight = CBSplineHelpers::Instance()->Weight(j,m_iorder,v,m_pivknot);
						double t_dweight = t_piweight[i][j] * t_duweight * t_dvweight;
						t_pdwt[i][j] = t_dweight;//stores the weight in the dynamic array
						t_dsum += t_dweight;
					}
				}


				Vector3d t_vertex;
				for(int i=0; i< m_iupoints; i++)
				{
					for (int j=0; j< m_ivpoints; j++)
					{
						t_vertex += t_ppoints[i][j] * (t_pdwt[i][j]/t_dsum);
					}
				}

				//draws depending upon in which viewport
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
		}

		ui = m_ivpoints - m_iorder + 1.0;
		vj = m_iupoints - m_iorder + 1.0;

		for(double u=0.0; u<ui; u+=0.1)
		{
			for (double v=0.0; v<vj; v+=0.1)
			{
				glBegin(GL_LINE_STRIP);
				double t_dsum = 0.0;
				for(int i=0; i< m_iupoints; i++)
				{
					//uses helpers to calculate the bspline weight
					double t_duweight = CBSplineHelpers::Instance()->Weight(i,m_iorder,v,m_piuknot);
					for (int j=0; j< m_ivpoints; j++)
					{
						double t_dvweight = CBSplineHelpers::Instance()->Weight(j,m_iorder,u,m_pivknot);
						double t_dweight = t_piweight[i][j] * t_duweight * t_dvweight;
						t_pdwt[i][j] = t_dweight;//stores the weight in the dynamic array
						t_dsum += t_dweight;
					}
				}


				Vector3d t_vertex;
				for(int i=0; i< m_iupoints; i++)
				{
					for (int j=0; j< m_ivpoints; j++)
					{
						t_vertex += t_ppoints[i][j] * (t_pdwt[i][j]/t_dsum);
					}
				}

				//draws depending upon in which viewport
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
		}
		
		

		//clean up the arrays
		for (int i=0; i< m_iupoints; i++)
		{
			delete [] t_pdwt[i];
			delete [] t_ppoints[i];
			delete [] t_piweight[i];
		}
		delete [] t_pdwt;
		delete [] t_ppoints;
		delete [] t_piweight;
	}
}