#include "Camera.h"

void Camera::Update(const float deltaTime)
{
}

void Camera::SetPerspective(const float fov, const float aspectRatio, const float near, const float far)
{
	mProjectionTransform = glm::perspective(fov, aspectRatio, near, far);
	mProjectionViewTransform = mProjectionTransform * mViewTransform;
}

void Camera::SetLookAt(const glm::vec3 from, const glm::vec3 to, const glm::vec3 up)
{
	mViewTransform = glm::lookAt(from, to, up);
	mWorldTransform = glm::inverse(mViewTransform);
}

void Camera::SetPosition(const glm::vec3 position)
{
	mWorldTransform = glm::translate(position);
	mViewTransform = glm::inverse(mWorldTransform);
}

const glm::mat4 Camera::GetWorldTransform()
{
	return mWorldTransform;
}

const glm::mat4 Camera::GetView()
{
	return glm::inverse(mWorldTransform);
}

const glm::mat4 Camera::GetProjection()
{
	return mProjectionTransform;
}

void Camera::UpdateProjectViewTransform()
{

}