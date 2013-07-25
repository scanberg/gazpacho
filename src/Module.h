#ifndef MODULE_H
#define MODULE_H

#include "Core.h"
#include "GameObject.h"

class Module
{
public:
	const Array & getStaticGameObjects();
	const List 	& getDynamicGameObjects();
	const Array & getPortals();

	void addDynamicGameObject(GameObject * object);

private:
	Array<GameObject> 	m_staticGameObjects;
	List<GameObject>	m_dynamicGameObjects;
	
	Array<GameObject>	m_portals;
};

#endif