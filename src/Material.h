#ifndef MATERIAL_H
#define MATERIAL_H

#include "Core.h"
#include "Shader.h"

class Material
{
public:
	Material();
	~Material();

	void setColor(vec3 color);

	void bind();
	void unbind();
private:
	vec3 m_color;
};

#endif