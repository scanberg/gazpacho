#ifndef MESH_H
#define MESH_H

#include "Core.h"
#include "GL.h"

class MeshData
{
public:
	virtual void *	getData();
	virtual i32 	getSize();

	virtual void	setData(i32 size, void * data);

protected:
	MeshData(i32 size = 0, void * data = NULL);
	virtual ~MeshData();

	virtual void validate();

	i32 	m_size;
	void * 	m_data;
};

class VertexData : public MeshData
{
public:
	VertexData(VertexFormat format, BufferUsage usage, i32 size = 0, void * data = NULL);
	~VertexData();

	const VertexFormat &	getFormat();
	const VertexBuffer & 	getVertexBuffer();
private:
	VertexFormat 	m_format;
	VertexBuffer 	m_vertexBuffer;
};

class IndexData : public MeshData
{
public:
	IndexData(IndexDataType type, GLenum mode, BufferUsage usage, i32 size = 0, void * data = NULL);
	~IndexData();

	GLenum 					getType();
	GLenum					getMode();
	const VertexBuffer &	getIndexBuffer();

private:
	void validate();

	GLenum	 	m_type;
	GLenum 		m_mode;
	IndexBuffer	m_indexBuffer;
};

class IndexRange
{
public:
	IndexRange(i32 start, i32 count);

	i32 getStart();
	i32 getCount();
private:
	i32 m_start;
	i32 m_count;
};

class Mesh
{
	friend Mesh * LoadMesh(const char * filename);
public:

	const VertexArray & getVertexArray();

	void				draw();

private:
	Mesh();
	~Mesh();

	VertexData		m_vertexData;
	IndexData		m_indexData;
	VertexArray		m_vertexArray;
};

#endif