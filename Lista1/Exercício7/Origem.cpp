#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "../Shader.h"
using namespace std;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
int setupGeometry();

int main() {

	glfwInit();
	GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Exercicio 7", NULL, NULL);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	cout << "Renderer: " << renderer << endl;
	cout << "OpenGL version supported " << version << endl;

	unsigned int VAO = setupGeometry();

	Shader shader("../Shaders/vertexSource.vs", "../Shaders/fragmentSource.fs");

	GLint colorLoc = glGetUniformLocation(shader.ID, "inputColor");
	assert(colorLoc > -1);
	glUseProgram(shader.ID);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		glClearColor(0.0f, 0.4f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUniform4f(colorLoc, 0.0f, 1.0f, 0.0f, 1.0f);
		glUseProgram(shader.ID);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glUniform4f(colorLoc, 0.5f, 0.0f, 0.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(6 * sizeof(int)));

		glUniform4f(colorLoc, 0.0f, 0.0f, 0.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(12 * sizeof(int)));

		glUniform4f(colorLoc, 0.5f, 0.5f, 0.5f, 1.0f);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(18 * sizeof(int)));

		glUniform4f(colorLoc, 0.58f, 0.29f, 0.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(21 * sizeof(int)));

		glUniform4f(colorLoc, 0.0f, 0.5f, 0.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(27 * sizeof(int)));

		glfwSwapBuffers(window);
	}
	glDeleteVertexArrays(1, &VAO);

	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int setupGeometry() {
	float squareVertices[] = {
		-1.0f, -1.0f, 0.0f,
		-1.0f, -0.8f, 0.0f,		// Grama
		 1.0f, -0.8f, 0.0f,
		 1.0f, -1.0f, 0.0f,

		-0.7f, -1.0f, 0.0f,
		-0.7f, -0.2f, 0.0f,		// Casa
		-0.1f, -1.0f, 0.0f,
		-0.1f, -0.2f, 0.0f,

		-0.6f, -0.2f, 0.0f,
		-0.7f, -0.2f, 0.0f,		// Chamine
		-0.6f,  0.2f, 0.0f,
		-0.7f,  0.2f, 0.0f,

		-0.8f, -0.2f, 0.0f,
		-0.0f, -0.2f, 0.0f,		// Telhado
		-0.4f,  0.3f, 0.0f,

		 0.6f, -1.0f, 0.0f,
		 0.8f, -1.0f, 0.0f,		// Tronco
		 0.6f, -0.3f, 0.0f,
		 0.8f, -0.3f, 0.0f,

		 0.4f, -0.3f, 0.0f,
		 1.0f, -0.3f, 0.0f,		// Folha
		 0.4f,  0.4f, 0.0f,
		 1.0f,  0.4f, 0.0f
	};

	int indices[] = {
		0, 1, 2,
		0, 2, 3,

		4, 5, 6,
		5, 6, 7,

		8, 9, 10,
		9, 10, 11,

		12, 13, 14,

		15, 16, 17,
		16, 17, 18,

		19, 20, 21,
		20, 21, 22
	};

	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(squareVertices), squareVertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	return VAO;
}
