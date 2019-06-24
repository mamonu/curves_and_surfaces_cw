#include "StdAfx.h"
#include "textureloader.h"
#include <fstream>

using namespace std;

textureloader::textureloader(void)
{
	_texturehandle=0;
}


//---------------------------------------------



textureloader::~textureloader(void)
{
	glDeleteTextures(1, &_texturehandle);
}


//---------------------------------------------




BOOL textureloader::LoadTextureData(const char * file)
{
	Bitmap textureimage;
	ifstream fin(file,ios::binary);
	if (!fin){
		AfxMessageBox("Error: unable to load bitmap file");
		return FALSE;
	}
	textureimage.Read(fin);
    glGenTextures(1, &_texturehandle);	
 	glBindTexture(GL_TEXTURE_2D, _texturehandle);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	gluBuild2DMipmaps( GL_TEXTURE_2D, 3, textureimage.Width(), textureimage.Height(), GL_BGR_EXT,
			GL_UNSIGNED_BYTE, textureimage.Bits() );

    return TRUE;
}



//---------------------------------------------



void textureloader::ApplyTexture()const
{
	glBindTexture(GL_TEXTURE_2D, _texturehandle);
}


//---------------------------------------------