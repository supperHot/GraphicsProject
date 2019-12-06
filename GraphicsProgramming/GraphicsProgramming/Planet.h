#pragma once
#include <glut.h>
#include <fstream>
#include <gl/gl.h>
#include <gl/glu.h>

using namespace std;

// MY CLASS INCLUDES //
#include <vector>
#include "Vector3.h"
#include "SOIL.h"
#include "Vector3.h"

class Planet
{
private:
	Vector3 position = (0,0,0);
	float speed;
	int quality;
	float radius;
	void setPiont(float,float, float,float);
	GLuint texture;
	float roatation = 0;
public:
	void load(char* filename);
	void setRadius(float);
	void setQuality(int);
	void setSpeed(float);
	void setPosition(float,float,float);
	Vector3 getPosition();
	void render();
	void update(float);
};

