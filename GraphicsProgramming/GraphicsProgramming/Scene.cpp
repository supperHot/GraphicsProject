#include "Scene.h"


// Scene constructor, initilises OpenGL
// You should add further variables to need initilised.

Scene::Scene(Input *in)
{
	// Store pointer for input class
	input = in;
		
	//OpenGL settings
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);			// Cornflour Blue Background
	glutSetCursor(GLUT_CURSOR_NONE);
	glClearDepth(1.0f);									// Depth Buffer Setup
	glClearStencil(0);									// Clear stencil buffer
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);

	// Other OpenGL / render setting should be applied here.
	
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);

	// Initialise scene variables

	//texture variables


	tie1->load("models/spaceship.obj","models/spaceship.png");
	tie2->load("models/spaceship.obj", "models/spaceship.png");
	tie3->load("models/spaceship.obj", "models/spaceship.png");
	xWing->load("models/spaceship.obj", "models/spaceship.png");

	tie1->setPosition(0,0,0);
	tie2->setPosition(2,0,0);
	tie3->setPosition(2,2,0);
	xWing->setPosition(0,2,0);

	yavin->setPosition(0, 0, 0);
	yavin->setQuality(50);
	yavin->setRadius(1.0);
	yavin->load("gfx/yavin.png");
	yavin->setSpeed(0.1);
	skybox->load("gfx/skyboxSpace.png");
	//-
	yavin4->setPosition(0, 0, 0);
	yavin4->setQuality(20);
	yavin4->setRadius(0.05);
	yavin4->load("gfx/yavin4.png");
	yavin4->setSpeed(0.05);

	son->setPosition(0, 0, 0);
	son->setQuality(20);
	son->setRadius(0.04);
	son->load("gfx/son.png");

	trench->load("gfx/ground.bmp", "gfx/wall.png");

	camera1.update();
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	GLfloat Light_Ambient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	glLightfv(GL_LIGHT2, GL_AMBIENT, Light_Ambient);

	GLfloat Light_Diffuse[] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat Light_Position[] = { -1.0f, 0.0f, 0.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Light_Diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, Light_Position);

	GLfloat Light_Diffuse1[] = { 1.0f,1.0f,0.5f,1.0f };
	GLfloat Light_Position1[] = { 0.0f, 0.0f, -1.0f, 1.0f };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Light_Diffuse1);
	glLightfv(GL_LIGHT1, GL_POSITION, Light_Position1);
}

void Scene::handleInput(float dt)
{
	//moving the camera (the else is to stop you moving in opppiste dircetions at the same time)
	

	if (input->isKeyDown('w')) {
		camera1.moveForward(30,dt);
	}
	else
		if (input->isKeyDown('s')) {
			camera1.moveForward(-30, dt);
		}
	
	//---
	if (input->isKeyDown('a')) {
		camera1.strafeRight(-10, dt);
	}
	else
		if (input->isKeyDown('d')) {
			camera1.strafeRight(10, dt);
		}
	//---
	if (input->isKeyDown('n')) {
		camera1.flyUp(-10, dt);
	}
	else
		if (input->isKeyDown('m')) {
			camera1.flyUp(10, dt);
		}
	//---
	if (input->isKeyDown('e')) {
		camera1.rotateZ(30, dt);
	}
	else
		if (input->isKeyDown('q')) {
			camera1.rotateZ(-30, dt);
		}
	if (input->getMouseX() > width/2) {
		camera1.rotateY(30, dt);
	}
	else
		if (input->getMouseX() < width/2) {
			camera1.rotateY(-30, dt);
		}
	if (input->getMouseY() < height / 2) {
		camera1.rotateX(30, dt);

	}
	else
		if (input->getMouseY() > height / 2) {
			camera1.rotateX(-30, dt);
		}
	if (input->isKeyDown('1')) {
		cameraAngle = 1;
	}
	if (input->isKeyDown('2')) {
		cameraAngle = 2;
	}
	if (input->isKeyDown('3')) {
		cameraAngle = 3;
	}
	if (input->isKeyDown('4')) {
		cameraAngle = 4;
	}
	if (input->isKeyDown('5')) {
		cameraAngle = 5;
	}
}

void Scene::update(float dt)
{
	// update scene related variables.
	
	glutWarpPointer(width / 2,height /2);
	yavin->setPosition(camera1.getPosition().x + 1.15, camera1.getPosition().y + 0.1, camera1.getPosition().z + 0.3);
	yavin->update(dt);
	yavin4->setPosition(camera1.getPosition().x + 0.35, camera1.getPosition().y + 0.2, camera1.getPosition().z + 1.0);
	yavin4->update(dt);
	son->setPosition(camera1.getPosition().x - 2.00, camera1.getPosition().y - 0.1, camera1.getPosition().z + 0.0);
	skybox->update(camera1.getPosition().x, camera1.getPosition().y, camera1.getPosition().z);
	GLfloat Light_Position1[] = { camera1.getPosition().x - 1.0f,camera1.getPosition().y, camera1.getPosition().z, 1.0f };
	// Calculate FPS for output
	calculateFPS();
	

}

void Scene::render() {
	
	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// Reset transformations
	glLoadIdentity();
	switch (cameraAngle) {
		case 1:
		gluLookAt(camera1.getPosition().x, camera1.getPosition().y, camera1.getPosition().z,
			camera1.getDirection().x, camera1.getDirection().y, camera1.getDirection().z,
			camera1.getUp().x, camera1.getUp().y, camera1.getUp().z);
		break;
		case 2:
		gluLookAt(camera1.getPosition().x, camera1.getPosition().y, camera1.getPosition().z,
			camera1.getDirection().x, camera1.getDirection().y, camera1.getDirection().z,
			camera1.getUp().x, camera1.getUp().y, camera1.getUp().z);

	}
	//skyBos---
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT1);
	glDisable(GL_DEPTH_TEST);
	skybox->render();
	glEnable(GL_CULL_FACE);
	yavin4->render();//planet
	yavin->render();//planet
	son->render();
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDisable(GL_LIGHT1);
	//skyBox ---

	glEnable(GL_LIGHT0);

	tie1->render();
	tie2->render();
	tie3->render();
	xWing->render();
	trench->render();
	
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT2);
	// Render text, should be last object rendered.
	renderTextOutput();
	
	// Swap buffers, after all objects are rendered.
	glutSwapBuffers();
}

// Handles the resize of the window. If the window changes size the perspective matrix requires re-calculation to match new window size.
void Scene::resize(int w, int h) 
{
	width = w;
	height = h;
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0) {
		h = 1;
	}
	float ratio = (float)w / (float)h;
	fov = 90.0f;
	nearPlane = 0.1f;
	farPlane = 100.0f;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(fov, ratio, nearPlane, farPlane);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);

	
}

// Calculates FPS
void Scene::calculateFPS()
{

	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);

	if (time - timebase > 1000) {
		sprintf_s(fps, "FPS: %4.2f", frame*1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}
}

// Compiles standard output text including FPS and current mouse position.
void Scene::renderTextOutput()
{
	// Render current mouse position and frames per second.
	sprintf_s(mouseText, "Mouse: %i, %i", input->getMouseX(), input->getMouseY());
	sprintf_s(upwards, "up: %f, %f,%f", camera1.getUp().x,camera1.getUp().y,camera1.getUp().z);
	displayText(-1.f, 0.96f, 1.f, 0.f, 0.f, mouseText);
	displayText(-1.f, 0.90f, 1.f, 0.f, 0.f, fps);
	displayText(-1.f, 0.82f, 1.f, 0.f, 0.f, upwards);
}

// Renders text to screen. Must be called last in render function (before swap buffers)
void Scene::displayText(float x, float y, float r, float g, float b, char* string) {
	// Get Lenth of string
	int j = strlen(string);

	// Swap to 2D rendering
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 5, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Orthographic lookAt (along the z-axis).
	gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Set text colour and position.
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	// Render text.
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
	}
	// Reset colour to white.
	glColor3f(1.f, 1.f, 1.f);

	// Swap back to 3D rendering.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, ((float)width/(float)height), nearPlane, farPlane);
	glMatrixMode(GL_MODELVIEW);
}
