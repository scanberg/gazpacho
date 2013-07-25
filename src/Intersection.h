#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "Transform.h"
#include "Bounds.h"
#include "Frustum.h"

bool intersectBoxBox(	Transform * tboxA,
						Bounds * boxA,
						Transform * tboxB,
						Bounds * boxB);

bool intersectBoxSphere(Transform * tbox,
						Bounds * box,
						Transform * tsphere,
						Bounds * sphere);

bool intersectSphereSphere(	Transform * tsphereA,
							Bounds * sphereA,
							Transform * tsphereB,
							Bounds * sphereB);

bool intersectBoxFrustum(	Transform * tbox,
							Bounds * box,
							Transform * tfrustum,
							Frustum * frustum);

bool intersectFrustumPoint(	Transform * tfrustum,
							Frustum * frustum,
							const vec3 & point);

bool intersectFrustumSphere(Transform * tfrustum,
							Frustum * frustum,
							Transform * tsphere,
							Bounds * sphere);

#endif