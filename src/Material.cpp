#include "Material.h"

Material::Material() :
m_color(vec3(1.0))
{

}

Material::~Material()
{

}

void Material::setColor(vec3 color)
{
	m_color = color;
}

void Material::bind()
{
	const Shader * shader = Shader::getBoundShader();

	if(shader)
	{
		i32 location = shader->getUniformLocation("color");
		if(location > -1)
			glUniform3fv(location, 1, glm::value_ptr(m_color));
	}
}

void Material::unbind()
{

}