#ifndef FRUSTUM_H
#define FRUSTUM_H

#include "Core.h"
#include "Plane.h"

enum FrustumPlane { TOP, BOTTOM, LEFT, RIGHT, FRONT, BACK };

class Frustum
{
public:
	Frustum(const vec3 & eyePos, vec3 * corners, f32 farClip);
	const Plane &getPlane(FrustumPlane plane) const;

private:
	Plane m_planes[6];
};

#endif