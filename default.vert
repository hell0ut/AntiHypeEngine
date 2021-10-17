#version 330 core


layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
//uniform vec4 color;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
smooth out vec4 theColor;

void main()
{
	gl_Position = projection * view * model * vec4(aPos.x, aPos.y , aPos.z, 1.0);
	theColor = mix( vec4( aColor.x, aColor.y, aColor.z, 1.0 ), vec4( 0.0f, aColor.y, aColor.z, 1.0 ), aPos.y / 10 );
}