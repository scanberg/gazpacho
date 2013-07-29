#ifndef PORTAL_H
#define PORTAL_H

#include "Core.h"
#include "GameObject.h"
#include "Module.h"

class Portal : public GameObject
{
public:
	Portal(f32 width, f32 height, Portal * m_targetPortal = NULL);
	~Portal();

	Portal * 		getTargetPortal();
	const vec3 & 	getMin();
	const vec3 &	getMax();
	
	void 			setTargetPortal(Portal * portal);
private:
	Portal * m_targetPortal;
};

#endif