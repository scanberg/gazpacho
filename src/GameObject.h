#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Core.h"
#include "Transform.h"
#include "Bounds.h"
#include "Module.h"

enum GameObjectType	{ UNDEFINED, CAMERA, MODEL, PORTAL };

#define GAMEOBJECT_STATIC_BIT 	0x01
#define GAMEOBJECT_DRAWABLE_BIT	0x02

class GameObject
{
public:
	bool 				isStatic();
	bool				isDrawable();
	const Transform & 	getTransform();
	const Bounds & 		getBounds();
	Module * 			getOwnerModule();

	/* ID/Property Functionality */
	GameObjectType 		getType();

	/* Transform Functionality */
	const vec3 &		getPosition();
	const quat &		getOrientation();
	const vec3 &		getScale();
	const mat4 & 		getPose();
	const mat4 &		getInvPose();

	vec3				getEulerAngles();

	void				setPosition(const vec3 & position);
	void 				setOrientation(const quat & orientation);
	void				setScale(const vec3 & scale);

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
	void setOwnerModule(Module * module);

	u8				m_flags;
	GameObjectType 	m_type;
	Transform 		m_transform;
	Bounds 			m_bounds;

	Module *		m_ownerModule;

	u32 			m_ID;
};

#endif