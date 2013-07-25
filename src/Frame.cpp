#include "Frame.h"

Frame::Frame(vec3 topLeft, vec3 topRight, vec3 bottomLeft, vec3 bottomRight)
{
	m_points[0] 		= topLeft;
	m_points[1] 		= topRight;
	m_points[BOTTOMLEFT] 	= bottomLeft;
	m_points[BOTTOMRIGHT] 	= bottomRight;
	m_points[CENTER] 		= 0.25f * (topLeft + topRight + bottomLeft + bottomRight);
}

const vec3 & Frame::getPoint(FramePoint point) const
{
	assert(-1 < point && point < 4);
	return m_points[point];
}