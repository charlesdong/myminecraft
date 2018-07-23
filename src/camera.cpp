#include "camera.h"
#include "game.h"
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <iostream>
using std::cout;

const double Camera::Velocity = 3.0;

Camera::Camera() : eyePosition(0.0, 3.0, -5.0), front(0.0, 0.0, 1.0), up(0.0, 1.0, 0.0), pitch(0.0), yaw(90.0)
{
}

void Camera::update()
{
	static double timeLast = 0.0;
	static double timeCur;
	timeCur = glfwGetTime();
	double timeDelta = timeCur - timeLast;
	timeLast = timeCur;

	// process keys

	if (pGame->isKeyDown(GLFW_KEY_A))
		eyePosition -= glm::cross(front, up) * Velocity * timeDelta;
	if (pGame->isKeyDown(GLFW_KEY_D))
		eyePosition += glm::cross(front, up) * Velocity * timeDelta;
	if (pGame->isKeyDown(GLFW_KEY_W))
		eyePosition += front * Velocity * timeDelta;
	if (pGame->isKeyDown(GLFW_KEY_S))
		eyePosition -= front * Velocity * timeDelta;
	if (pGame->isKeyDown(GLFW_KEY_UP))
		eyePosition += up * Velocity * timeDelta;
	if (pGame->isKeyDown(GLFW_KEY_DOWN))
		eyePosition -= up * Velocity * timeDelta;

	// process cursor movements

	static glm::dvec2 curPosLast = pGame->getCursorPos();
	glm::dvec2 curPosCur = pGame->getCursorPos();

	double xOff = curPosCur.x - curPosLast.x;
	double yOff = curPosLast.y - curPosCur.y;	// NOTE: yOff needs to be inversed because the origin of the screen coordinates is at the left-top corner

	curPosLast = curPosCur;

	const double sensitivity = 0.2;
	yaw += xOff * sensitivity;
	pitch += yOff * sensitivity;

	// prevent the sudden jump of view
	if (pitch > 89.9)
		pitch = 89.9;
	if (pitch < -89.9)
		pitch = -89.9;

	adjustFront();
}

void Camera::render() const
{
}

void Camera::adjustFront()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
}