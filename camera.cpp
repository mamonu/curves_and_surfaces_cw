#include "StdAfx.h"
#include "camera.h"
#include<math.h>
#define DEGREE_TO_RAD 0.0174532925

Camera::Camera()
{
	_yaw=0.0;
	_pitch=0.0;
}


//------------------------------------------



Camera::~Camera()
{
}


//------------------------------------------




void Camera::SetClippingPlane(const GLdouble & left, const GLdouble & right, const GLdouble & bottom, const GLdouble & top, const GLdouble & nearp, const GLdouble & farp) //sets the clipping planes the viewing volume 
{
	_left=left;	
	_right=right;
	_bottom=bottom; 
	_top=top;
	_nearp=nearp;
	_farp=farp;
}


//------------------------------------------




void Camera::SetViewport(const GLint & startx, const GLint & starty, const GLsizei & width, const GLsizei & height)  //sets the viewport
{
	_vpstartx=startx;
	_vpstarty=starty;
	_vpwidth=width;
	_vpheight=height;
}



//------------------------------------------




void Camera::Yaw(const GLdouble & angle)			//yaw camera: moves the eye and sets new position of eye
{
	_yaw+=angle;
	_eye.z=_center.z+_radius*cos(_pitch*DEGREE_TO_RAD)*cos(_yaw*DEGREE_TO_RAD);
	_eye.x=_center.x+_radius*cos(_pitch*DEGREE_TO_RAD)*sin(_yaw*DEGREE_TO_RAD);
	_direction=_eye - _center;
	//_direction.Subtract(_eye,_center);
	_direction.Normalise();
}


//------------------------------------------




void Camera::Pitch(const GLdouble & angle)			//pitches camera: moves the eye and sets new position of eye
{
	_pitch+=angle;
	_eye.y=_center.y-_radius*sin(_pitch*DEGREE_TO_RAD);
	_eye.z=_center.z+_radius*cos(_pitch*DEGREE_TO_RAD)*cos(_yaw*DEGREE_TO_RAD);
	_eye.x=_center.x+_radius*cos(_pitch*DEGREE_TO_RAD)*sin(_yaw*DEGREE_TO_RAD);
	_direction=_eye - _center;
	//_direction.Subtract(_eye,_center);
	_direction.Normalise();
}



//------------------------------------------




void Camera::Move(const GLdouble &speed)			//moves camera in the direction of looking
{
	Vector3d dir=_direction * speed;
	_eye += dir;
	_center +=dir;
	//_radius +=speed;
	//_eye = _center + _direction*_radius;
}



//------------------------------------------




void Camera::StartCamera(void)const					//starts the camera 
{
	gluLookAt(_eye.x,_eye.y,_eye.z,_center.x,_center.y,_center.z,_up.x,_up.y,_up.z);
}



//------------------------------------------




void Camera::ChangeClippingPlane(const GLdouble delleft,const GLdouble delright,const GLdouble delbottom,const GLdouble deltop,const GLdouble delnear,const GLdouble delfar) //changes the clipping planes
{
	_left+=delleft;	
	_right+=delright;
	_bottom+=delbottom;
	_top+=deltop;
	_nearp+=delnear;
	_farp+=delfar;
}



//------------------------------------------




void Camera::SetEye(const Vector3d & eye)		//sets the eye and updates the center accordingly
{
	_eye=eye;
	//_center.Subtract(_eye,_direction.MultConst(_radius));
	_center = _eye - (_direction * _radius);
}



//------------------------------------------




void Camera::SetCenter(const Vector3d & center)		//sets the center and updates the eye accordingly
{
	_center=center;
	//_eye.Add(_center,_direction.MultConst(_radius));
	_eye = _center + (_direction * _radius);
}



//------------------------------------------




void Camera::SetCamera(const Vector3d & eye , const Vector3d & center , const Vector3d & up)		//sets the camera and initializes the pitch angle and yaw depending upon direction of looking
{
	_eye=eye; _center=center; _up=up; 
    //_direction.Subtract(_eye,_center);
	_direction = _eye - _center;
	_radius=_direction.Length();
	_direction.Normalise();
	GLdouble temp;
	temp=asin(_direction.y);
	_yaw=asin(_direction.x/cos(temp))*180.0/3.14285714;
	_pitch=-temp*180.0/3.14285714;
}




//------------------------------------------