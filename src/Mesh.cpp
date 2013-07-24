#include <stdio.h>
#include "Mesh.h"

MeshData::MeshData(i32 size, void * data) :
{
	if(data)
	{
		m_data = malloc( (size_t)size );
		memcpy( m_data, data, (size_t)size );
		m_size = size;
	}
	else
	{
		m_data = NULL;
		m_size = 0;
	}
}

MeshData::~MeshData()
{
	if(m_data)
		free(m_data);
}

void * MeshData::getData()
{
	return m_data;
}

i32 MeshData::getSize()
{
	return m_size;
}

void MeshData::setData(i32 size, void * data)
{
	if(data)
	{
		free(m_data);
		m_data = malloc( (size_t)size );
		memcpy( m_data, data, (size_t)size );
		m_size = size;
	}
}

void MeshData::validate()
{

}

VertexData::VertexData(VertexFormat format, BufferUsage usage, i32 size, void * data) :
MeshData(size, data),
m_format(format),
m_vertexBuffer(usage)
{
	validate();
}

VertexData::~VertexData()
{

}

const VertexFormat & VertexData::getFormat()
{
	return m_format;
}

const VertexBuffer & VertexData::getVertexBuffer()
{
	return m_vertexBuffer;
}

IndexData::IndexData(GLenum type, GLenum mode, BufferUsage usage, i32 size, void * data) :
MeshData(size, data),
m_type(type),
m_mode(mode),
m_indexBuffer(usage)
{
	validate();
}

IndexData::~IndexData()
{

}

IndexDataType IndexData::getType()
{
	return m_type;
}

IndexMode IndexData::getMode()
{
	return m_mode;
}

GLenum IndexData::getGLType()
{
	return m_glType;
}

GLenum IndexData::getGLMode()
{
	return m_glMode;
}

void IndexData::validate()
{

}


IndexRange::IndexRange(u32 start, u32 count) :
m_start(start),
m_count(count)
{

}

u32 IndexRange::getStart()
{
	return m_start;
}

u32 IndexRange::getCount()
{
	return m_count;
}

SubMesh::SubMesh(const IndexRange & ir, Material * mat) :
m_indexRange(ir),
m_material(mat)
{

}

const IndexRange & SubMesh::getIndexRange()
{
	return m_indexRange;
}

Material * SubMesh::getMaterial()
{
	return m_material;
}

Mesh::Mesh()
{

}

Mesh::~Mesh()
{
	if(m_subMeshes)
	{
		delete[] m_subMeshes;
		m_subMeshes = NULL;
	}
}

const VertexArray & Mesh::getVertexArray()
{
	return m_vertexArray;
}

void Mesh::draw()
{
	m_vertexArray.bind();

	glDrawElements(	m_indexData.getGLMode(),
					sm->getIndexRange().getCount(),
					m_indexData.getGLType(),
					sm->getIndexRange.getStart() );

	m_vertexArray.unbind();
}