#include "camera.h"

void camera::update() {
	float cosR, cosP, cosY;
	float sinR, sinP, sinY;
	//roll,pitch,yaw
	cosY = cosf(yaw * 3.1415 / 180);
	cosP = cosf(pitch * 3.1415 / 180);
	cosR = cosf(roll * 3.1415 / 180);
	sinY = sinf(yaw * 3.1415 / 180);
	sinP = sinf(pitch * 3.1415 / 180);
	sinR = sinf(roll * 3.1415 / 180);
	//this is to calculate some values used alot

	forward.x = sinY * cosP;
	forward.y = sinP;
	forward.z = cosP * -cosY;

	//where the camera pionts

	up.x = -cosY * sinR - sinY * sinP * cosR;
	up.y = cosP * cosR;
	up.z = -sinY * sinR - sinP * cosR * -cosY;
	//where up is

	right = forward.cross(up);
}
Vector3 camera::getPosition() {
	return position;
}
Vector3 camera::getDirection() {
	return (position + forward);
}
Vector3 camera::getUp() {
	return up;
}
Vector3 camera::realGetUp() {
	return (up);
}
void camera::setPosition(int x, int y, int z) {
	position = x, y, z;
}
void camera::setrotation(int x, int y, int z) {
	pitch = x;
	yaw = y;
	roll = z;
}
void camera::moveForward(int speed, float dt) {
	dt *= speed;
	position.add(forward,dt);
	//up.add(forward, dt);
	//moves our camera forward
}
void camera::strafeRight(int speed, float dt) {
	dt *= speed;
	right = forward.cross(up);
	position.add(right, dt);
	//up.add(right, -dt);
	//moves our camera to the right
}
void camera::flyUp(int speed, float dt) {
	dt *= speed;
	position.add(up,dt);
	//moves camera up
}

void camera::rotateZ(int speed, float dt) {
	roll = roll + (speed*dt);
	update();
}
void camera::rotateY(int speed, float dt) {
	yaw = yaw + (speed*dt);
	update();
}
void camera::rotateX(int speed, float dt) {
	pitch = pitch + (speed * dt);
	update();
}



