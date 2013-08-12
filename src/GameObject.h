#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Core.h"
#include "Transform.h"
#include "Bounds.h"

enum GameObjectType	{ UNDEFINED, CAMERA, MODEL, PORTAL };

#define GAMEOBJECT_STATIC_BIT 	0x01
#define GAMEOBJECT_DRAWABLE_BIT	0x02

class GameObject
{
public:
	bool 				isStatic() const;
	bool				isDrawable() const;
	const Transform & 	getTransform() const;
	const Bounds & 		getBounds() const;
	Module * 			getOwnerModule() const;

	/* ID/Property Functionality */
	GameObjectType 		getType() const;

	/* Transform Functionality */
	const vec3 &		getPosition() const;
	const quat &		getOrientation() const;
	const vec3 &		getScale() const;
	mat4		 		getPose() const;
	mat4				getInvPose() const;
	mat4				getModelMatrix() const;
	mat4				getInvModelMatrix() const;

	vec3				getEulerAngles() const;

	void				setPosition(const vec3 & position);
	void 				setOrientation(const quat & orientation);
	void				setScale(const vec3 & scale);
	void 				setTransform(const mat4 & transform);

	void				translate(const vec3 &translation);
	void				move(vec3 movement);
	void 				rotate(f32 angle, const vec3 & axis);
	void				rotateX(f32 angle);
	void				rotateY(f32 angle);
	void				rotateZ(f32 angle);

	/* Bounds Functionality */


protected:
	friend class Module;
	GameObject();
	virtual ~GameObject();

	void setFlags(u8 flags);
	void setType(GameObjectType type);
	void setStatic(bool flag);
	void setOwnerModule(Module * module);

	u8				m_flags;
	GameObjectType 	m_type;
	Transform 		m_transform;
	Bounds 			m_bounds;

	Module *		m_ownerModule;

	u32 			m_ID;
};

#endif