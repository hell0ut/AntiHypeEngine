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

const float PROP_CONST = 25.0;
const float sensitivity = 0.2;

GLfloat positions[] =
{
	100.0f,10.0f,0.0f,0.0f,
	100.0f,600.0f,1.0f,0.0f,
	600.0f,100.0f,1.0f,1.0f,
	600.0f,600.0f,0.0f,1.0f
};

unsigned int indicies_rec[] = {
	0,1,2,
	2,3,0
};


GLfloat TempColor[] = { 0.9f, 1.0f, 0.0f, 1.0f };

// Vertices coordinates
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



int main()
{
	// Initialize GLFW
	glfwInit();
	//srand(time(0));

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(800, 800, "AntihypeTech Engine", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, 800, 800);

	glm::mat4 proj = glm::ortho(-1.0f,1.0f,-1.0f,1.0f,-1.0f,1.0f);
	glm::mat4 strafe_left = glm::translate(glm::mat4(1.0f), glm::vec3(-0.1 * sensitivity, 0, 0));
	glm::mat4 strafe_right = glm::translate(glm::mat4(1.0f), glm::vec3(0.1* sensitivity, 0, 0));
	glm::mat4 strafe_up = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0.1*sensitivity, 0));
	glm::mat4 strafe_down = glm::translate(glm::mat4(1.0f), glm::vec3(0, -0.1*sensitivity, 0));
	glm::mat4 scale_up =  glm::ortho(-0.8f, 0.8f, -0.8f, 0.8f, -1.0f, 1.0f);
	glm::mat4 scale_down = glm::ortho(-1.2f, 1.2f, -1.2f, 1.2f, -1.0f, 1.0f);
	glm::mat4 mvp = proj;
	// Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	//Texture texture("res/Textures/gorch.png");
	//texture.Bind();
	//shaderProgram.SetUniform1i("u_Texture", 0);



	VAO VAO1;
	VAO1.Bind();


	VBO VBO1(vertices, sizeof(vertices));

	EBO EBO1(indices, sizeof(indices));

	VertexBufferLayout layout;
	layout.push<float>(2);
	//layout.push<float>(2);

	VAO1.LinkVBO(VBO1, layout);

	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	Renderer renderer;

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		//renderer.Draw(VAO1, EBO1, shaderProgram);

		shaderProgram.Activate(TempColor);
		shaderProgram.SetUniformMat4f("u_MVP", mvp);
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		EBO1.Bind();
		glDrawElements(GL_TRIANGLES, EBO1.size, GL_UNSIGNED_INT, nullptr);



		// Draw primitives, number of indices, datatype of indices, index of indices
		if (glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS) {
			mvp*= strafe_up;
		}
		if (glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS) {
			mvp *= strafe_down;
		}
		if (glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS) {
			mvp *= strafe_right;
		}
		if (glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS) {
			mvp *= strafe_left;
		}
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
			glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), 0.2f*sensitivity, glm::vec3(0,0,1.0));
			mvp *= rotationMatrix;
		}
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
			glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), -0.2f*sensitivity, glm::vec3(0,0,1.0));
			mvp *= rotationMatrix;
		}
		if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS) {
			mvp *= scale_up;
		}
		if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS) {
			mvp *= scale_down;
		}

		//float rand1 = rand() % 20 / static_cast<float>(10);
		//float rand2 = rand() % 20 / static_cast<float>(10);
		//proj = glm::ortho(-rand1, rand1, -rand2, rand2, -1.0f, 1.0f);
		//YELLOW[0] = rand() / static_cast<GLfloat>(33000);
		//YELLOW[1] = rand() / static_cast<GLfloat>(33000);
		//YELLOW[2] = rand() / static_cast<GLfloat>(33000);

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}