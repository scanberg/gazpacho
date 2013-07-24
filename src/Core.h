#ifndef CORE_H
#define CORE_H

#include <string>
#include <vector>
#include <list>

#include <GL/glew.h>
#include <GL/glfw.h>

#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/half_float.hpp>
#include <glm/gtc/quaternion.hpp>

#define EPSILON 1.0e-7
#define PI		3.14159265359

typedef signed char		i8;
typedef signed short	i16;
typedef signed int 		i32;

typedef unsigned char	u8;
typedef unsigned short	u16;
typedef unsigned int	u32;

typedef std::string 	String;

typedef std::vector 	Array;
typedef std::list		List;

using glm::half;
using glm::hvec2;
using glm::hvec3;
using glm::hvec4;

using glm::vec2;
using glm::vec3;
using glm::vec4;

using glm::mat2;
using glm::mat3;
using glm::mat4;

using glm::quat;

using glm::normalize;
using glm::dot;
using glm::cross;
using glm::min;
using glm::max;
using glm::clamp;

#endif