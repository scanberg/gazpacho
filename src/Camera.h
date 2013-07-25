#ifndef CAMERA_H
#define CAMERA_H

#include "Core.h"
#include "GameObject.h"

class Camera : public GameObject
{
public:
	f32 getFov() const;
	f32 getNearClip() const;
	f32 getFarClip() const;
	f32 getFocalDistance() const;
	f32 getFocalRange() const;

	const mat4 & getProjMatrix() const;
	const mat4 & getViewMatrix() const;

	void setFov(f32 fov);
	void setNearClip(f32 near);
	void setFarClip(f32 far);
	void setFocalDistance(f32 focalDist);
	void setFocalRange(f32 focalRange);

	void setupProjection(int width, int height);
private:
	mat4 m_projMatrix;
	mat4 m_viewMatrix;

	f32 m_fov;
	f32 m_near;
	f32 m_far;
	f32 m_focalDistance;
	f32 m_focalRange;
};

#endif