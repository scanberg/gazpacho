#include "Intersection.h"

bool barycentricTriangleIntersect(const vec3 &p, const vec3 * t);

bool intersectBoxPoint( const Transform * tbox,
						const Bounds * box,
						const vec3 & point)
{
	vec3 tPoint = vec3(tbox->getInvPose() * vec4(point, 1.0f));

	if(	tPoint.x < box->getMin().x || box->getMax().x < tPoint.x )	return 0;
	if(	tPoint.y < box->getMin().y || box->getMax().y < tPoint.y )	return 0;
	if(	tPoint.z < box->getMin().z || box->getMax().z < tPoint.z )	return 0;

	return true;
}

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
	vec3 normal = glm::normalize(glm::cross(triangle[1]-triangle[0], triangle[2]-triangle[0]));
	vec3 direction = end - start;
	f32 t = glm::dot(triangle[0]-start, normal) / glm::dot(direction, normal);

    vec3 pointInPlane = start + direction * t;

    if(t > 0.0f && t < 1.0f && barycentricTriangleIntersect(pointInPlane, triangle))
        return true;

    return false;
}

bool intersectLinePortal(	const vec3 & start,
							const vec3 & end,
							const Portal & portal)
{
	/*vec3 a[3] = { 	portal.getPortalCorner(TOPLEFT),
					portal.getPortalCorner(BOTTOMLEFT),
					portal.getPortalCorner(TOPRIGHT) };

	vec3 b[3] = { 	portal.getPortalCorner(BOTTOMLEFT),
					portal.getPortalCorner(BOTTOMRIGHT),
					portal.getPortalCorner(TOPRIGHT) };

	return intersectLineTriangle(start, end, a) || intersectLineTriangle(start, end, b); */

	mat4 transform = portal.getInvPose();

	vec3 tstart = vec3(transform * vec4(start, 1.0f));
	vec3 tend	= vec3(transform * vec4(end, 1.0f));

	vec3 min = portal.getBounds().getMin();
	vec3 max = portal.getBounds().getMax();

	vec3 direction = tend - tstart;

	if(glm::sign(tend.z) == glm::sign(tstart.z)) return 0;
	if(direction.z > 0.0f) return 0;

	vec3 pointInPlane = tstart + direction * (glm::abs(tstart.z) / glm::abs(direction.z));

	if(pointInPlane.x < min.x || max.x < pointInPlane.x) return 0;
	if(pointInPlane.y < min.y || max.y < pointInPlane.y) return 0;

	return 1;
}

bool barycentricTriangleIntersect(const vec3 &p, const vec3 * t)
{
    vec3 v0 = t[2] - t[0];
    vec3 v1 = t[1] - t[0];
    vec3 v2 = p - t[0];

    f32 dot00 = glm::dot(v0,v0);
    f32 dot01 = glm::dot(v0,v1);
    f32 dot02 = glm::dot(v0,v2);
    f32 dot11 = glm::dot(v1,v1);
    f32 dot12 = glm::dot(v1,v2);

    f32 invDenom = 1.0f / (dot00 * dot11 - dot01 * dot01);

    vec3 baryCoords;

    baryCoords[2] = (dot11 * dot02 - dot01 * dot12) * invDenom;
    baryCoords[1] = (dot00 * dot12 - dot01 * dot02) * invDenom;

    baryCoords[0] = 1.0f - baryCoords[1] - baryCoords[2];

    return (baryCoords[1] > 0.0f) && (baryCoords[2] > 0.0f) && (baryCoords[0] > 0.0f);

}