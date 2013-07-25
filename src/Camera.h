#ifndef CAMERA_H
#define CAMERA_H

#include "Core.h"

class Camera
{
public:
	f32 getFov();
	f32 getNearClip();
	f32 getFarClip();
	f32 getFocalDistance();
	f32 getFocalRange();

	void setFov(f32 fov);
	void setNearClip(f32 near);
	void setFarClip(f32 far);
	void setFocalDistance(f32 focalDist);
	void setFocalRange(f32 focalRange);

	void setupProjection(int width, int height);
private:
	mat4 m_projMatrix;
	f32 m_fov;
	f32 m_near;
	f32 m_far;
	f32 m_focalDistance;
	f32 m_focalRange;
};

#endif