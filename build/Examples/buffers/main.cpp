#include "caze.hpp"

int main(int argc, char const *argv[])
{
	
	Window window("Caze", 960, 540);

	// glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

#if 0
	GLfloat vertices[] = 
	{
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
#else
	GLfloat vertices[] = 
	{
		0, 0, 0,
		0, 3, 0,
		8, 3, 0,
		8, 0, 0
	};

	GLushort indices[] = 
	{
		0, 1, 2,
		2, 3, 0
	};

	VertexArray vao;
	Buffer* vbo = new Buffer(vertices, 4 * 3, 3);
	IndexBuffer ibo(indices, 6);

	vao.addBuffer(vbo, 0);

#endif

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader shader("./src/classes/shaders/basic.vert", "./src/classes/shaders/basic.frag");
	shader.enable();

	// glUniformMatrix4fv(glGetUniformLocation(shader.getShader(), "pr_matrix"), 1, GL_FALSE, ortho.elements);

	shader.setUniformMat4("pr_matrix", ortho);
	shader.setUniformMat4("ml_matrix", mat4::translation(vec3(4, 3, 0)));

	shader.setUniform2f("light_pos", vec2(4.0f, 1.5f));

	shader.setUniform4f("sh_color", vec4(0.2f, 0.2f, 0.2f, 1.0f));

	while(!window.closed())
	{
		window.clear();
		double x, y;
		window.getMousePosition(x, y);
		shader.setUniform2f("light_pos", vec2((float)(x * 8.0f / 960.0f), (float)(3.0f - y * 3.0f / 540.0f)));

#if 0
		glDrawArrays(GL_TRIANGLES, 0, 6);
#else
		vao.bind();
		ibo.bind();
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
		ibo.unbind();
		vao.unbind();
#endif
		window.update();
	}

	return 0;
}