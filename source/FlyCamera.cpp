#include "FlyCamera.h"


FlyCamera::FlyCamera(GLFWwindow* window)
{
	mWindow = window;
	Mouse::Init();
}

void FlyCamera::SetPerspective(const float fov, const float aspectRatio, const float near, const float far)
{
	mProjectionTransform = glm::perspective(fov, aspectRatio, near, far);
	UpdateProjectViewTransform();
}

void FlyCamera::SetRotationSpeed(const float rotSpeed)
{
	mRotSpeed = rotSpeed;
}


void FlyCamera::SetSpeed(const float speed)
{
	mSpeed = speed;
}

void FlyCamera::Rotate(float angle, glm::vec3 axis)
{
	mWorldTransform = glm::rotate(mWorldTransform, angle, axis);
	mViewTransform = glm::inverse(mWorldTransform);
	UpdateProjectViewTransform();
}

void FlyCamera::Translate(glm::vec3 distance)
{
	mWorldTransform = glm::translate(mWorldTransform, distance);
	mViewTransform = glm::inverse(mWorldTransform);
	UpdateProjectViewTransform();
}

void FlyCamera::Update(float deltaTime)
{
	glm::vec3 direction = glm::vec3(0);
	if (glfwGetKey(mWindow, GLFW_KEY_W) == GLFW_PRESS)
	{
		direction = glm::vec3(0, 0, -1);
	}
	else if (glfwGetKey(mWindow, GLFW_KEY_X) == GLFW_PRESS)
	{
		direction = glm::vec3(0, 0, 1);
	}
	else if (glfwGetKey(mWindow, GLFW_KEY_A) == GLFW_PRESS)
	{
		direction = glm::vec3(-1, 0, 0);
	}
	else if (glfwGetKey(mWindow, GLFW_KEY_D) == GLFW_PRESS)
	{
		direction = glm::vec3(1, 0, 0);
	}

	Translate(deltaTime * mSpeed * direction);

	if (Mouse::IsButtonPressed(Mouse::LEFT))
	{
		if (Mouse::GetPosDeltaX() != 0)
		{
			Rotate(glm::radians(deltaTime * mRotSpeed * Mouse::GetPosDeltaX()), glm::vec3(0, 1, 0));
		}
		if (Mouse::GetPosDeltaY() != 0)
		{
			Rotate(glm::radians(deltaTime * mRotSpeed * Mouse::GetPosDeltaY()), glm::vec3(1, 0, 0));
		}

	}

	std::cout << "x: " << Mouse::GetPrevPosX() << std::endl;
}