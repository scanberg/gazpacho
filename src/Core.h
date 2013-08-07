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
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>

#define EPSILON 1.0e-6
#define PI		3.14159265359

typedef signed char		i8;
typedef signed short	i16;
typedef signed int 		i32;

typedef unsigned char	u8;
typedef unsigned short	u16;
typedef unsigned int	u32;

typedef glm::half 		f16;
typedef float 			f32;
typedef double			f64;

using glm::hvec2;
using glm::hvec3;
using glm::hvec4;

using glm::vec2;
using glm::vec3;
using glm::vec4;

using glm::ivec2;
using glm::ivec3;
using glm::ivec4;

using glm::uvec2;
using glm::uvec3;
using glm::uvec4;

using glm::mat2;
using glm::mat3;
using glm::mat4;

using glm::quat;

using glm::normalize;
using glm::dot;
using glm::cross;
using glm::length;
using glm::min;
using glm::max;
using glm::clamp;

class Bone;
class Bounds;
class Camera;
class Frame;
class Frustum;
class GameObject;
class Material;
class Mesh;
class Material;
class Module;
class Plane;
class Portal;
class Skeleton;
class Transform;

#endif