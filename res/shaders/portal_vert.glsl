#version 150
uniform mat4 modelMatrix = mat4(1.0);
uniform mat4 viewMatrix = mat4(1.0);
uniform mat4 projMatrix = mat4(1.0);
uniform vec3 color = vec3(1.0);

uniform vec4 clipPlane = vec4(0.0);

in vec3 in_position;
out vec4 Color;

float gl_ClipDistance[1];

void main(void)
{
    gl_Position = projMatrix * viewMatrix * modelMatrix * vec4(in_position, 1.0);
    vec4 viewPos =  viewMatrix * modelMatrix * vec4(in_position, 1.0);

    gl_ClipDistance[0] = dot(viewPos, clipPlane);
	Color = vec4(color, 1.0);
}