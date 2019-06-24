#include "StdAfx.h"
#include "cbezier.h"
#include "CHelpers.h"
#include <GL/gl.h>
#include <GL/glu.h>

const double CBezier::MINTIME = 0.0;
const double CBezier::MAXTIME = 1.0;

CBezier::CBezier(CMyOpenGLWnd *t_pparent):CCurve(t_pparent)
{
	m_dtimestep = 0.01;
	CHelpers::Initialise();
}


CBezier::~CBezier(void)
{
	CHelpers::Destroy();
}


//draws the bezier curve
void CBezier::Draw()
{
	CCurve::Draw();
	CCurve::DrawControlPolygon();
	int n = m_inumpoints - 1;
	if (n >0)
	{
		//uses helpers to calculate factorial
		long double t_infactorial = CHelpers::Instance()->Factorial(n);
		glColor3d(1.0,0.0,1.0);
		glBegin(GL_LINE_STRIP);
		list<Vector3d>::const_iterator j;
		for (double t_dtime=MINTIME; t_dtime <=MAXTIME; t_dtime += m_dtimestep)
		{
			j = m_point.begin();
			Vector3d t_vertex;
			for(int i=0; i<=n; i++,j++)
			{
				//uses helpers to calculate factorials and the power
				long double t_dweight = ((long double)t_infactorial / (long double)(CHelpers::Instance()->Factorial(i) * CHelpers::Instance()->Factorial(n-i))) * CHelpers::Instance()->Power(t_dtime,i) * CHelpers::Instance()->Power(1 - t_dtime,n-i);
				t_vertex += t_dweight * (*j);
			}

			//draws depending upon viewport
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
		j = m_point.end();
		j--;
		//draws the last point
		glVertex3d((*j).x,(*j).y,(*j).z);
		glEnd();
	}
	
}