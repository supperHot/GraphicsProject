#pragma once
#include "Vector3.h"
class camera
{
private:
	Vector3 position = (0, 0, 6);
	Vector3 forward; //forward dircetion
	Vector3 up; //up direction
	Vector3 right;
	float yaw = 0;
	float pitch = 0;
	float roll =  0;
	float speed = 0;
	int x;
public:
	void update();
	void moveForward(int, float);
	void strafeRight(int, float);
	void flyUp(int, float);
	void rotateX(int, float);
	void rotateY(int, float);
	void rotateZ(int, float);

	void setPosition(int, int, int);
	void setrotation(int, int, int);

	Vector3 getPosition();
	Vector3 getDirection();
	Vector3 getUp();
	Vector3 realGetUp();
};