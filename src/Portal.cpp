#include "Portal.h"

Portal::Portal(f32 width, f32 height, Portal * m_targetPortal)
{
	assert(width > 0);
	assert(height > 0);

	f32 half_width = width * 0.5f;
	f32 half_height = height * 0.5f;

	vec3 min = vec3(-half_width, -half_height, 0.0f);
	vec3 max = vec3(half_width, half_height, 0.0f);
	f32 radius = length(max);

	m_bounds = Bounds(min, max, radius);
}

Portal::~Portal()
{
	
}

Portal * Portal::getTargetPortal()
{
	return m_targetPortal;
}

const vec3 & Portal::getMin()
{
	return m_bounds.getMin();
}

const vec3 & Portal::getMax()
{
	return m_bounds.getMax();
}

void Portal::setTargetPortal(Portal * portal)
{
	m_targetPortal = portal;
}