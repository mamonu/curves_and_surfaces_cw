#include "StdAfx.h"
#include "crevolutionsurface.h"
#include "CHelpers.h"
#define TWOPI 6.4

CRevolutionSurface::CRevolutionSurface(CMyOpenGLWnd * t_pparent): CBezier(t_pparent)
{
}

CRevolutionSurface::~CRevolutionSurface(void)
{
}

//draws the revolution surface if the basic curve is given in the front view
void CRevolutionSurface::Draw()
{
	CCurve::Draw();
	CCurve::DrawControlPolygon();
	int n = m_inumpoints - 1;
	if (n >0)
	{
		long double t_infactorial = CHelpers::Instance()->Factorial(n);
		glColor3d(1.0,0.0,1.0);
	//	glBegin(GL_POINTS);
		list<Vector3d>::const_iterator j;
		
		//for the revolution iterating from 0 to 2 pi
	//	for (double u =0.0; u<TWOPI; u+=0.1)
	//	{
	//		glBegin(GL_LINE_STRIP);
			//for generating bezier curve 
		for (double t_dtime=0.0; t_dtime <1.0; t_dtime += 0.05)
		{
			glBegin(GL_LINE_STRIP);
			
			j = m_point.begin();
			Vector3d t_vertex;
			
			for(int i=0; i<=n; i++,j++)
			{
				long double t_dweight = ((long double)t_infactorial / (long double)(CHelpers::Instance()->Factorial(i) * CHelpers::Instance()->Factorial(n-i))) * CHelpers::Instance()->Power(t_dtime,i) * CHelpers::Instance()->Power(1 - t_dtime,n-i);
				t_vertex += t_dweight * (*j);
			}
			for (double u =0.0; u<=TWOPI; u+=0.05)
			{
				glVertex3d(t_vertex.x*cos(u),t_vertex.y,t_vertex.x*sin(u));
			}
			glEnd();
		}

		for (double u =0.0; u<TWOPI; u+=0.05)
		{
			glBegin(GL_LINE_STRIP);
			//for generating bezier curve 
			for (double t_dtime=0.0; t_dtime <=1; t_dtime += 0.05)
			{
				j = m_point.begin();
				Vector3d t_vertex;
				
				for(int i=0; i<=n; i++,j++)
				{
					long double t_dweight = ((long double)t_infactorial / (long double)(CHelpers::Instance()->Factorial(i) * CHelpers::Instance()->Factorial(n-i))) * CHelpers::Instance()->Power(t_dtime,i) * CHelpers::Instance()->Power(1 - t_dtime,n-i);
					t_vertex += t_dweight * (*j);
				}
				glVertex3d(t_vertex.x*cos(u),t_vertex.y,t_vertex.x*sin(u));
			}
			glEnd();
		}

	}


}