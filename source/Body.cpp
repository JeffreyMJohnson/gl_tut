#include "Body.h"


Body::Body(vec3 a_position, float a_radius, vec3 a_scale, vec4 a_color)
{
	SetPosition(a_position);
	radius = a_radius;
	SetScale(a_scale);
	color = a_color;
	mTransform = mat4(1);
}


void Body::SetPosition(vec3 newPosition)
{
	mPosition = newPosition;
	mTransform = glm::translate(mTransform, mPosition);
}

void Body::SetScale(vec3 newScale)
{
	mScale = newScale;
	mTransform = glm::scale(mTransform, newScale);
}

void Body::SetRotation(float angle, vec3 axis)
{
	mRotation = axis * angle;
	mTransform = glm::rotate(mTransform, glm::radians(angle), axis);
}



void Body::Update(float deltaTime)
{


}

void Body::Draw()
{
	Gizmos::addSphere(vec3(), radius, 10, 10, color, &mTransform);
}