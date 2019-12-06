#pragma once

using namespace std;

// INCLUDES //
#include <glut.h>
#include <fstream>
#include <gl/gl.h>
#include <gl/glu.h>
#include "SOIL.h"

class Trench
{
private:
	GLuint ground;
	GLuint wall;
public:
	void render();
	void update(float);
	void load(char*, char*);
};

