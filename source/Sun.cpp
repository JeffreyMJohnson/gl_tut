#include "..\include\Sun.h"

void Sun::Init()
{
	color = WIRE_FRAME;
	radius = 2;
	rotationSpeed = 5;
}

void Sun::Update(float deltaTime)
{
	mTransform *= glm::rotate(glm::radians(deltaTime * rotationSpeed), vec3(0, 1, 0));
}
