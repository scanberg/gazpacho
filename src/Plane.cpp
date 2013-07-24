#include "Plane.h"

Plane::Plane(vec3 normal, f32 dist) :
m_data(vec4(normalize(normal), dist))
{}

Plane::Plane(vec4 normAndDist) :
m_data(normAndDist)
{}

Plane::Plane(vec3 normal, vec3 point)
{
	normal = normalize(normal);
	f32 distance = dot(normal, point);

	m_data = vec4(normal, distance);
}

Plane::Plane(const vec3 &a, const vec3 &b, const vec3 &c)
{
	vec3 A = b-a;
	vec3 B = c-a;
	assert(dot(A,B) > EPSILON);

	vec3 normal = normalize(cross(b-a,c-a));
	f32 distance = dot(normal, a);

	m_data = vec4(normal, distance);
}

f32 Plane::signedDistance(const vec3 &coord)
{
	return dot(m_data, vec4(point, 1.0f));
}
f32 Plane::signedDistance(const vec4 &hcoord)
{
	return dot(m_data, hcoord);
}

const vec3 & 	Plane::getNormal()
{
	return m_data.xyz();
}

const f32 &		Plane::getDistance()
{
	return m_data[3];
}
const vec4 & 	Plane::getVec4()
{
	return m_data;
}