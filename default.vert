#version 330 core

//Positions/Coordinates

// Colors
//layout (location = 1) in vec3 aColor;
layout (location = 0) in vec3 aPos;
uniform vec4 color;
// Outputs the color for the Fragment Shader
// Controls the scale of the vertices
uniform mat4 u_MVP;
smooth out vec4 theColor;

void main()
{
	gl_Position = u_MVP * vec4(aPos.x, aPos.y , aPos.z, 1.0);
	theColor = mix( vec4( color.x, color.y, color.z, color.w ), vec4( 0.0f, color.y, color.z, color.w ), aPos.y / 10 );
}