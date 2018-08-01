#include "aabb.h"

AABB AABB::expand(const glm::dvec3 & offset) const
{
	AABB result(*this);
	if (offset.x >= 0.0)
		result.xmax += offset.x;
	else
		result.xmin += offset.x;	// NOTE: offset.x is negative now, so it should be '+='
	if (offset.y >= 0.0)
		result.ymax += offset.y;
	else
		result.ymin += offset.y;
	if (offset.z >= 0.0)
		result.zmax += offset.z;
	else
		result.zmin += offset.z;
	return result;
}

double maxShiftX(const AABB & obj, const AABB & bar, double delta)
{
	if (!collideY(obj, bar) || !collideZ(obj, bar))
		return delta;
	if (delta > 0.0 && obj.xmax + delta > bar.xmin)
		return bar.xmin - obj.xmax;
	else if (delta < 0.0 && obj.xmin + delta < bar.xmax)
		return bar.xmax - obj.xmin;
	return delta;
}

double maxShiftY(const AABB & obj, const AABB & bar, double delta)
{
	if (!collideX(obj, bar) || !collideZ(obj, bar))
		return delta;
	if (delta > 0.0 && obj.ymax + delta > bar.ymin)
		return bar.ymin - obj.ymax;
	else if (delta < 0.0 && obj.ymin + delta < bar.ymax)
		return bar.ymax - obj.ymin;
	return delta;
}

double maxShiftZ(const AABB & obj, const AABB & bar, double delta)
{
	if (!collideX(obj, bar) || !collideY(obj, bar))
		return delta;
	if (delta > 0.0 && obj.zmax + delta > bar.zmin)
		return bar.zmin - obj.zmax;
	else if (delta < 0.0 && obj.zmin + delta < bar.zmax)
		return bar.zmax - obj.zmin;
	return delta;
}