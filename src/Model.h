#ifndef MODEL_H
#define MODEL_H

#include "GameObject.h"
#include "Mesh.h"
#include "Material.h"
#include "Skeleton.h"

class Model : public GameObject
{
	
protected:
	Mesh * m_mesh;
	Material * m_material;
	Skeleton * m_skeleton;
};

#endif