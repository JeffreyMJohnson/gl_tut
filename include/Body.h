#pragma once
#include <glm\glm.hpp>
#include <glm\ext.hpp>
#include <aie\Gizmos.h>

using glm::vec3;
using glm::vec4;
using glm::mat4;


class Body
{
public:
	vec3 rotation;
	vec4 color;
	float radius;

	Body(vec3 a_position = vec3(1), float a_radius = 1.0f,  vec3 a_scale = vec3(1), vec4 a_color = vec4(1,1,1,.5f));
	
	void SetPosition(vec3 newPosition);

	void SetScale(vec3 newScale);

	void SetRotation(float angle, vec3 axis);

	void Update(float deltaTime);

	void Draw();

private:
	mat4 mTransform;
	vec3 mPosition, mScale, mRotation;
};
