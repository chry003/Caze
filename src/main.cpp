#include "caze.hpp"

int main(int argc, char const *argv[])
{
	
	Window window("Caze", 800, 600);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	GLfloat vertices[] = 
	{
		// -0.5f, -0.5f, 0.0f,
		// -0.5f,  0.5f, 0.0f,
		//  0.5f,  0.5f, 0.0f,
		//  0.5f,  0.5f, 0.0f,
		//  0.5f, -0.5f, 0.0f,
		// -0.5f, -0.5f, 0.0f,
		4, 3, 0,
		12, 3, 0,
		4, 6, 0,
		4, 6, 0,
		12, 3, 0,
		12, 6, 0
	};

	GLuint vao, vbo;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader shader("./src/classes/shaders/basic.vert", "./src/classes/shaders/basic.frag");
	shader.enable();

	glUniformMatrix4fv(glGetUniformLocation(shader.getShader(), "pr_matrix"), 1, GL_FALSE, ortho.elements);

	while(!window.closed())
	{
		window.clear();
		glDrawArrays(GL_TRIANGLES, 0, 6);
		window.update();
	}

	return 0;
}