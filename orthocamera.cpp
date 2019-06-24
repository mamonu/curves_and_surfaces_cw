#include "StdAfx.h"
#include "orthocamera.h"

Orthocamera::Orthocamera(void)
{
}

 
//----------------------------------------------



void Orthocamera::ProjectionMode(void)const			//sets ortho projection mode
{
	glViewport(_vpstartx,_vpstarty,_vpwidth,_vpheight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(_left,_right,_bottom,_top,_nearp,_farp);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}



//----------------------------------------------