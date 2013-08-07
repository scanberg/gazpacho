#ifndef PORTAL_H
#define PORTAL_H

#include "Core.h"
#include "GameObject.h"

class Portal : public GameObject
{
public:
	static void init();
	static void cleanup();
	
	Portal(f32 width, f32 height, Portal * targetPortal = NULL);
	~Portal();

	bool 			isMirror();

	Portal * 		getTargetPortal();
	const vec3 & 	getMin();
	const vec3 &	getMax();
	Plane 			getPlane();
	
	void 			setTargetPortal(Portal * portal);

	void draw(Camera * cam);
private:
	static Mesh * m_quad;
	Portal * m_targetPortal;
};

#endif