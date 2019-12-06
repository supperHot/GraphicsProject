
#pragma once

	using namespace std;

	// INCLUDES //
#include <glut.h>
#include <fstream>
#include <gl/gl.h>
#include <gl/glu.h>
#include "SOIL.h"
#include "Vector3.h"

	class Skybox
	{
	private:
		GLuint texture;
		Vector3 position;
	public:
		void render();
		void update(float,float,float);
		void load(char*);
	};

