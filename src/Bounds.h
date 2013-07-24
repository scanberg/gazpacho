#ifndef BOUNDS_H
#define BOUNDS_H

#include "Core.h"
#include "Transform.h"

class Bounds
{
public:
	bool intersectBoundingBox(Bounds * ba, Transform * ta, Bounds * bb, Transform * tb);
	bool intersectBoundingSphere(Bounds * ba, Transform * ta, Bounds * bb, Transform * tb);
private:
	vec3 	m_min, m_max;
	f32		radius;
};

#endif