#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Core.h"
#include "Transform.h"
#include "Bounds.h"
#include "Module.h"

class GameObject
{
public:
	bool 				isStatic();
	const Transform & 	getTransform();
	const Bounds & 		getBounds();

	Module * 	getOwnerModule();
protected:
	GameObject();
	virtual ~GameObject();

	bool 		m_static;
	Transform 	m_transform;
	Bounds 		m_bounds;

	Module *	m_ownerModule;

	u32 		m_ID;
};

#endif