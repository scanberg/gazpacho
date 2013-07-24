#ifndef PLANE_H
#define PLANE_H

#include "Core.h"

class Plane
{
public:
	Plane(vec3 normal, f32 dist) :
	m_data(vec4(normalize(normal), dist))
	{}

	Plane(vec4 normAndDist) :
	m_data(normAndDist)
	{}

	Plane(const vec3 &a, const vec3 &b, const vec3 &c)
	{
		
	}

	inline const vec3 & getNormal() { return m_data.xyz(); }
	inline const f32 &	getDistance() { return m_data[3]; }
	inline const vec4 &	getVec4() { return m_data; }

private:
	vec4 m_data;
};