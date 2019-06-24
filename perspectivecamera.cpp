#include "StdAfx.h"
#include "perspectivecamera.h"
 
Perspectivecamera::Perspectivecamera(void)
{
}


//----------------------------------------------



void Perspectivecamera::ProjectionMode()const	//sets perspective projection mode
{
	glViewport(_vpstartx,_vpstarty,_vpwidth,_vpheight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(_left,_right,_bottom,_top,_nearp,_farp);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


//----------------------------------------------