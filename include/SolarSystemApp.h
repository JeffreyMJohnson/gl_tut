#pragma once
#include "GameApp.h"
#include "Color.h"

using glm::vec3;
using glm::vec4;
using glm::mat4;

enum BODY
{
	SUN,
	MERCURY,
	VENUS,
	EARTH,
	MOON,
	MARS,
	JUPITER,
	SATURN,
	URANUS,
	NEPTUNE,
	PLUTO
};

class SolarSystemApp : public GameApp
{
public:
	const int WINDOW_WIDTH = 1280;
	const int WINDOW_HEIGHT = 720;
	const char* WINDOW_TITLE = "Solar System Exercise";
	const vec4 CLEAR_COLOR = vec4(.25f, .25f, .25f, 1);

	const static int MAX_BODY_COUNT = 11;

	const bool DEBUG_MODE = true;

	// Inherited via GameApp
	bool StartUp();

	void ShutDown();

	bool Update();

	void Draw();

private:
	mat4 view = mat4(1);
	mat4 projection = mat4(1);
	mat4* localTransforms[MAX_BODY_COUNT];
	mat4* orbitTransform[MAX_BODY_COUNT];
};