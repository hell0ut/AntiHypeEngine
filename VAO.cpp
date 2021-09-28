#include"VAO.h"
#include <glad/glad.h>

// Constructor that generates a VAO ID
VAO::VAO()
{
	glGenVertexArrays(1, &ID);

}

// Links a VBO to the VAO using a certain layout
const void VAO::LinkVBO(VBO& VBO, const VertexBufferLayout& layout)
{
	Bind();
	VBO.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];

		glVertexAttribPointer(i, element.count, element.type,
			element.normalized, layout.GetStride(), (const void*)offset);
		glEnableVertexAttribArray(i);
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}


	VBO.Unbind();
}


// Binds the VAO
const void VAO::Bind()
{
	glBindVertexArray(ID);
}

// Unbinds the VAO
const void VAO::Unbind()
{
	glBindVertexArray(0);
}

// Deletes the VAO
const void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}