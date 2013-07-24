#ifndef BOUNDS_H
#define BOUNDS_H

#include "Core.h"
#include "Transform.h"

class Bounds
{
public:
	Bounds(vec3 min, vec3 max, f32 radius) :
	m_min(min),
	m_max(max),
	m_radius(radius)
	{}

	const vec3 & getMin() { return m_min; }
	const vec3 & getMax() { return m_max; }
	const f32 & getRadius() { return m_radius;}
private:
	vec3 	m_min, m_max;
	f32		m_radius;
};

#endif