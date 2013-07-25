#ifndef PLANE_H
#define PLANE_H

#include "Core.h"

class Plane
{
public:
	Plane();
	Plane(vec3 normal, f32 dist);
	Plane(vec4 normAndDist);
	Plane(vec3 normal, vec3 point);
	Plane(const vec3 &a, const vec3 &b, const vec3 &c);

	f32 signedDistance(const vec3 &coord);
	f32 signedDistance(const vec4 &hcoord);

	vec3		 	getNormal();
	const f32 &		getDistance();
	const vec4 &	getVec4();

private:
	vec4 m_data;
};

#endif