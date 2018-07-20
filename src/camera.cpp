#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

const double Camera::Velocity = 3.0;

Camera::Camera() : eyePosition(0.0, 3.0, -5.0), front(0.0, 0.0, 1.0), up(0.0, 1.0, 0.0), pitch(0.0), yaw(90.0)
{
}

void Camera::update()
{
}

void Camera::render() const
{
}

void Camera::move(Direction d)
{
	switch (d)
	{
	case LEFT:
		eyePosition -= glm::cross(front, up) * Velocity * timeDelta;
		break;
	case RIGHT:
		eyePosition += glm::cross(front, up) * Velocity * timeDelta;
		break;
	case FRONT:
		eyePosition += front * Velocity * timeDelta;
		break;
	case BACK:
		eyePosition -= front * Velocity * timeDelta;
		break;
	case UP:
		eyePosition += up * Velocity * timeDelta;
		break;
	case DOWN:
		eyePosition -= up * Velocity * timeDelta;
		break;
	}
}

void Camera::newFrame()
{
	static double timeLast = 0.0f;
	static double timeCur;
	timeCur = glfwGetTime();
	timeDelta = timeCur - timeLast;
	timeLast = timeCur;
}