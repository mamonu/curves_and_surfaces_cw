#pragma once
#include "Bitmap.h"
#include <GL/gl.h>
#include <GL/glu.h>

class textureloader
{
private:
	//Bitmap _textureimage;
	GLuint _texturehandle;
public:
	textureloader(void);
	~textureloader(void);
	BOOL LoadTextureData(const char * file);
	void ApplyTexture()const;
    
};
