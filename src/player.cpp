#include "player.h"
#include "game.h"
#include <glm/glm.hpp>
#include <cstdio>

Player::Player() : position(0.0, 0.0, -5.0), frontInScene(0.0, 0.0, 1.0), front(0.0, 0.0, 1.0), up(0.0, 1.0, 0.0), pitch(0.0), yaw(90.0), velocity(3.0)
{
}

void Player::init(World * pWorld)
{
	world = pWorld;
}

void Player::update()
{
	double deltaTime = pGame->getDeltaTime();

	// Process key input.

	glm::dvec3 deltaPos;

	if (pGame->isKeyDown(GLFW_KEY_A))
		deltaPos -= glm::cross(front, up) * velocity * deltaTime;
	if (pGame->isKeyDown(GLFW_KEY_D))
		deltaPos += glm::cross(front, up) * velocity * deltaTime;
	if (pGame->isKeyDown(GLFW_KEY_W))
		deltaPos += front * velocity * deltaTime;
	if (pGame->isKeyDown(GLFW_KEY_S))
		deltaPos -= front * velocity * deltaTime;
	if (pGame->isKeyDown(GLFW_KEY_UP))
		deltaPos += up * velocity * deltaTime;
	if (pGame->isKeyDown(GLFW_KEY_DOWN))
		deltaPos -= up * velocity * deltaTime;

	move(deltaPos);

	// Process cursor movement.

	static glm::dvec2 curPosLast = pGame->getCursorPos();
	glm::dvec2 curPosCur = pGame->getCursorPos();

	double xOff = curPosCur.x - curPosLast.x;
	double yOff = curPosLast.y - curPosCur.y;	// NOTE: yOff needs to be inversed because the origin of the screen coordinates is at the left-top corner

	curPosLast = curPosCur;

	const double sensitivity = 0.2;
	yaw += xOff * sensitivity;
	pitch += yOff * sensitivity;

	// Prevent the sudden jump of view.
	if (pitch > 89.9)
		pitch = 89.9;
	if (pitch < -89.9)
		pitch = -89.9;

	adjustFront();
}

void Player::adjustFront()
{
	frontInScene.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	frontInScene.y = sin(glm::radians(pitch));
	frontInScene.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.x = frontInScene.x;
	front.y = 0.0;
	front.z = frontInScene.z;
	front = glm::normalize(front);
}

void Player::move(const glm::dvec3 & deltaPos)
{
	AABB hitbox = getHitbox();
	AABB hitboxExpanded = getHitbox().expand(deltaPos);
	std::vector<AABB> hitboxes = world->getHitboxes(hitboxExpanded);

	glm::dvec3 shift = deltaPos;

	for (const AABB & block : hitboxes)
	{
		double shiftX = maxShiftX(hitbox, block, shift.x);
		if (abs(shiftX) / abs(shift.x) < 1.0)
		{
			shift.y *= shiftX / shift.x;
			shift.z *= shiftX / shift.x;
			shift.x = shiftX;
		}

		double shiftY = maxShiftY(hitbox, block, shift.y);
		if (abs(shiftY) / abs(shift.y) < 1.0)
		{
			shift.x *= shiftY / shift.y;
			shift.z *= shiftY / shift.y;
			shift.y = shiftY;
		}

		double shiftZ = maxShiftZ(hitbox, block, shift.z);
		if (abs(shiftZ) / abs(shift.z) < 1.0)
		{
			shift.x *= shiftZ / shift.z;
			shift.y *= shiftZ / shift.z;
			shift.z = shiftZ;
		}
	}

	position += shift;

	glm::dvec3 shiftLeft = deltaPos - shift;
	glm::dvec3 shiftLeftTemp = shiftLeft;
	glm::dvec3 shiftLeftFinal = shiftLeft;
	AABB hitboxNew = getHitbox();
	AABB hitboxExpandedNew = getHitbox().expand(shiftLeft);
	std::vector<AABB> hitboxesNew = world->getHitboxes(hitboxExpandedNew);
	for (const AABB & block : hitboxesNew)
	{
		shiftLeftTemp.x = maxShiftX(hitboxNew, block, shiftLeftFinal.x);
		if (abs(shiftLeftTemp.x) / abs(shiftLeftFinal.x) <= 1.0)
			shiftLeftFinal.x = shiftLeftTemp.x;

		shiftLeftTemp.y = maxShiftY(hitboxNew, block, shiftLeftFinal.y);
		if (abs(shiftLeftTemp.y) / abs(shiftLeftFinal.y) <= 1.0)
			shiftLeftFinal.y = shiftLeftTemp.y;

		shiftLeftTemp.z = maxShiftZ(hitboxNew, block, shiftLeftFinal.z);
		if (abs(shiftLeftTemp.z) / abs(shiftLeftFinal.z) <= 1.0)
			shiftLeftFinal.z = shiftLeftTemp.z;
	}

	position += shiftLeftFinal;
}