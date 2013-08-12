#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Core.h"

class Transform
{
public:
	Transform();
	~Transform();

	const quat & getOrientation() const;
	const vec3 & getPosition() const;
	const vec3 & getScale() const;

	mat4 getModelMatrix() const;
	mat4 getInvModelMatrix() const;

	mat4 getPose() const;
	mat4 getInvPose() const;

	void setPosition(const vec3 & position);
	void setOrientation(const quat & orientation);
	void setScale(const vec3 & scale);
	void setTransform(const mat4 & transform);
	
private:
	quat m_orientation;
	vec3 m_position;
	vec3 m_scale;
};

#endif