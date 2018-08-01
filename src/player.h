#ifndef PLAYER_H_
#define PLAYER_H_

#include "aabb.h"
#include "world.h"
#include <glm/glm.hpp>
#include <vector>

class Player
{
private:
	// camera information
	glm::dvec3 position;
	glm::dvec3 frontInScene;
	glm::dvec3 front;
	glm::dvec3 up;
	double pitch;
	double yaw;

	// player's velocity in scalar

	double speed;
	double acceleration;
	glm::dvec3 velocity;

	bool flyModeEnabled;

	World * world;

	void adjustFront();
public:
	Player();
	void init(World * pWorld);
	void update();
	void move(const glm::dvec3 & deltaPos);

	const glm::dvec3 & getPosition() const { return position; }
	glm::dvec3 getEyePosition() const { return position + glm::dvec3(0.0, 1.6, 0.0); }	// TODO: MagNum
	glm::dvec3 getFrontInScene() const { return frontInScene; }
	glm::dvec3 getUp() const { return up; }
	glm::dvec3 getVelocity() const { return velocity; }
	double getPitch() const { return pitch; }
	double getYaw() const { return yaw; }
	AABB getHitbox() const
	{
		return AABB(
			position.x - 0.3,
			position.x + 0.3,
			position.y,
			position.y + 1.8,
			position.z - 0.3,
			position.z + 0.3
		);
	}
	bool isOnGround() const;
};

#endif