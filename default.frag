#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;


// Inputs the color from the Vertex Shader
smooth in vec4 theColor;
out vec4 outputColor;

void main()
{
	outputColor = theColor;
};

//uniform vec4 u_Color;
//uniform sampler2D u_Texture;