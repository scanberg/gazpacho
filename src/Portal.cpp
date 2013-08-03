#include "Portal.h"
#include "Shader.h"
#include "Camera.h"
#include "Mesh.h"
#include "Plane.h"
#include "Module.h"

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

	vec3 min = vec3(-half_width, -half_height, 0.0f);
	vec3 max = vec3(half_width, half_height, 0.0f);
	f32 radius = length(max);

	m_bounds = Bounds(min, max, radius);

	setScale(vec3(width, height, 1.0));

	setType(PORTAL);
}

Portal::~Portal()
{
	
}

Portal * Portal::getTargetPortal()
{
	return m_targetPortal;
}

const vec3 & Portal::getMin()
{
	return m_bounds.getMin();
}

const vec3 & Portal::getMax()
{
	return m_bounds.getMax();
}

Plane Portal::getPlane()
{

	return Plane(vec3(0,0,1),0.0f);
}

void Portal::setTargetPortal(Portal * portal)
{
	m_targetPortal = portal;
}

void Portal::draw(Camera * cam)
{
	const Shader * shader = Shader::getBoundShader();
	mat4 portalTransform = getPose();
	int planeLoc = -1;

	if(shader)
	{
		glUniformMatrix4fv(shader->getModelMatrixLocation(), 1, GL_FALSE, glm::value_ptr(portalTransform));
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
		glStencilFunc(GL_NEVER, 1, 0xFF);
		glStencilOp(GL_REPLACE, GL_KEEP, GL_KEEP);  // draw 1s on test fail (always)

		// draw stencil pattern
		glStencilMask(0xFF);
		glClear(GL_STENCIL_BUFFER_BIT);  // needs mask=0xFF

		mat4 proj = cam->getProjMatrix();
		proj[2][2] = 1.0f;
		//proj[2][3] = 1.0f;
		proj[3][2] = 1.0f;

		glUniformMatrix4fv(shader->getProjMatrixLocation(), 1, GL_FALSE, glm::value_ptr(proj));
		Portal::m_quad->draw();

		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		glDepthMask(GL_TRUE);
		glStencilMask(0x00);
		// draw where stencil's value is 0
		glStencilFunc(GL_EQUAL, 0, 0xFF);
		/* (nothing to draw) */
		// draw only where stencil's value is 1
		glStencilFunc(GL_EQUAL, 1, 0xFF);

		mat4 Pa = glm::translate(mat4(),getPosition()) * glm::mat4_cast(getOrientation());
   		mat4 PbInv = glm::mat4_cast(glm::conjugate(m_targetPortal->getOrientation())) * glm::translate(mat4(),-m_targetPortal->getPosition());
   		mat4 CInv = glm::mat4_cast(glm::conjugate(cam->getOrientation())) * glm::translate(mat4(),-cam->getPosition());

		mat4 viewMatrix = CInv * Pa * PbInv;

		glUniformMatrix4fv(shader->getViewMatrixLocation(), 1, GL_FALSE, glm::value_ptr(viewMatrix));
		glUniformMatrix4fv(shader->getProjMatrixLocation(), 1, GL_FALSE, glm::value_ptr(cam->getProjMatrix()));

		vec3 normal = glm::mat3_cast((m_targetPortal->getOrientation())) * vec3(0,0,-1);
		vec3 point = -m_targetPortal->getPosition();

		Plane clipPlane(normal, point);
		clipPlane.transform(viewMatrix);

		if(planeLoc > -1)
			glUniform4fv(planeLoc, 1, glm::value_ptr(clipPlane.getVec4()));

		m_targetPortal->getOwnerModule()->drawWithoutPortals(cam);

		if(planeLoc > -1)
			glUniform4f(planeLoc, 0,0,0,0);

		glDisable(GL_STENCIL_TEST);

	}
	else
	{
		Portal::m_quad->draw();
	}
}