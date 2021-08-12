#include "caze.hpp"

int main(int argc, char const *argv[])
{
	
	Window window("Caze", 960, 540);

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);


	Shader shader("./include/GLSL/basic.vert", "./include/GLSL/basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);
	shader.setUniformMat4("ml_matrix", mat4::translation(vec3(4, 3, 0)));

	Renderable2D sprite(maths::vec3(5, 5, 0), maths::vec2(4, 4), maths::vec4(1, 0, 1, 1), shader);
	Renderable2D sprite2(maths::vec3(7, 1, 0), maths::vec2(2, 3), maths::vec4(0.2f, 0, 1, 1), shader);

	shader.setUniform4f("sh_color", vec4(1.0f, 1.0f, 1.0f, 1.0f));

	Simple2DRenderer renderer;

	// shader.setUniform2f("light_pos", vec2(0.0f, 0.0f));
	while(!window.closed())
	{
		window.clear();

		double x, y;
		window.getMousePosition(x, y);
		shader.setUniform2f("light_pos", vec2((float)(x * 16.0f / 960.0f), (float)(9.0f - y * 9.0f / 540.0f)));

		renderer.submit(&sprite);
		renderer.submit(&sprite2);
		renderer.flush();

		window.update();
	}

	return 0;
}