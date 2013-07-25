#ifndef PORTAL_H
#define PORTAL_H

#include "Core.h"
#include "GameObject.h"
#include "Module.h"
#include "Frame.h"

class Portal : public GameObject
{
public:
	Portal * getTargetPortal();
	
	void setTargetPortal(Portal * portal);
private:
	Frame m_frame;
	bool m_mirror;

	GameObject * m_targetPortal;
};

#endif