#include "SolarSystemApp.h"

bool SolarSystemApp::StartUp()
{
	if (!glfwInit())
	{
		return false;
	}

	mWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, nullptr, nullptr);

	if (nullptr == mWindow)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(mWindow);


	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(mWindow);
		glfwTerminate();
		return false;
	}

	Gizmos::create();
	InitCamera();
	

	if (DEBUG_MODE)
	{
		int major = ogl_GetMajorVersion();
		int minor = ogl_GetMinorVersion();
		printf("GL: %i.%i\n", major, minor);
	}

	glClearColor(CLEAR_COLOR.r, CLEAR_COLOR.g, CLEAR_COLOR.b, CLEAR_COLOR.a);
	glEnable(GL_DEPTH_TEST);

	//init model transforms
	InitBodies();

	return true;
}

void SolarSystemApp::ShutDown()
{
	//destroy model transforms
	for (int i = 0; i < MAX_BODY_COUNT; i++)
	{
		delete localTransforms[i];
		delete orbitTransform[i];
	}
	delete mCamera;
	Gizmos::destroy();
	glfwDestroyWindow(mWindow);
	glfwTerminate();
}

bool SolarSystemApp::Update()
{
	if (glfwWindowShouldClose(mWindow) || glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		return false;
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Gizmos::clear();

	Gizmos::addTransform(mat4(1));

	vec4 white(1);
	vec4 black(0, 0, 0, 1);

	for (int i = 0; i < 21; i++)
	{
		Gizmos::addLine(vec3(-10 + i, 0, 10), vec3(-10 + i, 0, -10), i == 10 ? white : black);

		Gizmos::addLine(vec3(10, 0, -10 + i), vec3(-10, 0, -10 + i), i == 10 ? white : black);
	}

	timer.Update(glfwGetTime());

	*orbitTransform[MERCURY] = *orbitTransform[SUN] * glm::rotate(timer.CurrentTime + glm::radians(60.0f), vec3(0, 1, 0)) * glm::translate(vec3(0, 0, 1.5));
	*orbitTransform[VENUS] = *orbitTransform[SUN] * glm::rotate(timer.CurrentTime + glm::radians(30.0f), vec3(0, 1, 0)) * glm::translate(vec3(0, 0, 3));
	*orbitTransform[EARTH] = *orbitTransform[SUN] * glm::rotate(timer.CurrentTime, vec3(0, 1, 0)) * glm::translate(vec3(0, 0, 4.5f));
	*orbitTransform[MOON] = *orbitTransform[EARTH] * glm::rotate(timer.CurrentTime, vec3(0, 1, 0)) * glm::translate(vec3(0, 0, .75f));
	*orbitTransform[MARS] = *orbitTransform[SUN] * glm::rotate(timer.CurrentTime, vec3(0, 1, 0)) * glm::translate(vec3(0, 0, 6.5f));
	*orbitTransform[JUPITER] = *orbitTransform[SUN] * glm::rotate(timer.CurrentTime, vec3(0, 1, 0)) * glm::translate(vec3(0, 0, 9));
	*orbitTransform[SATURN] = *orbitTransform[SUN] * glm::rotate(timer.CurrentTime, vec3(0, 1, 0)) * glm::translate(vec3(0, 0, 11.5f));

	*localTransforms[SUN] = glm::rotate(timer.CurrentTime * .01f, vec3(0, 1, 0));
	*localTransforms[MERCURY] = glm::scale(vec3(.3f));
	*localTransforms[VENUS] = glm::scale(vec3(.5f));
	*localTransforms[EARTH] = glm::scale(vec3(.5f));
	*localTransforms[MOON] = glm::scale(vec3(.1f));
	*localTransforms[MARS] = glm::scale(vec3(.25f));
	*localTransforms[JUPITER] = glm::scale(vec3(.85f));
	*localTransforms[SATURN] = glm::scale(vec3(.75f));

	Gizmos::addSphere(vec3(), 1, 20, 20, WIRE_FRAME, &(*orbitTransform[SUN] * (*localTransforms[SUN])));
	Gizmos::addSphere(vec3(), 1, 20, 20, WIRE_FRAME, &(*orbitTransform[MERCURY] * (*localTransforms[MERCURY])));
	Gizmos::addSphere(vec3(), 1, 20, 20, WIRE_FRAME, &(*orbitTransform[VENUS] * (*localTransforms[VENUS])));
	Gizmos::addSphere(vec3(), 1, 20, 20, WIRE_FRAME, &(*orbitTransform[EARTH] * (*localTransforms[EARTH])));
	Gizmos::addSphere(vec3(), 1, 20, 20, WIRE_FRAME, &(*orbitTransform[MOON] * *localTransforms[MOON]));
	Gizmos::addSphere(vec3(), 1, 20, 20, WIRE_FRAME, &(*orbitTransform[MARS] * (*localTransforms[MARS])));
	Gizmos::addSphere(vec3(), 1, 20, 20, WIRE_FRAME, &(*orbitTransform[JUPITER] * (*localTransforms[JUPITER])));
	Gizmos::addSphere(vec3(), 1, 20, 20, WIRE_FRAME, &(*orbitTransform[SATURN] * (*localTransforms[SATURN])));

	Mouse::Update();
	mCamera->Update(timer.DeltaTime);

	//mat4 cameraTransform = glm::inverse(view);
	//cameraTransform = *localTransforms[SUN]* glm::translate(vec3(0, 1, 10));
	////cameraTransform = glm::translate(cameraTransform, vec3(timer.DeltaTime, 0, 0));
	//view = glm::inverse(cameraTransform);

	return true;
}

void SolarSystemApp::Draw()
{
	Gizmos::draw(mCamera->GetProjection() * mCamera->GetView());

	glfwSwapBuffers(mWindow);
	glfwPollEvents();
}

void SolarSystemApp::InitBodies()
{
	for (int i = 0; i < MAX_BODY_COUNT; i++)
	{
		localTransforms[i] = new mat4(1);
		orbitTransform[i] = new mat4(1);
	}
}
void SolarSystemApp::InitCamera()
{
	mCamera = new FlyCamera(mWindow);
	mCamera->SetSpeed(10.0f);
	mCamera->SetRotationSpeed(10.0f);
	mCamera->SetPerspective(CAMERA_FOV, (float)WINDOW_WIDTH / WINDOW_HEIGHT, CAMERA_NEAR, CAMERA_FAR);
	mCamera->SetLookAt(CAMERA_FROM, CAMERA_TO, CAMERA_UP);
}