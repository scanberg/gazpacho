#include "Transform.h"

Transform::Transform() :
m_orientation(),
m_position(),
m_scale(vec3(1.0))
{

}

Transform::~Transform()
{

}

const quat & Transform::getOrientation()
{
	return m_orientation;
}

const vec3 & Transform::getPosition()
{
	return m_position;
}

const vec3 & Transform::getScale()
{
	return m_scale;
}

mat4 Transform::getModelMatrix()
{
	// REMOVE WHEN A GLOBAL UPDATE IS IN PLACE, OR?
	mat4 pose;
	pose = 	glm::translate(mat4(), m_position) *
			glm::mat4_cast(m_orientation) *
			glm::scale(mat4(), m_scale);
	return pose;
}


mat4 Transform::getInvModelMatrix()
{
	mat4 pose;
	pose = 	glm::scale(mat4(), 1.0f/m_scale) *
	glm::mat4_cast(glm::conjugate(m_orientation)) *
	glm::translate(mat4(), -m_position);
	return pose;
}

mat4 Transform::getPose()
{
	// REMOVE WHEN A GLOBAL UPDATE IS IN PLACE, OR?
	mat4 pose;
	pose = 	glm::translate(mat4(), m_position) *
			glm::mat4_cast(m_orientation);
	return pose;
}

mat4 Transform::getInvPose()
{
	mat4 pose;
	pose = 	glm::mat4_cast(glm::conjugate(m_orientation)) *
			glm::translate(mat4(), -m_position);
	return pose;
}

void Transform::setPosition(const vec3 & position)
{
	m_position = position;
}

void Transform::setOrientation(const quat & orientation)
{
	m_orientation = orientation;
}

void Transform::setScale(const vec3 & scale)
{
	m_scale = scale;
}