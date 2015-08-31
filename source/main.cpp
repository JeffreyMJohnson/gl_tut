#include <gl_core_4_4.h>
#include <GLFW\glfw3.h>
#include <iostream>

#include <aie\Gizmos.h>
#include <glm\glm.hpp>
#include <glm\ext.hpp>
#include <glm\gtx\transform.hpp>

#include "Timer.h"

using glm::vec3;
using glm::vec4;
using glm::mat4;

const vec4 WHITE = vec4(1);
const vec4 BLACK = vec4(0, 0, 0, 1);
const vec4 WIRE_FRAME = vec4(0);

void main()
{
	if (glfwInit() == false)
	{
		return;
	}

	GLFWwindow* window = glfwCreateWindow(1280, 720, "Computer Graphics", nullptr, nullptr);

	if (nullptr == window)
	{
		glfwTerminate();
		return;
	}


	glfwMakeContextCurrent(window);

	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		return;
	}

	Gizmos::create();

	mat4 view = glm::lookAt(vec3(10, 10, 10), vec3(0), vec3(0, 1, 0));
	mat4 projection = glm::perspective(glm::pi<float>() * .25f, 16 / 9.f, .1f, 1000.f);

	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();
	printf("GL: %i.%i\n", major, minor);

	glClearColor(.25f, .25f, .25f, 1);
	glEnable(GL_DEPTH_TEST);


	Timer timer = Timer();
	


	
	


	while (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
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

		//Gizmos::addSphere(vec3(0, .5f, 0), 1.0f, 100, 100, vec4(.25f, .25f, .25f, 1));
		timer.Update(glfwGetTime());

		mat4 sunOrbit = mat4(1);
		mat4 earthOrbit = sunOrbit * glm::rotate(timer.CurrentTime, vec3(0,1,0)) * glm::translate(vec3(0,0,4));
		mat4 moonOrbit = earthOrbit * glm::rotate(timer.CurrentTime, vec3(0, 1, 0)) * glm::translate(vec3(0, 0, 1));

		mat4 sunLocal, earthLocal, moonLocal;
		earthLocal = glm::scale(vec3(.8f));
		moonLocal = glm::scale(vec3(.1f));
		sunLocal = glm::rotate(timer.CurrentTime, vec3(0, 1, 0));
		

		Gizmos::addSphere(vec3(), 1, 20, 20, WIRE_FRAME, &(sunOrbit * sunLocal));
		Gizmos::addSphere(vec3(), 1, 20, 20, WIRE_FRAME, &(earthOrbit * earthLocal));
		Gizmos::addSphere(vec3(), 1, 20, 20, WIRE_FRAME, &(moonOrbit * moonLocal));

		Gizmos::draw(projection * view);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}




	Gizmos::destroy();
	glfwDestroyWindow(window);
	glfwTerminate();
	return;
}