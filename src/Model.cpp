#include "Model.h"
#include "Shader.h"

Model::Model(Mesh * mesh, Material * material)
{
	setFlags(GAMEOBJECT_DRAWABLE_BIT);
	setType(MODEL);

	if(mesh)
		m_mesh = mesh;
	m_material = material;
}

Model::~Model()
{

}

Mesh * Model::getMesh()
{
	return m_mesh;
}

Material * Model::getMaterial()
{
	return m_material;
}

void Model::setMesh(Mesh * mesh)
{
	if(mesh)
		m_mesh = mesh;
}

void Model::setMaterial(Material * material)
{
	m_material = material;
}

void Model::draw()
{
	if(m_material)
		m_material->bind();

	const Shader * shader = Shader::getBoundShader();

	if(shader)
		glUniformMatrix4fv(shader->getModelMatrixLocation(), 1, GL_FALSE, glm::value_ptr(m_transform.getModelMatrix()));

	m_mesh->draw();
}