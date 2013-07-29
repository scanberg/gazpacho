/**
Copyright (C) 2012-2014 Robin Skånberg

Permission is hereby granted, free of charge,
to any person obtaining a copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <fstream>
#include <cstdio>
#include <cstring>
#include "Shader.h"
#include "GL.h"

#define BUFFER_SIZE 2048

static const char * default_vert_shader =
"#version 150\n \
uniform mat4 modelMatrix = mat4(1.0);\n \
uniform mat4 viewMatrix = mat4(1.0);\n \
uniform mat4 projMatrix = mat4(1.0);\n \
uniform vec3 color = vec3(1.0);\n \
in vec3 in_position;\n \
out vec4 Color;\n \
void main(void)\n \
{\n \
    gl_Position = projMatrix * viewMatrix * modelMatrix * vec4(in_position, 1.0);\n \
	Color = vec4(color, 1.0);\n \
}";

static const char * default_frag_shader =
"#version 150\n \
in vec4 Color;\n \
out vec4 out_frag0;\n \
void main(void)\n \
{\n \
    out_frag0 = Color;\n \
}";

Shader *Shader::boundShader = NULL;

/**
 * readTextFile - reads a simple textfile specified by filename,
 * if everything is ok, a pointer to a null-terminated string is returned,
 * otherwise NULL is returned.
 */

char* readTextFile(const char *filename) {
	if(filename == NULL)
		return 0;

    FILE *file = fopen(filename, "r");
    if(file == NULL)
    {
        printf("Cannot open file %s", filename);
        return 0;
    }

    fseek(file, 0, SEEK_END);

    char *buffer = NULL;
    int bytesinfile = ftell(file);
    rewind(file);

    if(bytesinfile > 0)
    {
        buffer = (char*)malloc(bytesinfile+1);
        size_t bytesread = fread( buffer, 1, bytesinfile, file);
        buffer[bytesread] = '\0'; // Terminate the string with a null character
    }

    fclose(file);

    return buffer;
}

Shader::Shader()
{
    vertexShader    = 0;
    fragmentShader  = 0;
    program         = 0;
    compiled        = 0;

    positionLoc     = -1;
    normalLoc       = -1;
    tangentLoc      = -1;
    texCoordLoc     = -1;
	extraLoc		= -1;

	modelMatrixLoc	= -1;
    viewMatrixLoc   = -1;
    projMatrixLoc   = -1;

    vertexFile      = NULL;
    fragmentFile    = NULL;

    loadAndCompile();
}

Shader::Shader( const char *vertFile, const char *fragFile )
{
    vertexShader    = 0;
    fragmentShader  = 0;
    program         = 0;
    compiled        = 0;

    positionLoc     = -1;
    normalLoc       = -1;
    tangentLoc      = -1;
    texCoordLoc     = -1;
	extraLoc		= -1;

	modelMatrixLoc	= -1;
    viewMatrixLoc   = -1;
    projMatrixLoc   = -1;

    vertexFile      = NULL;
    fragmentFile    = NULL; 

    setVertexFile(vertFile);
    setFragmentFile(fragFile);
    loadAndCompile();
}

Shader::~Shader()
{
    if(vertexFile)
        delete vertexFile;

    if(fragmentFile)
        delete fragmentFile;

    glDetachShader(program, fragmentShader); // Detach the fragment shader
    glDetachShader(program, vertexShader); // Detach the vertex shader

    glDeleteShader(fragmentShader); // Delete the fragment shader
    glDeleteShader(vertexShader); // Delete the vertex shader
    glDeleteProgram(program); // Delete the shader program
}

void Shader::setVertexFile(const char *vertFile)
{
    if(!vertFile)
    {
        printf("A null-pointer was passed");
        return;
    }

    if(vertexFile)
        delete vertexFile;

    int len = (int)strlen(vertFile);

    vertexFile = new char[len+1];
    strcpy(vertexFile, vertFile);
    vertexFile[len] = '\0';
}

void Shader::setFragmentFile(const char *fragFile)
{
    if(!fragFile)
    {
        printf("A null-pointer was passed");
        return;
    }

    if(fragmentFile)
        delete fragmentFile;

    int len = (int)strlen(fragFile);

    fragmentFile = new char[len+1];
    strcpy(fragmentFile, fragFile);
    fragmentFile[len] = '\0';
}

void printShaderInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;
 
    glGetShaderiv(obj, GL_INFO_LOG_LENGTH,&infologLength);
 
    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
        printf("%s",infoLog);
        free(infoLog);
    }
}
 
void printProgramInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;
 
    glGetProgramiv(obj, GL_INFO_LOG_LENGTH,&infologLength);
 
    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
        printf("%s",infoLog);
        free(infoLog);
    }
}

/*
 * loadAndCompile - create, load, compile and link a shader object.
 */
bool Shader::loadAndCompile()
{
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    printf("attempting to create shader program using \n\t%s \n\t%s\n",vertexFile,fragmentFile);
 
    char *vs = readTextFile(vertexFile);
    char *fs = readTextFile(fragmentFile);

    const char * c_vs = vs;
    const char * c_fs = fs;
 
    if(!vs)
        glShaderSource(vertexShader, 1, &default_vert_shader, NULL);
    else
        glShaderSource(vertexShader, 1, &c_vs, NULL);

    if(!fs)
        glShaderSource(fragmentShader, 1, &default_frag_shader, NULL);
    else
        glShaderSource(fragmentShader, 1, &c_fs, NULL);
 
    free(vs);
    free(fs);
 
    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);
 
    GLint status;

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    if(status == GL_FALSE)
    {
        printShaderInfoLog(vertexShader);
        return false;
    }

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
    if(status == GL_FALSE)
    {
        printShaderInfoLog(fragmentShader);
        return false;
    }

    program = glCreateProgram();
    glAttachShader(program,vertexShader);
    glAttachShader(program,fragmentShader);
 
    glBindAttribLocation(program, POSITION, "in_position");
	glBindAttribLocation(program, TEXCOORD, "in_texCoord");
    glBindAttribLocation(program, NORMAL, "in_normal");
	glBindAttribLocation(program, COLOR, "in_color");
    glBindAttribLocation(program, TANGENT, "in_tangent");
	glBindAttribLocation(program, INDEX, "in_extra");

    glBindFragDataLocation(program, 0, "out_frag0");
    glBindFragDataLocation(program, 1, "out_frag1");
    glBindFragDataLocation(program, 2, "out_frag2");
    glBindFragDataLocation(program, 3, "out_frag3");

    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &status);

    if(status == GL_FALSE)
    {
        printProgramInfoLog(program);
        return false;
    }
 
    positionLoc = glGetAttribLocation(program,"in_position");
    normalLoc = glGetAttribLocation(program, "in_normal");
	colorLoc = glGetAttribLocation(program, "in_color");
    tangentLoc = glGetAttribLocation(program, "in_tangent");
    texCoordLoc = glGetAttribLocation(program, "in_texCoord");
	extraLoc = glGetAttribLocation(program, "in_extra");
 
    projMatrixLoc = glGetUniformLocation(program, "projMatrix");
    viewMatrixLoc = glGetUniformLocation(program, "viewMatrix");
    modelMatrixLoc = glGetUniformLocation(program, "modelMatrix");

    glUseProgram(program);

    char str[10];
    for(int i=0; i<8; ++i)
    {
        sprintf(str, "texture%i",i);
        int textureLoc = glGetUniformLocation(program, str);
        if(textureLoc > -1)
            glUniform1i(textureLoc, i);
    }

    glUseProgram(0);

    compiled = true;

    printf("shader program was successfully created as program %i. \n",program);
 
    return true;
}

GLint Shader::getAttributeLocation(const char *att) const
{
    return glGetAttribLocation(program, att);
}


GLint Shader::getUniformLocation(const char *uni) const
{
    return glGetUniformLocation(program, uni);
}

void Shader::bind()
{
    if(!compiled)
        return;

    glUseProgram(program);
    boundShader = this;
}

void Shader::unbind()
{
    glUseProgram(0);
    boundShader = NULL;
}