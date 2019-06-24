#pragma once
#include "Vector3d.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include "Vector3d.h"


class Camera			//abstract class :can not be instantiated
{
protected:
	Vector3d _eye;
	Vector3d _center;
	Vector3d _up;
	GLint _vpstartx,_vpstarty;
	GLsizei _vpwidth,_vpheight;
	GLdouble _left,_right,_bottom,_top,_nearp,_farp;
	Vector3d _direction;
	GLdouble _yaw,_pitch;
	GLdouble _radius;
public:
	Camera(void);
	~Camera(void);
	void SetEye(const Vector3d & eye); 
	void SetUp(const Vector3d & up) {_up=up;}
	void SetClippingPlane(const GLdouble & left, const GLdouble & right, const GLdouble & bottom, const GLdouble & top, const GLdouble & nearp, const GLdouble & farp);
	void SetViewport(const GLint & startx, const GLint & starty, const GLsizei & width, const GLsizei & height);
	Vector3d Eye()const	{return _eye;}
	Vector3d Center()const {return _center;}
	Vector3d Up()const	{return _up;}
	void Yaw(const GLdouble & angle);
	void Pitch(const GLdouble & angle);
	void Move(const GLdouble & speed);
	void StartCamera()const;
	void ChangeClippingPlane(const GLdouble delleft,const GLdouble delright,const GLdouble delbottom,const GLdouble deltop,const GLdouble delnear,const GLdouble delfar);
	virtual void ProjectionMode(void)const = 0;
	void SetCenter(const Vector3d & center);
	void SetCamera(const Vector3d & eye , const Vector3d & center , const Vector3d & up);
	Vector3d Direction(void) { return _direction; }
};
