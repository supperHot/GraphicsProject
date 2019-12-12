#include "Ship.h"

Vector3 Ship::getPosition() {
	return postition;
}
void Ship::update(float dt) {
	postition.z += 1 * dt;
}