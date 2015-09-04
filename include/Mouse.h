#pragma once
#include <GLFW\glfw3.h>


class Mouse
{

	static double X_SCROLL, Y_SCROLL;
	static double X_POS, Y_POS;

	static void scroll_callback(GLFWwindow *w, double x, double y) { X_SCROLL = x; Y_SCROLL = y; }
	static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
	{
		X_POS = xpos;
		Y_POS = ypos;
	}
public:
	
	static void Init()
	{
		glfwSetScrollCallback(glfwGetCurrentContext(), scroll_callback);
		glfwSetCursorPosCallback(glfwGetCurrentContext(), cursor_pos_callback);
	}

	static double getScrollX() { return X_SCROLL; }


};