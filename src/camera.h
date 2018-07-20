#ifndef CAMERA_H_
#define CAMERA_H_

#include <glm/glm.hpp>

enum Direction { LEFT, RIGHT, FRONT, BACK, UP, DOWN };

class Camera
{
private:
	glm::dvec3 eyePosition;
	glm::dvec3 front;
	glm::dvec3 up;
	double pitch;
	double yaw;
	double timeDelta;

	static const double Velocity;
public:
	Camera();
	void update();
	void render() const;
	void move(Direction d);
	void newFrame();

	const glm::dvec3 & getEyePos() const
	{
		return eyePosition;
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