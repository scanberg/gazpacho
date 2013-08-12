#ifndef PORTAL_H
#define PORTAL_H

#include "Core.h"
#include "GameObject.h"

enum PortalCorner { TOPLEFT, TOPRIGHT, BOTTOMLEFT, BOTTOMRIGHT };

class Portal : public GameObject
{
public:
	static void init();
	static void cleanup();
	
	Portal(f32 width, f32 height, Portal * targetPortal = NULL);
	~Portal();

	bool 			isMirror() const;

	Portal * 		getTargetPortal() const;
	vec3			getPortalCorner(PortalCorner corner) const;
	Plane 			getPlane() const;

	mat4			getViewMatrix(Camera * cam) const;
	mat4			getInvViewMatrix(Camera * cam) const;
	
	void 			setTargetPortal(Portal * portal);

	void draw(Camera * cam);
private:
	static Mesh * m_quad;
	Portal * m_targetPortal;
};

#endif