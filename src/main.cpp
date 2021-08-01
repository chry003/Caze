#include "caze.hpp"

int main(int argc, char const *argv[])
{
	
	Window window("Caze", 800, 600);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	Shader shader("./src/classes/shaders/basic.vert", "./src/classes/shaders/basic.frag");

	static const GLfloat g_vertex_buffer_data[] = { 
		-0.5, -0.5f * float(sqrt(3)) / 3, 0.0f,
		 0.5, -0.5f * float(sqrt(3)) / 3, 0.0f,
		 0.0,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,
		-0.5 / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,
		 0.5 / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,
		 0.0, -0.5f * float(sqrt(3)) / 3, 0.0f,
	};

	GLuint indices[] =
	{
		0, 3, 5,
		3, 2, 4,
		5, 4, 1
	};

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);



	while(!window.closed())
	{
		window.clear();

		shader.enable();

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// Draw the triangle !
		// glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(0);

		window.update();
	}

	shader.disable();

	return 0;
}