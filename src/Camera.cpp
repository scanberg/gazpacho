#include "Camera.h"
#include "Shader.h"
#include "Module.h"

Camera::Camera()
{
	m_fov = 60.0;
	m_near = 0.1;
	m_far = 100.0;
}

Camera::~Camera()
{

}

f32 Camera::getFov() const
{
	return m_fov;
}

f32 Camera::getNearClip() const
{
	return m_near;
}

f32 Camera::getFarClip() const
{
	return m_far;
}

f32 Camera::getFocalDistance() const
{
	return m_focalDistance;
}

f32 Camera::getFocalRange() const
{
	return m_focalRange;
}

const mat4 & Camera::getViewMatrix()
{
    m_viewMatrix = glm::mat4_cast(glm::conjugate(getOrientation()));
    m_viewMatrix = glm::translate(m_viewMatrix,-getPosition());
	return m_viewMatrix;
}

const mat4 & Camera::getProjMatrix() const
{
	return m_projMatrix;
}

void Camera::setup()
{
	const Shader * shader = Shader::getBoundShader();

	if(shader)
	{
		glUniformMatrix4fv(shader->getViewMatrixLocation(), 1, GL_FALSE, glm::value_ptr(getViewMatrix()));
		glUniformMatrix4fv(shader->getProjMatrixLocation(), 1, GL_FALSE, glm::value_ptr(getProjMatrix()));
	}
}

void Camera::setupProjection(int width, int height)
{
	m_projMatrix = glm::perspective(m_fov, (float)width/(float)height, m_near, m_far);
}

void Camera::render()
{
	setup();
	Module * module = getOwnerModule();
	if(module)
		module->draw(this);
}