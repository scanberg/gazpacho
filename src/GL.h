#ifndef GL_H
#define GL_H

#include "Core.h"

enum VertexAttribute { 	POSITION=0, TEXCOORD, NORMAL,
						TANGENT, COLOR, INDEX };

enum BufferLongevity { 	STATIC, DYNAMIC };

class VertexFormat
{
public:
	VertexFormat( const char * format );

	i32 getSize();

	i32 getOffset(VertexAttribute attr);
	i32	getComponentCount(VertexAttribute attr);
	GLenum getType(VertexAttribute attr);

	void setAttribPointers() const;

private:
	static const i32 attributeCount = 6;

	void parseFormat( const char * format );
	void validate();

	i32		m_components[attributeCount];
	i32 	m_offsets[attributeCount];
	GLenum	m_types[attributeCount];

	u8 		m_totalByteSize;
};


// NOT IN USE
class BufferManager
{
public:
	u32 getBuffer(BufferLongevity longevity, GLenum target, i32 size);
private:
	BufferManager();
	~BufferManager();
};

class Buffer
{
public:
	virtual ~Buffer();

	virtual void bind() const;
	virtual void unbind() const;

	virtual void setData(u32 size, void * data);
protected:
	Buffer(GLenum usage);

	u32 m_bufferID;
	GLenum m_usage;
	GLenum m_target;

	virtual void validate();
};

class VertexBuffer : public Buffer
{
public:
	VertexBuffer(GLenum usage) :
	Buffer(usage)
	{ m_target = GL_ARRAY_BUFFER; }
};

class IndexBuffer : public Buffer
{
public:
	IndexBuffer(GLenum usage) :
	Buffer(usage)
	{ m_target = GL_ELEMENT_ARRAY_BUFFER; }
};

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void bind();
	void unbind();

private:
	u32 m_arrayID;
};

#endif