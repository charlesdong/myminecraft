#ifndef HITBOX_H_
#define HITBOX_H_

#include <glm/glm.hpp>

class AABB
{
public:
	double xmin;
	double xmax;
	double ymin;
	double ymax;
	double zmin;
	double zmax;

	AABB() : AABB(0.0, 0.0, 0.0, 0.0, 0.0, 0.0) { }

	AABB(double x1, double x2, double y1, double y2, double z1, double z2) :
		xmin(x1), xmax(x2), ymin(y1), ymax(y2), zmin(z1), zmax(z2) { }

	AABB expand(const glm::dvec3 & offset);
};

// Determine if two AABBs collide on the X axis.
inline bool collideX(const AABB & b1, const AABB & b2)
{
	//return b1.xmax > b2.xmin || b2.xmax > b1.xmin;
	return (b1.xmin <= b2.xmin && b1.xmax > b2.xmin) ||
		(b1.xmin > b2.xmin && b1.xmin < b2.xmax);
}

// Determine if two AABBs collide on the Y axis.
inline bool collideY(const AABB & b1, const AABB & b2)
{
	//return b1.ymax > b2.ymin || b2.ymax > b1.ymin;
	return (b1.ymin <= b2.ymin && b1.ymax > b2.ymin) ||
		(b1.ymin > b2.ymin && b1.ymin < b2.ymax);
}

// Determine if two AABBs collide on the Z axis.
inline bool collideZ(const AABB & b1, const AABB & b2)
{
	//return b1.zmax > b2.zmin || b2.zmax > b1.zmin;
	return (b1.zmin <= b2.zmin && b1.zmax > b2.zmin) ||
		(b1.zmin > b2.zmin && b1.zmin < b2.zmax);
}

// Determine if two AABBs collide.
inline bool collide(const AABB & b1, const AABB & b2)
{
	return collideX(b1, b2) && collideY(b1, b2) && collideZ(b1, b2);
}

// Maximum shift (absolute value) on X axis.
double maxShiftX(const AABB & obj, const AABB & bar, double delta);

// Maximum shift (absolute value) on Y axis.
double maxShiftY(const AABB & obj, const AABB & bar, double delta);

// Maximum shift (absolute value) on Z axis.
double maxShiftZ(const AABB & obj, const AABB & bar, double delta);

#endif