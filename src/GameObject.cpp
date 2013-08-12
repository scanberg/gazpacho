#include "GameObject.h"
#include "Module.h"

GameObject::GameObject() :
m_flags(0),
m_type(UNDEFINED),
m_ownerModule(NULL)
{

}

GameObject::~GameObject()
{

}

bool GameObject::isStatic() const
{
	return m_flags & GAMEOBJECT_STATIC_BIT;
}

bool GameObject::isDrawable() const
{
	return m_flags & GAMEOBJECT_DRAWABLE_BIT;
}

const Transform & GameObject::getTransform() const
{
	return m_transform;
}

const Bounds & GameObject::getBounds() const
{
	return m_bounds;
}

Module * GameObject::getOwnerModule() const
{
	return m_ownerModule;
}

GameObjectType GameObject::getType() const
{
	return m_type;
}

const vec3 & GameObject::getPosition() const
{
	return m_transform.getPosition();
}

const quat & GameObject::getOrientation() const
{
	return m_transform.getOrientation();
}

const vec3 & GameObject::getScale() const
{
	return m_transform.getScale();
}

mat4 GameObject::getPose() const
{
	return m_transform.getPose();
}

mat4 GameObject::getInvPose() const
{
	return m_transform.getInvPose();
}

mat4 GameObject::getModelMatrix() const
{
	return m_transform.getModelMatrix();
}

mat4 GameObject::getInvModelMatrix() const
{
	return m_transform.getInvModelMatrix();
}

vec3 GameObject::getEulerAngles() const
{
	return glm::eulerAngles(getOrientation());
}

void GameObject::setPosition(const vec3 & position)
{
	m_transform.setPosition(position);
}

void GameObject::setOrientation(const quat & orientation)
{
	m_transform.setOrientation(orientation);
}

void GameObject::setScale(const vec3 & scale)
{
	m_transform.setScale(scale);
}

void GameObject::setTransform(const mat4 & transform)
{
	m_transform.setTransform(transform);
}

void GameObject::translate(const vec3 &translation)
{
	m_transform.setPosition(m_transform.getPosition() + translation);
}

void GameObject::move(vec3 movement)
{
	movement = glm::mat3_cast(getOrientation()) * movement;
	translate(movement);
}

void GameObject::rotate(f32 angle, const vec3 & axis)
{
	setOrientation(glm::rotate(getOrientation(), angle, axis));
}

void GameObject::rotateX(f32 angle)
{
	rotate(angle, vec3(1,0,0));
}

void GameObject::rotateY(f32 angle)
{
	rotate(angle, vec3(0,1,0));
}

void GameObject::rotateZ(f32 angle)
{
	rotate(angle, vec3(0,0,1));
}

void GameObject::setFlags(u8 flags)
{
	m_flags = flags;
}

void GameObject::setType(GameObjectType type)
{
	m_type = type;
}

void GameObject::setOwnerModule(Module * module)
{
	m_ownerModule = module;
}