#include "Skybox.h"

void Skybox::render() {
	glBindTexture(GL_TEXTURE_2D, texture);//here we add our texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBegin(GL_QUADS);
	//--
	glVertex3f(position.x - 0.5, position.y - 0.5, position.z + 0.5);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(position.x - 0.5, position.y + 0.5, position.z + 0.5);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(position.x + 0.5, position.y + 0.5, position.z + 0.5);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(position.x + 0.5, position.y - 0.5, position.z + 0.5);
	glTexCoord2f(1.0, 0.0);
	//--
	glVertex3f(position.x - 0.5, position.y - 0.5, position.z - 0.5);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(position.x - 0.5, position.y + 0.5, position.z - 0.5);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(position.x - 0.5, position.y + 0.5, position.z + 0.5);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(position.x - 0.5, position.y - 0.5, position.z + 0.5);
	glTexCoord2f(1.0, 0.0);
	//--
	glVertex3f(position.x + 0.5, position.y - 0.5, position.z - 0.5);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(position.x + 0.5, position.y + 0.5, position.z - 0.5);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(position.x + 0.5, position.y + 0.5, position.z + 0.5);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(position.x + 0.5, position.y - 0.5, position.z + 0.5);
	glTexCoord2f(1.0, 0.0);
	//--
	glVertex3f(position.x - 0.5, position.y - 0.5, position.z - 0.5);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(position.x - 0.5, position.y + 0.5, position.z - 0.5);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(position.x + 0.5, position.y + 0.5, position.z - 0.5);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(position.x + 0.5, position.y - 0.5, position.z - 0.5);
	glTexCoord2f(1.0, 0.0);
	//--
	glVertex3f(position.x - 0.5, position.y + 0.5, position.z - 0.5);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(position.x - 0.5, position.y + 0.5, position.z + 0.5);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(position.x + 0.5, position.y + 0.5, position.z + 0.5);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(position.x + 0.5, position.y + 0.5, position.z - 0.5);
	glTexCoord2f(1.0, 0.0);
	//--
	glVertex3f(position.x - 0.5, position.y - 0.5, position.z - 0.5);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(position.x - 0.5, position.y - 0.5, position.z + 0.5);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(position.x + 0.5, position.y - 0.5, position.z + 0.5);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(position.x + 0.5, position.y - 0.5, position.z - 0.5);
	glTexCoord2f(1.0, 0.0);
	//--
	glEnd();
}

void Skybox::load(char* filename)
{
	texture = SOIL_load_OGL_texture
	(
		filename,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_INVERT_Y // Depending on texture file type some need inverted others don't.
	);

	//check for an error during the load process
	if (texture == 0)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}

}

void Skybox::update(float x,float y,float z) {
	position.x = x;
	position.y = y;
	position.z = z;
}