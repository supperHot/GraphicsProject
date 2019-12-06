#include "Planet.h"
void Planet::setRadius(float newRadius) {
	radius = newRadius;
}
void Planet::setQuality(int newQuality) {
	quality = newQuality;
}
void Planet::setSpeed(float newSpeed) {
	speed = newSpeed;
}
void Planet::setPosition(float x,float y,float z) {
	position.x = x;
	position.y = y;
	position.z = z;
}
Vector3 Planet::getPosition() {
	return (position);
}
void Planet::render() {
	float latitude = 0;
	float longitude = roatation;
	float segment1 = (2*3.14159) / quality;
	float segment2 = (2*3.14159) / quality;
	float textureIncriment = 1.0/quality;
	float textureX = 0;
	float textureY = 0;
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBegin(GL_QUADS);
	for (int i = 0; i < quality/2; i++) {
		for (int j = 0; j < quality; j++) {
			setPiont(latitude, longitude, 0.0, 0.0);
			setPiont(latitude, longitude + segment1, 1.0, 0.0);
			setPiont(latitude + segment2, longitude + segment1, 1.0, 1.0);
			setPiont(latitude + segment2, longitude, 0.0, 1.0);
			longitude += segment2;
		}
		latitude += segment1;
	}
	glEnd();
	
}
void Planet::setPiont(float longitude, float latitude, float textureX, float textureY) {
	float sinlatitude = sin(latitude);
	float coslatitude = cos(latitude);
	float coslongitude = cos(longitude);
	float sinlongitude = sin(longitude);
	glVertex3f((radius * coslatitude * sinlongitude) + position.x,
		(radius * coslongitude) + position.y,
		(radius * sinlatitude * sinlongitude) + position.z);
	glNormal3f(coslatitude * sinlongitude,
		coslongitude,
		sinlatitude * sinlongitude);
	glTexCoord2f(textureX, textureY);
}
void Planet::load(char* filename)
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
void Planet::update(float dt) {
	roatation += speed * dt;
	if (roatation > 360) {
		roatation = 0;
	}
}