#include "player.h"
#include "game.h"
#include <glm/glm.hpp>
#include <cstdio>

Player::Player() : position(0.5, 5.0, 0.5), frontInScene(0.0, 0.0, 1.0), front(0.0, 0.0, 1.0), up(0.0, 1.0, 0.0), pitch(0.0), yaw(90.0), velocity(0.0, 0.0, 0.0), speed(3.0), acceleration(8.0), flyModeEnabled(false)
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

	static bool spacePressed = false;
	static bool f1Pressed = false;
	velocity.x = 0.0;
	velocity.z = 0.0;

	if (pGame->isKeyDown(GLFW_KEY_F1))
	{
		if (!f1Pressed)
		{
			flyModeEnabled = !flyModeEnabled;
			f1Pressed = true;
		}
	}
	else
		f1Pressed = false;
	if (pGame->isKeyDown(GLFW_KEY_A))
		velocity -= glm::cross(front, up) * speed;
	if (pGame->isKeyDown(GLFW_KEY_D))
		velocity += glm::cross(front, up) * speed;
	if (pGame->isKeyDown(GLFW_KEY_W))
		velocity += front * speed;
	if (pGame->isKeyDown(GLFW_KEY_S))
		velocity -= front * speed;
	if (pGame->isKeyDown(GLFW_KEY_SPACE))
	{
		if (!flyModeEnabled)
		{
			if (!spacePressed && isOnGround())
			{
				spacePressed = true;
				velocity.y = 4.0;	// TODO: MN
			}
		}
		else
			velocity.y = 6.0;	// TODO: MN
	}
	else
	{
		spacePressed = false;
		if (flyModeEnabled)
			velocity.y = 0.0;
	}

	if (!isOnGround() && !flyModeEnabled)
		velocity.y -= acceleration * deltaTime;

	move(velocity * deltaTime);

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
	else if (pitch < -89.9)
		pitch = -89.9;
	
	if (yaw > 360.0)
		yaw -= 360.0;
	else if (yaw < 0.0)
		yaw += 360.0;

	//printf("vy: %lf\n", velocity.y);

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

	if (deltaPos.y < 0.0 && shift.y + shiftLeftFinal.y == 0.0)
		velocity.y = 0.0;
}

bool Player::isOnGround() const
{
	AABB hitbox = getHitbox();
	for (double x = floor(hitbox.xmin); x <= floor(hitbox.xmax); x += 1.0)
		for (double z = floor(hitbox.zmin); z <= floor(hitbox.zmax); z += 1.0)
			if (world->hasBlock((long)x, (long)ceil(position.y) - 1L, (long)z))
				return true;
	return false;
}