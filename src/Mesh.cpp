#include "Mesh.h"
#include <memory.h>

MeshData::MeshData(i32 size, void * data)
{
	if(data)
	{
		m_data = malloc( size );
		memcpy( m_data, data, size );
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

VertexData::VertexData(VertexFormat format, GLenum usage, i32 size, void * data) :
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

IndexData::IndexData(GLenum type, GLenum usage, GLenum mode, i32 size, void * data) :
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

GLenum IndexData::getType()
{
	return m_type;
}

GLenum IndexData::getMode()
{
	return m_mode;
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

Mesh::Mesh(	const VertexFormat & vFormat,
			GLenum vUsage,
			i32 vSize,
			void * vData, 
			GLenum iType,
			GLenum iUsage,
			GLenum iMode,
			i32 iSize ,
			void * iData,
			u32 iCount) :
m_vertexData(vFormat, vUsage, vSize, vData),
m_indexData(iType, iUsage, iMode, iSize, iData),
m_indexRange(0, iCount)
{

}

Mesh::~Mesh()
{
} 

const VertexArray & Mesh::getVertexArray()
{
	return m_vertexArray;
}

void Mesh::draw()
{
	m_vertexArray.bind();

	glDrawElements(	m_indexData.getMode(),
					m_indexRange.getCount(),
					m_indexData.getType(),
					(void*)+m_indexRange.getStart() );

	m_vertexArray.unbind();
}