#version 150
uniform mat4 modelMatrix = mat4(1.0);
uniform mat4 viewMatrix = mat4(1.0);
uniform mat4 projMatrix = mat4(1.0);
uniform vec3 color = vec3(1.0);

in vec3 in_position;
out vec4 Color;
out vec4 ViewPos;

void main(void)
{
    gl_Position = projMatrix * viewMatrix * modelMatrix * vec4(in_position, 1.0);
    ViewPos =  viewMatrix * modelMatrix * vec4(in_position, 1.0);
	Color = vec4(color, 1.0);
}