#include "Frustum.h"

Frustum::Frustum(const vec3 & eyePos, vec3 * corners, f32 farClip)
{
	m_planes[TOP] 		= Plane(eyePos, corners[1], corners[0]);
	m_planes[BOTTOM]	= Plane(eyePos, corners[2], corners[3]);
	m_planes[LEFT]		= Plane(eyePos, corners[0], corners[2]);
	m_planes[RIGHT]		= Plane(eyePos, corners[3], corners[1]);
	m_planes[FRONT]		= Plane(corners[2], corners[1], corners[0]);
	vec3 center 		= 0.25f * (corners[0] + corners[1] + corners[2] + corners[3]);
	m_planes[BACK]		= Plane(-1.0f * m_planes[FRONT].getNormal(), eyePos + (center - eyePos) * farClip);
}

const Plane & Frustum::getPlane(FrustumPlane plane) const
{
	assert(-1 < plane && plane < 6);
	return m_planes[plane];
}