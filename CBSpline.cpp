#include "StdAfx.h"
#include "cbspline.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include "CBSplineHelpers.h"

CBSpline::CBSpline(CMyOpenGLWnd *t_pparent):CCurve(t_pparent)
{

}

CBSpline::CBSpline(CMyOpenGLWnd *t_pparent,const int & t_iorder):CCurve(t_pparent)
{
	m_iprevnumpoints = 0;
	m_piknot = NULL;
	m_iorder = t_iorder;
	CBSplineHelpers::Initialise();
}

CBSpline::~CBSpline(void)
{
	CBSplineHelpers::Destroy();
	if (m_piknot)
		delete [] m_piknot;
}

//draws the bspline curve
void CBSpline::Draw()
{
	CCurve::Draw();
	CCurve::DrawControlPolygon();

	if (m_inumpoints > m_iorder)
	{
		//creates standard knots only if the number of control points has changed
		if (m_iprevnumpoints != m_inumpoints)
		{
			m_iprevnumpoints = m_inumpoints;
			CBSplineHelpers::Instance()->CreateStandardKnots(m_inumpoints,m_iorder,&m_piknot);
		}
		glColor3d(1.0,0.5,0.5);
		glBegin(GL_LINE_STRIP);
		for(double t_dtime =0; t_dtime<= m_inumpoints - m_iorder + 1.0; t_dtime +=0.01  )
		{
			list<Vector3d>::const_iterator j = m_point.begin();
			Vector3d t_vertex;
			for (int i=0; i<m_inumpoints; i++,j++)
			{
				double t_dweight =CBSplineHelpers::Instance()->Weight(i,m_iorder,t_dtime,m_piknot);
				t_vertex += t_dweight * (*j);
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
		
	}
}