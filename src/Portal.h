#ifndef PORTAL_H
#define PORTAL_H

#include "Core.h"
#include "Module.h"

class Portal
{
public:
	Portal * getTargetPortal();
	Module * getOwnerModule();
	
	void setTargetPortal(Portal * portal);
private:
	vec3 m_frame[4];
	bool m_mirror;

	Module * m_ownerModule;
	Portal * m_targetPortal;
};

#endif