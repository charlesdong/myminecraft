#ifndef CAMERA_H_
#define CAMERA_H_

#include <glm/glm.hpp>

class Camera
{
private:
	glm::dvec3 eyePosition;
	glm::dvec3 front;
	glm::dvec3 up;
	double pitch;
	double yaw;

	static const double Velocity;

	void adjustFront();
public:
	Camera();
	void update();
	void render() const;

	const glm::dvec3 & getEyePos() const
	{
		return eyePosition;
	}

	glm::dvec3 getPlayerPos() const
	{
		return eyePosition - glm::dvec3(0.0, 1.6, 0.0);
	}

	const glm::dvec3 & getFront() const
	{
		return front;
	}

	const glm::dvec3 & getUp() const
	{
		return up;
	}
};

#endif