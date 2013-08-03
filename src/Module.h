#ifndef MODULE_H
#define MODULE_H

#include "Core.h"
#include "GameObject.h"
#include "Camera.h"
#include "Portal.h"

class Module
{
public:
	Module();
	~Module();
	
	const std::vector<GameObject*> & 	getStaticGameObjects();
	const std::list<GameObject*> & 		getDynamicGameObjects();
	const std::vector<Portal*> & 		getPortals();

	void addGameObject(GameObject * object);
	void removeGameObject(GameObject * object);

	void draw(Camera * camera);
	void drawWithoutPortals(Camera * camera = NULL);

private:
	std::vector<GameObject*> 	m_staticGameObjects;
	std::list<GameObject*>		m_dynamicGameObjects;
	
	std::vector<Portal*>		m_portals;
};

#endif