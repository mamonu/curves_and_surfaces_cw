#include "StdAfx.h"
#include "cbeziersurface.h"
#include "CHelpers.h"
#include <GL/gl.h>

CBezierSurface::CBezierSurface(CMyOpenGLWnd *t_pparent,const int t_ivpoints):CSurface(t_pparent,t_ivpoints)
{
	CHelpers::Initialise();
}



CBezierSurface::~CBezierSurface(void)
{
	CHelpers::Destroy();
}



//draws the bezier curve
void CBezierSurface::Draw()
{
	CSurface::Draw();
	int ni = m_iupoints - 1;
	if (ni >0)
	{
		int nj = m_ivpoints - 1;
		//uses helpers to calculate the factorials
		long double t_inifactorial = CHelpers::Instance()->Factorial(ni);
		long double t_injfactorial = CHelpers::Instance()->Factorial(nj);

		//stores the control points in the dynamic 2d array from the list
		list<Vector3d>::const_iterator k = m_point.begin();
		Vector3d **t_ppoints = new Vector3d* [m_iupoints];
		for (int i=0; i< m_iupoints; i++)
		{
			t_ppoints[i] = new Vector3d[m_ivpoints];
			for (int j=0; j< m_ivpoints; j++,k++)
				t_ppoints[i][j] = (*k);
		}

		glColor3d(1.0,0.0,1.0);
		
		for(double u=0.0; u<=1.0; u+=0.1)
		{
			glBegin(GL_LINE_STRIP);
			for (double v=0.0; v<=1.0; v+=0.1)
			{
				Vector3d t_vertex;
				for (int i=0; i<=ni; i++)
				{
					long double t_diweight = ((long double)t_inifactorial / (long double)(CHelpers::Instance()->Factorial(i) * CHelpers::Instance()->Factorial(ni-i))) * CHelpers::Instance()->Power(u,i) * CHelpers::Instance()->Power(1 - u,ni-i);
					for (int j=0; j<=nj; j++)
					{
						long double t_djweight = ((long double)t_injfactorial / (long double)(CHelpers::Instance()->Factorial(j) * CHelpers::Instance()->Factorial(nj-j))) * CHelpers::Instance()->Power(v,j) * CHelpers::Instance()->Power(1 - v,nj-j);
						t_vertex += t_ppoints[i][j] * (t_diweight * t_djweight);
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

		for(double u=0.0; u<= 1.0; u+=0.1)
		{
			glBegin(GL_LINE_STRIP);
			for (double v=0.0; v<=1.0; v+=0.1)
			{
				Vector3d t_vertex;
				for (int i=0; i<=ni; i++)
				{
					long double t_diweight = ((long double)t_inifactorial / (long double)(CHelpers::Instance()->Factorial(i) * CHelpers::Instance()->Factorial(ni-i))) * CHelpers::Instance()->Power(v,i) * CHelpers::Instance()->Power(1 - v,ni-i);
					for (int j=0; j<=nj; j++)
					{
						long double t_djweight = ((long double)t_injfactorial / (long double)(CHelpers::Instance()->Factorial(j) * CHelpers::Instance()->Factorial(nj-j))) * CHelpers::Instance()->Power(u,j) * CHelpers::Instance()->Power(1 - u,nj-j);
						t_vertex += t_ppoints[i][j] * (t_diweight * t_djweight);
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

		//clean up the array created above
		for (int i=0; i< m_iupoints; i++)
			delete [] t_ppoints[i];
		delete [] t_ppoints;
		
	}
}