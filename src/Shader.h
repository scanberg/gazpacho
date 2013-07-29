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

#ifndef SHADER_H
#define SHADER_H

#include "Core.h"

class Shader
{
private:
    GLuint program;
    GLuint vertexShader, fragmentShader;

    /*
     * Holders for predefined locations in the shader.
     * The predefined variables are:
     *
     * in_position: position data sent to vertex shader.
     * in_normal: normal data sent to vertex shader.
     * in_texCoord: texture coordinate data sent to vertex shader.
     * in_tangent
     * in_extra
     *
     * modelMatrix: model to world matrix
     * viewMatrix: world to view matrix
     * projMatrix: the projection matrix
     */
     
    GLint positionLoc, texCoordLoc, normalLoc, colorLoc, tangentLoc, extraLoc;
    GLint modelMatrixLoc, viewMatrixLoc, projMatrixLoc;

    char *vertexFile, *fragmentFile;
    bool compiled;

    static Shader *boundShader;
    
public:
    Shader();
    Shader(const char *vertFile, const char *fragFile);
    ~Shader();

    static inline const Shader *getBoundShader() { return boundShader; }

    bool loadAndCompile();

    void setVertexFile(const char *vertFile);
    void setFragmentFile(const char *fragFile);

    inline const char *getVertexFile() { return vertexFile; }
    inline const char *getFragmentFile() { return fragmentFile; }

    GLint getAttributeLocation(const char *att) const;
    GLint getUniformLocation(const char *uni) const;

    inline const GLint & getPositionLocation()	{ return positionLoc; }
    inline const GLint & getNormalLocation()	{ return normalLoc; }
	inline const GLint & getColorLocation()		{ return colorLoc; }
    inline const GLint & getTangentLocation()	{ return tangentLoc; }
    inline const GLint & getTexCoordLocation()	{ return texCoordLoc; }
	inline const GLint & getExtraLocation()		{ return extraLoc; }

    inline const GLint & getModelMatrixLocation() const	{ return modelMatrixLoc; }
    inline const GLint & getViewMatrixLocation() const	{ return viewMatrixLoc; }
    inline const GLint & getProjMatrixLocation() const	{ return projMatrixLoc; }

    inline const bool & isCompiled() { return compiled; }

    void bind();
    void unbind();
};

#endif
