#pragma once
#include "GameApp.h"
#include "Color.h"
#include "FlyCamera.h"

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
	const float CAMERA_FOV = glm::pi<float>() * .25f;
	const float CAMERA_NEAR = .1f;
	const float CAMERA_FAR = 1000.0f;
	const vec3 CAMERA_FROM = vec3(10, 10, 10);
	const vec3 CAMERA_TO = vec3(0);
	const vec3 CAMERA_UP = vec3(0, 1, 0);

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
	FlyCamera* mCamera = nullptr;

	void InitBodies();
	void InitCamera();
};