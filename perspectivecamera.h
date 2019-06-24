#pragma once
#include "Camera.h"

class Perspectivecamera :public Camera		//inherits from camera
{
public:
	Perspectivecamera(void);
	void ProjectionMode(void)const;
};
