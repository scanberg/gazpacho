#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Core.h"

class GameObject
{
public:
	bool intersect(GameObject * other);
private:
	bool 		m_static;
	Transform * m_transform;
	Bounds *	m_bounds;
	Mesh * 		m_mesh;
	Material * 	m_material;
	Skeleton * 	m_skeleton;

};