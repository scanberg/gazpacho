#ifndef MODULE_H
#define MODULE_H

#include "Core.h"
#include "GameObject.h"

class Module
{
public:
	Module();
	//Module(const Array<GameObject*> & staticGameObjects, const Array<GameObject*> & dynamicGameObjects);
	const std::vector<GameObject*> & getStaticGameObjects();
	const std::list<GameObject*> & getDynamicGameObjects();
	const std::vector<GameObject*> & getPortals();

	void addDynamicGameObject(GameObject * object);

private:
	std::vector<GameObject*> 	m_staticGameObjects;
	std::list<GameObject*>		m_dynamicGameObjects;
	
	std::vector<GameObject*>	m_portals;
};

#endif