#include "Intersection.h"

bool intersectBoxBox(	Transform * tboxA,
						Bounds * boxA,
						Transform * tboxB,
						Bounds * boxB)
{
	return false;
}

bool intersectBoxSphere(Transform * tbox,
						Bounds * box,
						Transform * tsphere,
						Bounds * sphere)
{
	return false;
}

bool intersectSphereSphere(	Transform * tsphereA,
							Bounds * sphereA,
							Transform * tsphereB,
							Bounds * sphereB)
{
	return false;
}

bool intersectBoxFrustum(	Transform * tbox,
							Bounds * box,
							Transform * tfrustum,
							Frustum * frustum)
{
	return false;
}

bool intersectFrustumPoint(	Transform * tfrustum,
							Frustum * frustum,
							const vec3 & point)
{
	return false;
}

bool intersectFrustumSphere(Transform * tfrustum,
							Frustum * frustum,
							Transform * tsphere,
							Bounds * sphere)
{
	return false;
}

bool intersectLineTriangle(	const vec3 & start,
							const vec3 & end,
							const vec3 * triangle)
{
	return false;
}