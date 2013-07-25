#include "Frustum.h"

Frustum::Frustum(const vec3 & eyePos, const Frame & frame, f32 farClip)
{
	m_planes[TOP] 		= Plane(eyePos, frame.getPoint(TOPRIGHT), frame.getPoint(TOPLEFT));
	m_planes[BOTTOM]	= Plane(eyePos, frame.getPoint(BOTTOMLEFT), frame.getPoint(BOTTOMRIGHT));
	m_planes[LEFT]		= Plane(eyePos, frame.getPoint(TOPLEFT), frame.getPoint(BOTTOMLEFT));
	m_planes[RIGHT]		= Plane(eyePos, frame.getPoint(BOTTOMRIGHT), frame.getPoint(TOPRIGHT));
	m_planes[FRONT]		= Plane(frame.getPoint(BOTTOMLEFT), frame.getPoint(TOPRIGHT), frame.getPoint(TOPLEFT));
	m_planes[BACK]		= Plane(-1.0f * m_planes[FRONT].getNormal(), eyePos + (frame.getPoint(CENTER) - eyePos) * farClip);
}

const Plane & Frustum::getPlane(FrustumPlane plane) const
{
	assert(-1 < plane && plane < 6);
	return m_planes[plane];
}