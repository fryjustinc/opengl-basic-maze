//#version 130

uniform mat4 M;
varying vec4 gl_FrontColor;
varying vec4 gl_BackColor;
varying vec4 gl_Color;
attribute vec3 pos;
//in vec2 pos;

void main()
{	
	gl_FrontColor=vec4(pos.x/8.0,pos.y/8.0,pos.z,1.0);
	gl_BackColor=vec4(pos.x/8.0,pos.y/8.0,pos.z,1.0);
	vec4 p = vec4(pos, 1);
	gl_Position = M*p;
}
