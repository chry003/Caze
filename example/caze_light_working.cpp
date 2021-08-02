#include "caze.hpp"

int main(int argc, char const *argv[])
{
	
	Window window("Caze", 800, 600);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	GLfloat vertices[] = 
	{
		// -0.5f, -0.5f, 0.0f,
		// -0.5f,  0.5f, 0.0f,
		//  0.5f,  0.5f, 0.0f,
		//  0.5f,  0.5f, 0.0f,
		//  0.5f, -0.5f, 0.0f,
		// -0.5f, -0.5f, 0.0f,
		0, 0, 0,
		8, 0, 0,
		0, 3, 0,
		0, 3, 0,
		8, 0, 0,
		8, 3, 0
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

	// glUniformMatrix4fv(glGetUniformLocation(shader.getShader(), "pr_matrix"), 1, GL_FALSE, ortho.elements);

	shader.setUniformMat4("pr_matrix", ortho);
	shader.setUniformMat4("ml_matrix", mat4::translation(vec3(4, 3, 0)));

	shader.setUniform2f("light_pos", vec2(7.0f, 4.5f));

	shader.setUniform4f("sh_color", vec4(0.3f, 0.1f, 0.6f, 1.0f));

	while(!window.closed())
	{
		window.clear();
		glDrawArrays(GL_TRIANGLES, 0, 6);
		window.update();
	}

	return 0;
}