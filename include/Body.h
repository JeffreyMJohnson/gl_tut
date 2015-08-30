#pragma once
#include <glm\glm.hpp>
#include <glm\ext.hpp>

#include <iostream>

using glm::vec3;
using glm::vec4;
using glm::mat4;

const vec4 WHITE = vec4(1, 1, 1, 1);
const vec4 GREY = vec4(.5f, .5f, .5f, 1);
const vec4 WIRE_FRAME = vec4(1, 1, 1, 0);


class Body
{
public:
	vec3 rotation();
	vec4 color = WHITE;
	float radius = 0;
	float rotationSpeed = 0;
	mat4 mTransform = mat4(1);
	const mat4* mParentTransform = nullptr;


	void Translate(vec3 newPosition);

	void Scale(vec3 newScale);

	void Rotate(float angle, vec3 axis);

	void SetParentTransform(const mat4* parentTransform);

private:

};
