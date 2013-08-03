#include "Module.h"
#include "Model.h"

Module::Module()
{

}

Module::~Module()
{

}

const std::vector<GameObject*> & Module::getStaticGameObjects()
{
	return m_staticGameObjects;
}

const std::list<GameObject*> & Module::getDynamicGameObjects()
{
	return m_dynamicGameObjects;
}

const std::vector<Portal*> & Module::getPortals()
{
	return m_portals;
}

void Module::addGameObject(GameObject * object)
{
	if(object)
	{
		if(object->getType() == PORTAL)
			m_portals.push_back((Portal*)object);
		else
		{
			if(object->isStatic())
				m_staticGameObjects.push_back(object);
			else
				m_dynamicGameObjects.push_back(object);
		}

		object->setOwnerModule(this);
	}
}

void Module::removeGameObject(GameObject * object)
{

}

void Module::draw(Camera * camera)
{
	std::list<Model*> renderList;

	for(u32 i=0; i<m_staticGameObjects.size(); ++i)
	{
		if(m_staticGameObjects[i]->getType() == MODEL)
		{
			Model * model = (Model*)m_staticGameObjects[i];
			renderList.push_back(model);
		}
	}

	for(std::list<GameObject*>::iterator it=m_dynamicGameObjects.begin();
		it != m_dynamicGameObjects.end();
		++it)
	{
		if((*it)->getType() == MODEL)
		{
			Model * model = (Model*)(*it);
			renderList.push_back(model);
		}
	}

	for(std::list<Model*>::iterator it = renderList.begin();
		it != renderList.end();
		++it)
	{
		(*it)->draw();
	}

	for(u32 i=0; i<m_portals.size(); ++i)
	{
		m_portals[i]->draw(camera);
	}

}

void Module::drawWithoutPortals(Camera * camera)
{
	std::list<Model*> renderList;

	for(u32 i=0; i<m_staticGameObjects.size(); ++i)
	{
		if(m_staticGameObjects[i]->getType() == MODEL)
		{
			Model * model = (Model*)m_staticGameObjects[i];
			renderList.push_back(model);
		}
	}

	for(std::list<GameObject*>::iterator it=m_dynamicGameObjects.begin();
		it != m_dynamicGameObjects.end();
		++it)
	{
		if((*it)->getType() == MODEL)
		{
			Model * model = (Model*)(*it);
			renderList.push_back(model);
		}
	}

	for(std::list<Model*>::iterator it = renderList.begin();
		it != renderList.end();
		++it)
	{
		(*it)->draw();
	}
}