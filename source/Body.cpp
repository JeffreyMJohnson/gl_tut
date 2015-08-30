#include "Body.h"


void Body::Translate(vec3 newPosition)
{
	mTransform = glm::translate(mTransform, newPosition);
}

void Body::Scale(vec3 newScale)
{
	mTransform = glm::scale(mTransform, newScale);
}

void Body::Rotate(float angle, vec3 axis)
{
	mTransform = glm::rotate(mTransform, glm::radians(angle), axis);
}

void Body::SetParentTransform(const mat4* parentTransform)
{
	mParentTransform = parentTransform;
}
