#include "GL.h"
#include <cstring>
#include <cstdio>
#include <cstdlib>

#define DEFAULT_USAGE GL_STATIC_DRAW
#define DEFAULT_FORMAT "v3f:tc2f:n3f"

VertexFormat::VertexFormat( String format ) :
m_totalByteSize(0)
{
	for(int i=0; i<attribCount; ++i)
	{
		m_components[i] = 0;
		m_offsets[i] = 0;
		m_types[i] = GL_FLOAT;
	}

	parseFormat(format.c_str());
	validate();
}

i32 VertexFormat::getSize()
{
	return m_totalByteSize;
}

i32 VertexFormat::getOffset(VertexAttribute attr)
{
	return m_offsets[attr];
}

i32	VertexFormat::getComponentCount(VertexAttribute attr)
{
	return m_components[attr];
}

GLenum VertexFormat::getType(VertexAttribute attr)
{
	return m_types[attr];
}

void VertexFormat::setAttribPointers()
{
	for(u32 i=0; i<attributeCount; ++i)
	{
		if(m_components[i] > 0)
		{
			i32 size 		= m_components[i];
			GLenum type 	= m_types[i];
			GLboolean norm 	= GL_FALSE;
			i32 stride		= m_totalByteSize;
			i32 offset 		= m_offsets[i];

			if(i == NORMAL || i == TANGENT)
				norm = GL_TRUE;
			
			glVertexAttribPointer(i, size, type, norm, stride, (GLvoid*)(0 + offset));
			glEnableVertexAttribArray(i);
		}
	}
}

void VertexFormat::parseFormat(const char * format)
{
	if(format)
	{
		char * formatcpy = (char*)malloc( strlen(format) + 1 );
		strcpy(formatcpy,format);

		i32 currentOffset = 0;
		i32 target;
		char * pch;

		pch = strtok(formatcpy,":");
		while(pch != NULL)
		{
			target = -1;
			if(pch[0] == 'v' || pch[0] == 'p')
				target = POSITION;
			else if (pch[0] == 't')
				if(pch[1] == 'c')
				{
					target = TEXCOORD;
					++pch;
				}
				else
					target = TANGENT;
			else if (pch[0] == 'n')
				target = NORMAL;
			else if (pch[0] == 'c')
				target = COLOR;
			else if (pch[0] == 'i')
				target = INDEX;

			if(target > -1)
			{
				m_components[target] = atoi(++pch);
				++pch;
				int size = 0;

				if (pch[0] == 'f')
				{
					m_types[target] = GL_FLOAT;
					size = sizeof(f32);
				}
				else if (pch[0] == 'h')
				{
					m_types[target] = GL_HALF_FLOAT;
					size = sizeof(f16);
				}
				else if (pch[0] == 'b')
				{
					m_types[target] = GL_BYTE;
					size = sizeof(i8);
				}
				else if (pch[0] == 's')
				{
					m_types[target] = GL_SHORT;
					size = sizeof(i16);
				}
				else if (pch[0] == 'i')
				{
					m_types[target] = GL_INT;
					size = sizeof(i32);
				}
				else if (pch[0] == 'u')
				{
					if (pch[1] == 'b')
					{
						m_types[target] = GL_UNSIGNED_BYTE;
						size = sizeof(u8);
					}
					else if (pch[1] == 's')
					{
						m_types[target] = GL_UNSIGNED_SHORT;
						size = sizeof(u16);
					}
					else if (pch[1] == 'i')
					{
						m_types[target] = GL_UNSIGNED_INT;
						size = sizeof(u32);
					}
				}
				m_offsets[target] = currentOffset;
				currentOffset += size * m_components[target];
			}
		}
		m_totalByteSize = currentOffset;
	}
}

void VertexFormat::validate()
{
	if(m_components[POSITION] < 1 || m_components[POSITION] > 4)
	{
		printf("VertexFormat did not have a valid position attribute, falling back to default. \n");
		parseFormat(DEFAULT_FORMAT);
		return;
	}
	for(i32 i=1; i<attributeCount; ++i)
	{
		if(m_components[i] > 4)
		{
			printf("VertexFormat comtains invalid component size(s), falling back to default. \n");
			parseFormat(DEFAULT_FORMAT);
			return;
		}
	}
}



Buffer::Buffer( BufferUsage usage ) :
m_usage(usage)
{
	glGenBuffers(1, &m_bufferID);
}

Buffer::~Buffer()
{
	glDeleteBuffers(1, &m_bufferID);
}

void Buffer::bind()
{
	glBindBuffer(m_target, m_bufferID);
}

void Buffer::unbind()
{
	glBindBuffer(m_target, 0);
}

void Buffer::setData(i32 size, void * data)
{
	bind();
	glBufferData(m_target, size, data, m_usage);
	unbind();
}

void Buffer::validate()
{
	if(	m_usage == GL_STATIC_DRAW ||
		m_usage == GL_DYNAMIC_DRAW ||
		m_usage == GL_STREAM_DRAW )
	{
		printf("Buffer usage is ok! \n");
		return;
	}

	m_usage = DEFAULT_USAGE;
	printf("Specified buffer usage is not valid, falling back to default. \n");
}

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_arrayID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_arrayID);
}

void VertexArray::bind()
{
	glBindVertexArray(m_arrayID);
}

void VertexArray::unbind()
{
	glBindVertexArray(0);
}