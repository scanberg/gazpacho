#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Core.h"

class Transform
{
public:
	const quat & getOrientation();
	const vec3 & getEulerAngles();
	const vec3 & getPosition();
	const vec3 & getScale();

	void setPosition(const vec3 & p);
	void setPosition(const vec4 & p);

	void setOrientation(const quat & q);
	void setOrientationEuler(const vec3 & e);

	void setScale(const vec3 & s);

private:
	quat m_quaternion;
	vec3 m_position;
	vec3 m_scale;
};

#endif