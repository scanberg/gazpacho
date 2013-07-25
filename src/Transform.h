#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Core.h"

class Transform
{
public:
	Transform();
	~Transform();

	const quat & getOrientation();
	const vec3 & getPosition();
	const vec3 & getScale();
	const mat4 & getPose();

	void setPosition(const vec3 & p);
	void setOrientation(const quat & q);
	void setScale(const vec3 & s);
	
private:
	mat4 m_localPose;
	quat m_quaternion;
	vec3 m_position;
	vec3 m_scale;
};

#endif