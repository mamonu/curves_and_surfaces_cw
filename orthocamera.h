#pragma once
#include "Camera.h"

class Orthocamera : public Camera			//inherits from camera
{
public:
	Orthocamera(void);
	void ProjectionMode(void)const;
};
