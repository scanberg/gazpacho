#ifndef FRAME_H
#define FRAME_H

#include "Core.h"

enum FramePoint { TOPLEFT = 0, TOPRIGHT, BOTTOMLEFT, BOTTOMRIGHT, CENTER };

class Frame
{
public:
	Frame(vec3 topLeft, vec3 topRight, vec3 bottomLeft, vec3 bottomRight);

	const vec3 & getPoint(FramePoint point) const;
private:
	vec3 m_points[5];
};

#endif