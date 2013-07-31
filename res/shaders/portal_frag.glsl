#version 150

uniform vec4 clipPlane = vec4(0.0);

in vec4 Color;
out vec4 out_frag0;

void main(void)
{
	if(dot(vec4(gl_FragCoord.xyz,1.0), clipPlane) < 0.0)
		discard;
    out_frag0 = Color;
}