#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include"VBO.h"
#include "VertexBufferLayout.h"

class VAO
{
public:
	// ID reference for the Vertex Array Object
	GLuint ID;
	// Constructor that generates a VAO ID
	VAO();

	// Links a VBO to the VAO using a certain layout
	const void LinkVBO(VBO& VBO, const VertexBufferLayout& layout);
	// Binds the VAO
	const void Bind();
	// Unbinds the VAO
	const void Unbind();
	// Deletes the VAO
	const void Delete();
};
#endif