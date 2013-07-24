#ifndef FRUSTUM_H
#define FRUSTUM_H

#include "Core.h"

class Frustum
{
public:
	Frustum(vec3 eyePos, f32 near, f32 far, vec3 * frame);
private:
	vec4 planes[6];
};

#endif