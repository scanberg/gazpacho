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

	mat4 getModelMatrix();
	mat4 getInvModelMatrix();

	mat4 getPose();
	mat4 getInvPose();

	void setPosition(const vec3 & position);
	void setOrientation(const quat & orientation);
	void setScale(const vec3 & scale);
	
private:
	quat m_orientation;
	vec3 m_position;
	vec3 m_scale;
};

#endif