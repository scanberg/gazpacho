#version 150

uniform vec4 clipPlane = vec4(0.0);

in vec4 Color;
in vec4 WorldPos;
out vec4 out_frag0;

void main(void)
{
	if(dot(WorldPos, clipPlane) < 0.0)
		discard;
    out_frag0 = Color;
}