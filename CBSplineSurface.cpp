#include "StdAfx.h"
#include "cbsplinesurface.h"
#include <GL/gl.h>
#include "CBSplineHelpers.h"

CBSplineSurface::CBSplineSurface(CMyOpenGLWnd *t_pparent,const int & t_iorder):CSurface(t_pparent,t_iorder + 1)
{
	m_iupoints = 0;
	m_iuprevpoints=0;
	m_ivprevpoints=0;
	m_piuknot = NULL;
	m_pivknot = NULL;
	m_iorder = t_iorder;
	CBSplineHelpers::Initialise();
}



CBSplineSurface::~CBSplineSurface(void)
{
	CBSplineHelpers::Destroy();
}



//draws the bspline
void CBSplineSurface::Draw()
{
	CSurface::Draw();

	// draws only if horizontal points are greater than the order
	if (m_iupoints > m_iorder) 
	{
		//stores control points from list into dynamic 2d array of control points
		list<Vector3d>::const_iterator k = m_point.begin();
		Vector3d **t_ppoints = new Vector3d* [m_iupoints];
		for (int i=0; i< m_iupoints; i++)
		{
			t_ppoints[i] = new Vector3d[m_ivpoints];
			for (int j=0; j< m_ivpoints; j++,k++)
				t_ppoints[i][j] = (*k);
		}
		
		//checks if previous points are same so it doesnt calculate the standard knot if same
		if (m_iuprevpoints != m_iupoints) 
		{
			m_iuprevpoints = m_iupoints;
			CBSplineHelpers::Instance()->CreateStandardKnots(m_iupoints,m_iorder,&m_piuknot); //uses bspline helper to create standard knot
		}

		if (m_ivprevpoints != m_ivpoints)
		{
			m_ivprevpoints = m_ivpoints;
			CBSplineHelpers::Instance()->CreateStandardKnots(m_ivpoints,m_iorder,&m_pivknot);
		}

		double ui = m_iupoints - m_iorder + 1.0;
		double vj = m_ivpoints - m_iorder + 1.0;

		glColor3d(1.0,0.5,0.5);
		

		for(double u=0.0; u<=ui; u+=0.1)
		{
			glBegin(GL_LINE_STRIP);
			for (double v=0.0; v<=vj; v+=0.1)
			{
				
				Vector3d t_vertex;
				for(int i=0; i< m_iupoints; i++)
				{
					//uses bspline helpers to calculate the weight
					double t_duweight = CBSplineHelpers::Instance()->Weight(i,m_iorder,u,m_piuknot);
					for (int j=0; j< m_ivpoints; j++)
					{
						double t_dvweight = CBSplineHelpers::Instance()->Weight(j,m_iorder,v,m_pivknot);
						t_vertex += t_ppoints[i][j] * (t_duweight * t_dvweight);
					}
				}

				//draws the surface depending upon in which viewport to be drawn
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

		for(double u=0.0; u<=ui; u+=0.1)
		{
			glBegin(GL_LINE_STRIP);
			for (double v=0.0; v<=vj; v+=0.1)
			{
				
				Vector3d t_vertex;
				for(int i=0; i< m_iupoints; i++)
				{
					//uses bspline helpers to calculate the weight
					double t_duweight = CBSplineHelpers::Instance()->Weight(i,m_iorder,v,m_piuknot);
					for (int j=0; j< m_ivpoints; j++)
					{
						double t_dvweight = CBSplineHelpers::Instance()->Weight(j,m_iorder,u,m_pivknot);
						t_vertex += t_ppoints[i][j] * (t_duweight * t_dvweight);
					}
				}

				//draws the surface depending upon in which viewport to be drawn
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


		

		//clean up the dynamic array
		for (int i=0; i< m_iupoints; i++)
			delete [] t_ppoints[i];
		delete [] t_ppoints;
	}
}

