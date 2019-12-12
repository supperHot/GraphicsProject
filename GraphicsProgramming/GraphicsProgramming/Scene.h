// Scene class. Configures a basic 3D scene.
// Interfaces with the Input class to handle user input
// Calculates and outputs Frames Per Second (FPS) rendered.
// Important functions are the constructor (initialising the scene), 
// update (for process user input and updating scene objects) and render (renders scene).
#ifndef _SCENE_H
#define _SCENE_H

// Include GLUT, openGL, input.
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Input.h"
#include <stdio.h>
// Further includes should go here:
#include "SOIL.h"
#include <vector>
#include "model.h"
#include "camera.h"
#include "trench.h"
#include "Planet.h"
#include "Skybox.h"
#include "Ship.h"

class Scene{

public:
	Scene(Input *in);
	// Main render function
	void render();
	// Handle input function that receives delta time from parent.
	void handleInput(float dt);
	// Update function receives delta time from parent (used for frame independent updating).
	void update(float dt);
	// Resizes the OpenGL output based on new window size.
	void resize(int w, int h);

protected:
	// Renders text (x, y positions, RGB colour of text, string of text to be rendered)
	void displayText(float x, float y, float r, float g, float b, char* string);
	// A function to collate all text output in a single location
	void renderTextOutput();
	void calculateFPS();

	// draw primitive functions
	

	// For access to user input.
	Input* input;
		
	// For Window and frustum calculation.
	int width, height;
	float fov, nearPlane, farPlane;

	// For FPS counter and mouse coordinate output.
	int frame = 0, time, timebase = 0;
	char fps[40];
	char mouseText[40];
	char upwards[40];

	camera camera1;
	camera* cameraMan = &camera1;

	model sphere;
	model* ball = &sphere;

	Ship fighter1; Ship* tie1 = &fighter1;
	Ship fighter2; Ship* tie2 = &fighter2;
	Ship fighter3; Ship* tie3 = &fighter3;
	Ship fighter4; Ship* xWing = &fighter4;


	Trench pit;
	Trench* trench = &pit;
	
	Planet planet1;
	Planet* yavin = &planet1;
	Planet planet2;
	Planet* yavin4 = &planet2;
	Planet star;
	Planet* son = &star;

	Skybox box;
	Skybox* skybox = &box;

	int cameraAngle = 1;
	float moveZ;
	float moveX;
	float moveY;
	bool wireframe;
};

#endif