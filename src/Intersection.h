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
							Frustum * frustum);

bool intersectFrustumSphere(Frustum * frustum,
							Transform * tsphere,
							Bounds * sphere);

#endif