#include "Frame.h"

Frame::Frame(vec3 topLeft, vec3 topRight, vec3 bottomLeft, vec3 bottomRight) :
m_points[TOPLEFT](topLeft),
m_points[TOPRIGHT](topRight),
m_points[BOTTOMLEFT](bottomLeft),
m_points[BOTTOMRIGHT](bottomRight)
{}

const vec3 & Frame::getPoint(FramePoint point)
{
	assert(-1 < point && point < 4);
	return m_points[point];
}