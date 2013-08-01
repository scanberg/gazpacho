#ifndef BOUNDS_H
#define BOUNDS_H

#include "Core.h"
#include "Transform.h"

class Bounds
{
public:
	Bounds()
	{}
	Bounds(vec3 min, vec3 max, f32 radius) :
	m_min(min),
	m_max(max),
	m_radius(radius)
	{}

	const vec3 & getMin() { return m_min; }
	const vec3 & getMax() { return m_max; }
	const f32 & getRadius() { return m_radius;}

	void drawBB()
	{
		GLfloat vertices[] = { 	m_min.x,m_min.y,m_min.z,
								m_min.x,m_max.y,m_min.z,
								m_max.x,m_max.y,m_min.z,
								m_max.x,m_min.y,m_min.z,

								m_max.x,m_min.y,m_max.z,
								m_min.x,m_min.y,m_max.z,
								m_min.x,m_max.y,m_max.z,
								m_max.x,m_max.y,m_max.z
								 };     // 8 of vertex coords

		GLubyte indices[] = {0,1,2,3,   // 24 of indices
		                     0,3,4,5,
		                     0,5,6,1,
		                     1,6,7,2,
		                     7,4,3,2,
		                     4,7,6,5};

		// activate and specify pointer to vertex array
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, vertices);

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glColor3f(1.0f,1.0f,0.0f);

		// draw a cube
		glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indices);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		// deactivate vertex arrays after drawing
		glDisableClientState(GL_VERTEX_ARRAY);

	}
private:
	vec3 	m_min, m_max;
	f32		m_radius;
};

#endif