#include "Trench.h"

/*
the ternch class makes most of our world
*/



void Trench::render(){

	glBindTexture(GL_TEXTURE_2D, ground);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBegin(GL_QUADS);
	for (float z = 0; z < 200;z += 2) {
		for (float x = 0; x < 4;x += 2) {
			glVertex3f(0 + x, 0, 0 + z);
			glTexCoord2f(0.0f, 0.0f);
			glNormal3f(0, 1, 0);

			glVertex3f(0 + x, 0, 2 + z);
			glTexCoord2f(0.0f, 1.0f);
			glNormal3f(0, 1, 0);

			glVertex3f(2 + x, 0, 2 + z);
			glTexCoord2f(1.0f, 1.0f);
			glNormal3f(0, 1, 0);

			glVertex3f(2 + x, 0, 0 + z);
			glTexCoord2f(1.0f, 0.0f);
			glNormal3f(0, 1, 0);
		}//theses loops make a bunch of quads to make the planes have plenty of normals to catch light
	}
	glEnd();
	//--
	glBindTexture(GL_TEXTURE_2D, wall);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBegin(GL_QUADS);
	for (float z = 0; z < 200;z+=2) {
		for (float y = 0; y < 6;y+=2) {
			glVertex3f(0, 0 + y, 0 + z);
			glTexCoord2f(0.0f, 0.0f);

			glVertex3f(0, 2 + y, 0 + z);
			glTexCoord2f(0.0f, 1.0f);

			glVertex3f(0, 2 + y, 2 + z);
			glTexCoord2f(1.0f, 1.0f);

			glVertex3f(0, 0 + y, 2 + z);
			glTexCoord2f(1.0f, 0.0f);
			//--
			glVertex3f(4, 0 + y, 0 + z);
			glTexCoord2f(0.0f, 0.0f);

			glVertex3f(4, 2 + y, 0 + z);
			glTexCoord2f(0.0f, 1.0f);

			glVertex3f(4, 2 + y, 2 + z);
			glTexCoord2f(1.0f, 1.0f);

			glVertex3f(4, 0 + y, 2 + z);
			glTexCoord2f(1.0f, 0.0f);
		}
	}
	glEnd();

	//pre calculated shadows
//	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(0.1, 0.1, 0.1, 0.8);
	glBegin(GL_QUADS);
	glVertex3f(0, 0.01, 0);
	glVertex3f(4, 0.01, 0);
	glVertex3f(4, 0.01, 200);
	glVertex3f(0, 0.01, 200);
	//---
	glVertex3f(0.01, 0.0, 0);
	glVertex3f(0.01, 6.0, 0);
	glVertex3f(0.01, 6.0, 200);
	glVertex3f(0.01, 0.0, 200);
	//---
	glVertex3f(3.99, 0.0, 0);
	glVertex3f(3.99, 1.0, 0);
	glVertex3f(3.99, 1.0, 200);
	glVertex3f(3.99, 0.0, 200);
	glEnd();
	glEnable(GL_BLEND);
//	glEnable(GL_LIGHTING);


}

void Trench::load(char* floorTexture, char* wallTexture)
{
	ground = SOIL_load_OGL_texture
	(
		floorTexture,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_INVERT_Y // Depending on texture file type some need inverted others don't.
	);

	//check for an error during the load process
	if (ground == 0)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}

	wall = SOIL_load_OGL_texture
	(
		wallTexture,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_INVERT_Y // Depending on texture file type some need inverted others don't.
	);

	//check for an error during the load process
	if (wall == 0)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}
}