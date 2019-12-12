#pragma once
#include "Model.h"
class Ship :
	public model
{
protected:

public:
	Vector3 getPosition();
	void update(float);
};

