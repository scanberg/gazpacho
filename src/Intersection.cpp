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

bool intersectLinePortal(	const vec3 & start,
							const vec3 & end,
							const Portal & portal)
{
	return false;
}

bool barycentricTriangleIntersect(const vec3 &p, const Triangle &t, vec3 &baryCoords)
{
    glm::vec3 v0 = t.point[2] - t.point[0];
    glm::vec3 v1 = t.point[1] - t.point[0];
    glm::vec3 v2 = p - t.point[0];

    f32 dot00 = glm::dot(v0,v0);
    f32 dot01 = glm::dot(v0,v1);
    f32 dot02 = glm::dot(v0,v2);
    f32 dot11 = glm::dot(v1,v1);
    f32 dot12 = glm::dot(v1,v2);

    f32 invDenom = 1.0 / (dot00 * dot11 - dot01 * dot01);
    baryCoords[2] = (dot11 * dot02 - dot01 * dot12) * invDenom;
    baryCoords[1] = (dot00 * dot12 - dot01 * dot02) * invDenom;

    baryCoords[0] = 1.0f - baryCoords[1] - baryCoords[2];

    return (baryCoords[1] > 0.0) && (baryCoords[2] > 0.0) && (baryCoords[0] > 0.0);

}

f32 rayVsTriangle(const Ray &ray, const Triangle &triangle, vec3 &baryCoords)
{
    f32 t = glm::dot(triangle.point[0]-ray.origin, triangle.normal) / glm::dot(ray.direction, triangle.normal);

    vec3 pointInPlane = ray.origin + ray.direction*t;

    if(barycentricTriangleIntersect(pointInPlane, triangle, baryCoords))
        return t;

    return MAXFLOAT;
}