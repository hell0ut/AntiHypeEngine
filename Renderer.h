#pragma once

#include <glad/glad.h>
#include"VAO.h"
#include"ShaderClass.h"
#include"VBO.h"
#include"EBO.h"
#include"VertexBufferLayout.h"


class Renderer {
public:
	void Draw(VAO& va, EBO& ib, Shader& shader);
};