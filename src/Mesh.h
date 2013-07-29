#ifndef MESH_H
#define MESH_H

#include "Core.h"
#include "GL.h"

class MeshData
{
public:
	virtual void *	getData();
	virtual u32 	getSize();

	virtual void	setData(u32 size, void * data);

protected:
	MeshData(u32 size = 0, void * data = NULL);
	virtual ~MeshData();

	virtual void validate();

	u32 	m_size;
	void * 	m_data;
};

class VertexData : public MeshData
{
public:
	VertexData(VertexFormat format, GLenum usage, u32 size = 0, void * data = NULL);
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
	IndexData(GLenum type, GLenum usage, GLenum mode, u32 size = 0, void * data = NULL);
	~IndexData();

	GLenum 					getType();
	GLenum					getMode();
	const IndexBuffer &		getIndexBuffer();

private:
	void validate();

	GLenum	 	m_type;
	GLenum 		m_mode;
	IndexBuffer	m_indexBuffer;
};

class IndexRange
{
public:
	IndexRange(u32 start, u32 count);

	u32 getStart();
	u32 getCount();
private:
	u32 m_start;
	u32 m_count;
};

class Mesh
{
	friend Mesh * LoadMesh(const char * filename);
public:
	Mesh(	const VertexFormat & vFormat,
			GLenum vUsage = GL_STATIC_DRAW,
			u32 vSize = 0,
			void * vData = NULL, 
			GLenum iType = GL_UNSIGNED_INT,
			GLenum iUsage = GL_STATIC_DRAW,
			GLenum iMode = GL_TRIANGLES,
			u32 iSize = 0,
			void * iData = NULL,
			u32 iCount = 0);
	~Mesh();

	const VertexArray & getVertexArray();

	void				draw();

private:

	VertexData		m_vertexData;
	IndexData		m_indexData;
	IndexRange		m_indexRange;
	VertexArray		m_vertexArray;
};

#endif