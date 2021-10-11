#pragma once

#include "Renderer.h"

#pragma region Colors
GLfloat YELLOW[] = { 0.9f, 1.0f, 0.0f, 1.0f };
GLfloat RED[] = { 1.0f, 0.0f, 0.0f, 1.0f };//red
GLfloat WHITE[] = { 1.0f, 1.0f, 1.0f, 1.0f };//white
GLfloat PURPLE[] = { 1.0f, 0.0f, 1.0f, 1.0f };//purple
GLfloat LIGHT_BLUE[] = { 0.0f, 1.0f, 1.0f, 1.0f };//light blue
GLfloat BROWN[] = { 1.0f, 0.5f, 0.0f, 1.0f };//orange/brown
GLfloat GREEN[] = { 0.0f, 1.0f, 0.0f , 1.0f };//Green
GLfloat BLUE[] = { 0.0f, 0.0f, 1.0f, 1.0f };//Blue
GLfloat CYAN[] = { 0.5f, 1.0f, 1.0f, 1.0f };//cyan
GLfloat BLACK[] = { 0.0f, 0.0f, 0.0f, 1.0f };//Black
GLfloat ORANGE[] = { 1.0f, 0.5f, 0.0f, 1.0f };//Orange
GLfloat VIOLET[] = { 0.5f, 0.5f, 0.5f , 1.0f };//Violet
#pragma endregion



void Renderer::Draw(VAO& VAO, EBO& IBO, Shader& shader) {
	shader.Activate();
	// Bind the VAO so OpenGL knows to use it
	VAO.Bind();
	IBO.Bind();
	glDrawElements(GL_TRIANGLES, IBO.size, GL_UNSIGNED_INT, nullptr);
}

