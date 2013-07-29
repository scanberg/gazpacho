#ifndef MODEL_H
#define MODEL_H

#include "GameObject.h"
#include "Mesh.h"
#include "Material.h"

class Model : public GameObject
{
public:
	Model(Mesh * mesh, Material * material = NULL);
	~Model();

	Mesh * 		getMesh();
	Material * 	getMaterial();

	void setMesh(Mesh * mesh);
	void setMaterial(Material * material);

	void draw();

protected:
	Mesh * m_mesh;
	Material * m_material;
};

#endif