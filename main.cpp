#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"ShaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"VertexBufferLayout.h"
//#include <ctime>
#include "Renderer.h"
#include "Texture.h"
#include "res/glm/glm.hpp"
#include "res/glm/gtc/matrix_transform.hpp"
#include <vector>


struct position {
	GLfloat x;
	GLfloat y;
	GLfloat z;
};

GLuint program;
struct position axis[6];
struct position axis_marks[600];
int graph_samples = 30;
const int estimated_polys = 3600;
int graph_size = 100;
int graph_y_scale = 50;
GLuint buffer_axis;
GLuint buffer_axis_marks;
GLuint vao;
GLuint buffer_3d_1;		
GLuint uniform_color;


const float PROP_CONST = 25.0;
const float sensitivity = 0.2;


float Z(float x, float y) {
	return sin(x) + cos(y);
}



unsigned int indicies_rec[] = {
	0,1,2,
	2,3,0
};


//GLfloat TempColor[] = { 0.9f, 1.0f, 0.0f, 1.0f };

#pragma region LAB1
GLfloat vertices[] =
{
	7.0f/PROP_CONST, 0.0f,  //0
	-6.0f / PROP_CONST, 15.0f/PROP_CONST, //1		-6 15
	-6.0f / PROP_CONST, 21.0f / PROP_CONST, //2		-6 21
	-12.0f / PROP_CONST, 15.0f / PROP_CONST, //3	-12 15
	-6.0f / PROP_CONST, 4.0f / PROP_CONST, //4		-6	4
	-10.0f / PROP_CONST, 0.0f / PROP_CONST, //5		-10 0
	-6.0f / PROP_CONST, -4.0f / PROP_CONST, //6		-6 -4
	-6.0f / PROP_CONST, 0.0f / PROP_CONST, //7		-6 0
	-5.0f / PROP_CONST, -5.0f / PROP_CONST, //8		-5 -5
	0.0f / PROP_CONST, -10.0f / PROP_CONST, //9		0 -9
	5.0f / PROP_CONST, -5.0f / PROP_CONST, //10		5 -5
	0.0f / PROP_CONST, 0.0f / PROP_CONST, //11		0 0
	10.0f / PROP_CONST, 0.0f / PROP_CONST, //12		10 0
	10.0f / PROP_CONST, -10.0f / PROP_CONST, //13	10 -10
	19.0f / PROP_CONST, -10.0f / PROP_CONST, //14	19 -10
	23.0f / PROP_CONST, -14.0f / PROP_CONST, //15	23 -14
	14.0f / PROP_CONST, -14.0f / PROP_CONST, //16	14 -14
	-4.0f / PROP_CONST, -14.0f / PROP_CONST, //17	-4 -14
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 7, 
	1, 2, 3, 
	4, 5, 6,
	11,12,13,
	11,8,9,
	11,10,9,
	17,16,10,
	13,14,15,
	13,16,15
};

#pragma endregion

#pragma region Cube

GLfloat cube_verticies[] = {

	// VERTEX INDICIES		COLORS
	0.0f,0.0f,0.0f,		0.9f, 1.0f, 0.0f,
	1.0f,0.0f,0.0f,		1.0f, 0.0f, 0.0f,
	1.0f,1.0f,0.0f,		0.31f,0.47f,0.26f,
	0.0f,1.0f,0.0f,		1.0f, 0.0f, 1.0f,
	
	1.0f,0.0f,1.0f,		1.0f, 0.5f, 0.0f,
	0.0f,1.0f,1.0f,		0.5f, 0.5f, 0.5f,
	1.0f,1.0f,1.0f,		0.5f, 1.0f, 1.0f,
	0.0f,0.0f,1.0f,		0.0f, 1.0f, 1.0f
};


GLuint cube_indicies[] = {
	
	0,3,1,
	1,2,3,

	1,4,2,
	4,6,2,

	4,1,0,
	0,7,4,

	0,3,7,
	7,3,5,

	6,4,7,
	7,5,6,

	3,2,6,
	3,6,5

};

#pragma endregion

#pragma region Octahendron
GLfloat octahedron_verticies[] = {
	//     COORDINATES     /        COLORS      /   TexCoord  //
	   -0.5f, 0.0f,  0.5f,     0.31f,0.47f,0.26f,//	0.0f, 0.0f,
	   -0.5f, 0.0f, -0.5f,     0.13f,0.55f,0.13f,//	5.0f, 0.0f,
		0.5f, 0.0f, -0.5f,     0.49f,0.99f,0.0f,//	0.0f, 0.0f,
		0.5f, 0.0f,  0.5f,     0.0f,1.0f,0.0f,//	5.0f, 0.0f,
		0.0f, 0.8f,  0.0f,     0.31f,0.47f,0.26f,//	2.5f, 5.0f
		0.0f, -0.8f,  0.0f,    0.31f,0.47f,0.26f,//	2.5f, 5.0f
};

GLuint octahedron_indicies[] = {
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4,

	0, 1, 5,
	1, 2, 5,
	2, 3, 5,
	3, 0, 5,
};

#pragma endregion


#pragma region Transform_matricies
glm::mat4 strafe_left = glm::translate(glm::mat4(1.0f), glm::vec3(-0.1 * sensitivity, 0, 0));
glm::mat4 strafe_right = glm::translate(glm::mat4(1.0f), glm::vec3(0.1 * sensitivity, 0, 0));
glm::mat4 strafe_up = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0.1 * sensitivity, 0));
glm::mat4 strafe_down = glm::translate(glm::mat4(1.0f), glm::vec3(0, -0.1 * sensitivity, 0));
glm::mat4 scale_up = glm::ortho(-0.8f, 0.8f, -0.8f, 0.8f, -0.8f, 0.8f);
glm::mat4 scale_down = glm::ortho(-1.2f, 1.2f, -1.2f, 1.2f, -1.2f, 1.2f);
glm::mat4 mvp1 = glm::ortho(-1.0f, 1.0f,
	-1.0f, 1.0f,
	-1.0f, 1.0f);
glm::mat4 mvp2 = glm::ortho(-1.0f, 0.0f, -1.0f, 0.0f, -1.0f, 1.0f);
glm::mat4 mvp3 = glm::ortho(-1.0f, 1.0f,
	-1.0f, 1.0f,
	-1.0f, 1.0f);
#pragma endregion


#pragma region Axes

void generateLines() {

	//axis lines
	//x
	axis[0].x = -graph_size;
	axis[0].y = 0;
	axis[0].z = 0;
	axis[1].x = graph_size;
	axis[1].y = 0;
	axis[1].z = 0;
	//y
	axis[2].x = 0;
	axis[2].y = -graph_size;
	axis[2].z = 0;
	axis[3].x = 0;
	axis[3].y = graph_size;
	axis[3].z = 0;
	//z
	axis[4].x = 0;
	axis[4].y = 0;
	axis[4].z = graph_size;
	axis[5].x = 0;
	axis[5].y = 0;
	axis[5].z = -graph_size;



}

void generate_axis_marks() {
	//axis marks
	int i;
	int index = 0;
	//x
	for (i = -graph_size; i < graph_size; ++i) {
		if (i % 2 != 0) continue; //only every 2 points
		axis_marks[index].x = i;
		axis_marks[index].y = 0;
		axis_marks[index].z = 0;
		index++;
		axis_marks[index].x = i;
		axis_marks[index].y = 1;
		axis_marks[index].z = 0;
		index++;
	}
	//y
	for (i = -graph_size; i < graph_size; ++i) {
		if (i % 2 != 0) continue;
		axis_marks[index].x = 0;
		axis_marks[index].y = i;
		axis_marks[index].z = 0;
		index++;
		axis_marks[index].x = 1;
		axis_marks[index].y = i;
		axis_marks[index].z = 0;
		index++;
	}
	//z
	for (i = -graph_size; i < graph_size; ++i) {
		if (i % 2 != 0) continue;
		axis_marks[index].x = 0;
		axis_marks[index].y = 0;
		axis_marks[index].z = i;
		index++;
		axis_marks[index].x = 0;
		axis_marks[index].y = 1;
		axis_marks[index].z = i;
		index++;
	}


}


#pragma endregion
 

void draw_graph() {
	int i;
	glUniform4f(uniform_color, 0, 1, 0, 1);
	glBindBuffer(GL_ARRAY_BUFFER, buffer_axis);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_LINES, 0, 9);
	glDisableVertexAttribArray(0);

	//axis marks
	glBindBuffer(GL_ARRAY_BUFFER, buffer_axis_marks);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_LINES, 0, 600);
	glDisableVertexAttribArray(0);

	glUniform4f(uniform_color, 1, 0.5, 0.1, 1);
	// graph
	glBindBuffer(GL_ARRAY_BUFFER, buffer_3d_1);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	for (i = 0; i < graph_samples * 2; i++) {
		glDrawArrays(GL_LINE_STRIP, i * graph_samples * 2, graph_samples * 2);
	}
	glDisableVertexAttribArray(0);
	//color for 3d graph pt 2



}



int main()
{
	// Initializing OPENGL, window, shader, etc.
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(800, 800, "AntihypeTech Engine", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	gladLoadGL();
	glViewport(0, 0, 800, 800);

	//Textures testing
	{
		//Texture texture("res/Textures/gorch.png");
		//texture.Bind();
		//shaderProgram.SetUniform1i("u_Texture", 0);
	}

	// Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");
	program = shaderProgram.ID;
	uniform_color = glGetUniformLocation(program, "color");
	VertexBufferLayout layout;
	layout.push<float>(3);
	layout.push<float>(3);

	//octahedron
	
	//VAO VAO1;
	//VAO1.Bind();
	//VBO VBO1(octahedron_verticies, sizeof(octahedron_verticies));
	//EBO EBO1(octahedron_indicies, sizeof(octahedron_indicies));

	//VAO1.LinkVBO(VBO1, layout);
	//VAO1.Unbind();
	//VBO1.Unbind();
	//EBO1.Unbind();



	//cube

	//VAO VAO2;
	//VBO VBO2(cube_verticies, sizeof(cube_verticies));
	//EBO EBO2(cube_indicies, sizeof(cube_indicies));
	//VAO2.LinkVBO(VBO2, layout);
	//VAO2.Unbind();
	//VBO2.Unbind();
	//EBO2.Unbind();



	//graph axes
	generateLines();
	generate_axis_marks();
	
	glGenBuffers(1, &buffer_axis);
	glBindBuffer(GL_ARRAY_BUFFER, buffer_axis);
	//assign axis data
	glBufferData(GL_ARRAY_BUFFER, sizeof(axis), axis, GL_STATIC_DRAW);


	glGenBuffers(1, &buffer_axis_marks);
	glBindBuffer(GL_ARRAY_BUFFER, buffer_axis_marks);
	//assign axis_marks data
	glBufferData(GL_ARRAY_BUFFER, sizeof(axis_marks), axis_marks, GL_STATIC_DRAW);
	
	//int estimatedPolys = pow(graph_samples * 2, 2);
	struct position graph_3d_1[estimated_polys];


	int i, j;
	int index = 0;


	//generate graph_3d_1
	for (i = -graph_samples; i < graph_samples; i++) {
		for (j = -graph_samples; j < graph_samples; j++) {
			graph_3d_1[index].x = i;
			graph_3d_1[index].z = j;
			float d = sqrt(i * i + j * j);
			if (d == 0.0)
				d = 1;

			graph_3d_1[index].y = (sin(d) / d) * graph_y_scale;

			index++;
		}
	}

	glGenBuffers(1, &buffer_3d_1);
	glBindBuffer(GL_ARRAY_BUFFER, buffer_3d_1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(graph_3d_1), graph_3d_1, GL_STATIC_DRAW);
	
	/*
	{

		float Zs[300];
		float x_i = 0, y_i = 0;
		int xi = 0, yi = 0;
		while (x_i < 1) {
			while (y_i < 1) {
				unsigned int loc_i = xi * 10 + yi;
				Zs[loc_i * 3] = x_i;
				Zs[loc_i * 3 + 1] = y_i;
				Zs[loc_i * 3 + 2] = Z(x_i, y_i);
				//std::cout << Zs[loc_i] << " " << Zs[loc_i + 1] << " " << Zs[loc_i + 2] << std::endl;
				y_i += 0.1;
				yi += 1;
			}
			x_i += 0.1;
			xi += 1;
			y_i = 0;
			yi = 0;
		}





		GLuint Zs_i[180];
		for (unsigned int x_i = 0; x_i < 90; x_i++) {
			if (x_i % 10 == 9 && x_i != 0) continue;
			Zs_i[x_i * 2] = x_i;
			Zs_i[x_i * 2 + 1] = x_i + 1;
			//std::cout << Zs_i[x_i * 2] << " " << Zs_i[x_i*2+1] <<  std::endl;
		}


		GLuint Zs_i2[180];
		for (unsigned int x_i = 0; x_i < 90; x_i++) {
			if (x_i % 10 == 9 && x_i != 0) continue;
			Zs_i[x_i * 2] = x_i % 10 * 10 + x_i / 10;
			Zs_i[x_i * 2 + 1] = (x_i + 1) % 10 * 10 + (x_i + 1) / 10;
			std::cout << Zs_i[x_i * 2] << " " << Zs_i[x_i * 2 + 1] << std::endl;
		}
		VertexBufferLayout layout2;
		layout2.push<float>(3);



		VAO VAO3;
		VBO VBO3(Zs, sizeof(Zs));
		EBO EBO3(Zs_i, sizeof(Zs_i));
		EBO EBO4(Zs_i2, sizeof(Zs_i2));
		VAO3.LinkVBO(VBO3, layout2);
		VAO3.Unbind();
		VBO3.Unbind();
		EBO3.Unbind();
	}
	*/
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f); //background
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shaderProgram.Activate();//activating shader

		//octahedron rendering with its mvp matrix

		shaderProgram.SetUniformMat4f("u_MVP", mvp1);
		draw_graph();
		//VAO1.Bind();
		//EBO1.Bind();
		//glDrawElements(GL_TRIANGLES, EBO1.size, GL_UNSIGNED_INT, nullptr);

		//cube rendering

		//shaderProgram.SetUniformMat4f("u_MVP", mvp2);
		//VAO2.Bind();
		//EBO2.Bind();
		//glDrawElements(GL_TRIANGLES, EBO2.size, GL_UNSIGNED_INT, nullptr);






		if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) mvp1 *= strafe_up;
			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) mvp1 *= strafe_down;
			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) mvp1 *= strafe_right;
			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) mvp1 *= strafe_left;
			if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS) mvp1 *= scale_up;
			if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS) mvp1 *= scale_down;
			if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
				glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), 0.2f * sensitivity, glm::vec3(1.0, 0, 0));
				mvp1 *= rotationMatrix;
			}
			if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
				glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), -0.2f * sensitivity, glm::vec3(0, 1.0, 0));
				mvp1 *= rotationMatrix;
			}

		}

		if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) mvp2 *= strafe_up;
			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) mvp2 *= strafe_down;
			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) mvp2 *= strafe_right;
			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) mvp2 *= strafe_left;
			if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS) mvp2 *= scale_up;
			if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS) mvp2 *= scale_down;
			if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
				glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), 0.2f * sensitivity, glm::vec3(1.0, 0, 0));
				mvp2 *= rotationMatrix;
			}
			if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
				glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), -0.2f * sensitivity, glm::vec3(0, 1.0, 0));
				mvp2 *= rotationMatrix;
			}

		}

	/*	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) mvp3 *= strafe_up;
			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) mvp3 *= strafe_down;
			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) mvp3 *= strafe_right;
			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) mvp3 *= strafe_left;
			if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS) mvp3 *= scale_up;
			if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS) mvp3 *= scale_down;
			if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
				glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), 0.2f * sensitivity, glm::vec3(1.0, 0, 0));
				mvp3 *= rotationMatrix;
			}
			if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
				glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), -0.2f * sensitivity, glm::vec3(0, 1.0, 0));
				mvp3 *= rotationMatrix;
			}
		}
		*/


		glfwSwapBuffers(window);
		glfwPollEvents();
	}




	// Delete all the objects we've created

	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}