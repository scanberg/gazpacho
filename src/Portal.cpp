#include "Portal.h"
#include "Shader.h"
#include "Camera.h"
#include "Mesh.h"
#include "Plane.h"
#include "Module.h"
#include "Intersection.h"

Mesh * Portal::m_quad = NULL;

void Portal::init()
{
	f32 vData[12] = {   -0.5, 0.5, 0,
						 0.5, 0.5, 0,
						-0.5,-0.5, 0,
						 0.5,-0.5, 0 };

	u32 iData[6] = { 	0, 2, 1,
						1, 2, 3 };

	m_quad = new Mesh(	"v3f",
						GL_STATIC_DRAW,
						12*sizeof(f32),
						vData,
						GL_UNSIGNED_INT,
						GL_STATIC_DRAW,
						GL_TRIANGLES,
						6*sizeof(u32),
						iData,
						6);
}

void Portal::cleanup()
{
	if(m_quad)
		delete m_quad;
}

Portal::Portal(f32 width, f32 height, Portal * targetPortal) :
m_targetPortal(targetPortal)
{
	assert(width > 0);
	assert(height > 0);

	f32 half_width = width * 0.5f;
	f32 half_height = height * 0.5f;

	vec3 min = vec3(-half_width, -half_height, -0.1f);
	vec3 max = vec3(half_width, half_height, 0.1f);
	f32 radius = length(max);

	m_bounds = Bounds(min, max, radius);

	setScale(vec3(width, height, 1.0));

	setType(PORTAL);
}

Portal::~Portal()
{
	
}

bool Portal::isMirror() const
{
	return m_targetPortal == this;
}

Portal * Portal::getTargetPortal() const
{
	return m_targetPortal;
}

vec3 Portal::getPortalCorner(PortalCorner corner) const
{
	f32 x = (corner % 2) ? m_bounds.getMin().x : m_bounds.getMax().x;
	f32 y = (corner < 2) ? m_bounds.getMax().y : m_bounds.getMin().y;

	vec4 h = vec4(x, y, 0.0f, 1.0f);

	return vec3(getPose() * h);
}

Plane Portal::getPlane() const
{
	Plane p(vec3(0,0,1), 0.0f);
	p.transform(getPose());
	return p;
}

mat4 Portal::getViewMatrix(Camera * cam) const
{
	assert(cam != NULL);

	mat4 P2P = glm::rotate(mat4(1.0f), 180.0f, vec3(0,1,0));

	//if(isMirror())
	//	P2P = P2P * glm::scale(mat4(1.0f), vec3(-1,1,1));

	mat4 viewMatrix = cam->getInvPose() * getPose() * P2P * m_targetPortal->getInvPose();
	return viewMatrix;
}

mat4 Portal::getInvViewMatrix(Camera * cam) const
{
	assert(cam != NULL);

	mat4 P2P = glm::rotate(mat4(1.0f), 180.0f, vec3(0,1,0));
	mat4 viewMatrix = getTargetPortal()->getPose() * P2P * getInvPose() * cam->getPose();
	return viewMatrix;
}

void Portal::setTargetPortal(Portal * portal)
{
	m_targetPortal = portal;
}

void Portal::draw(Camera * cam)
{
	assert(cam != NULL);

	//printf("Drawing portal %u \n", this);

	const Shader * shader = Shader::getBoundShader();
	int planeLoc = -1;

	if(shader)
	{
		glUniformMatrix4fv(shader->getModelMatrixLocation(), 1, GL_FALSE, glm::value_ptr(getModelMatrix()));
		planeLoc = shader->getUniformLocation("clipPlane");
	}

	vec3 n = glm::mat3_cast((getOrientation())) * vec3(0,0,1);
	vec3 p = -getPosition();

	Plane plane(n, p);
	//if(glm::dot(vec4(cam->getPosition(),1.0f), plane.getVec4()) < 0.0f)
	//	return;

	if(shader && m_targetPortal && m_targetPortal->getOwnerModule())
	{
		//m_bounds.drawBB();

		glEnable(GL_STENCIL_TEST);
		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
		glDepthMask(GL_FALSE);
		glStencilFunc(GL_ALWAYS, 1, 1);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);  // draw 1s on test fail (always)

		// draw stencil pattern
		glStencilMask(0xFF);
		glClear(GL_STENCIL_BUFFER_BIT);  // needs mask=0xFF

		mat4 proj = cam->getProjMatrix();

		//if(	glm::dot(vec4(cam->getPosition(), 1.0f), plane.getVec4()) < 1.5f*cam->getNearClip() )
		if( intersectBoxPoint( &getTransform(), &getBounds(), cam->getPosition()) )
		{
			// HACK TO REMOVE NEAR CLIP ON PORTAL
			proj[2][2] = 1.0f;
			proj[3][2] = 0.0f;
		}

		glUniformMatrix4fv(shader->getProjMatrixLocation(), 1, GL_FALSE, glm::value_ptr(proj));
		Portal::m_quad->draw();

		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		glDepthMask(GL_TRUE);
		//glStencilMask(0x00);

		// draw only where stencil's value is 1
		glStencilFunc(GL_EQUAL, 1, 1);
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

		// Clear using a custom quad on screen
		glDepthFunc(GL_ALWAYS);

		mat4 clearModel = glm::translate(glm::scale(mat4(), vec3(2,2,1)), vec3(0,0,1));
		mat4 clearView = mat4();
		mat4 clearProj = mat4();

		glUniformMatrix4fv(shader->getModelMatrixLocation(),1, GL_FALSE, glm::value_ptr(clearModel));
		glUniformMatrix4fv(shader->getViewMatrixLocation(), 1, GL_FALSE, glm::value_ptr(clearView));
		glUniformMatrix4fv(shader->getProjMatrixLocation(), 1, GL_FALSE, glm::value_ptr(clearProj));

		i32 colorLoc = shader->getUniformLocation("color");
		if(colorLoc > -1)
			glUniform3fv(colorLoc, 1, glm::value_ptr(vec3(0,0,0)));

		Portal::m_quad->draw();

		glDepthFunc(GL_LESS);

		mat4 viewMatrix = getViewMatrix(cam);

		glUniformMatrix4fv(shader->getViewMatrixLocation(), 1, GL_FALSE, glm::value_ptr(viewMatrix));
		glUniformMatrix4fv(shader->getProjMatrixLocation(), 1, GL_FALSE, glm::value_ptr(cam->getProjMatrix()));

		vec3 normal = glm::mat3_cast((m_targetPortal->getOrientation())) * vec3(0,0,1);
		vec3 point = -m_targetPortal->getPosition();

		Plane clipPlane(normal, point);
		clipPlane.transform(viewMatrix);

		if(planeLoc > -1)
			glUniform4fv(planeLoc, 1, glm::value_ptr(clipPlane.getVec4()));

		glEnable(GL_CLIP_PLANE0);

		m_targetPortal->getOwnerModule()->drawWithoutPortals(cam);

		glDisable(GL_CLIP_PLANE0);
		glDisable(GL_STENCIL_TEST);

	}
	else
	{
		Portal::m_quad->draw();
	}
}