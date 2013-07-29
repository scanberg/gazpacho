#include "Transform.h"

Transform::Transform() :
m_localPose(),
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

const mat4 & Transform::getPose()
{
	// REMOVE WHEN A GLOBAL UPDATE IS IN PLACE
	m_localPose = glm::scale(mat4(), m_scale);
	m_localPose = glm::mat4_cast(m_orientation) * m_localPose;
	m_localPose = glm::translate(m_localPose, m_position);

	return m_localPose;
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