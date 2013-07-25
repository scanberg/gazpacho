#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Core.h"

class GameObject
{
public:
	bool 		isStatic();
	Module * 	getOwnerModule();

private:
	bool 		m_static;
	Module *	m_ownerModule;
	Transform * m_transform;
	Bounds *	m_bounds;
	Mesh * 		m_mesh;
	Material * 	m_material;
	Skeleton * 	m_skeleton;
	Camera * 	m_camera;
};