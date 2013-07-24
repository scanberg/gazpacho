#ifndef MODULE_H
#define MODULE_H

#include "Core.h"
#include "GameObject.h"

class Module
{
public:
	const Array & getStaticGameObjects();
	const List & getDynamicGameObjects();

	const Array & getPortals();
private:
	Array 	m_staticGameObjects;
	List	m_dynamicGameObjects;
	
	Array	m_portals;
};

#endif