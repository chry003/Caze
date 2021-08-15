#include "caze.hpp"
#include <time.h>

#define BATCH_RENDERER 1

int main(int argc, char const *argv[])
{
	
	Window window("Caze", 960, 540);

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);


	Shader shader("./Dependencies/GLSL/basic.vert", "./Dependencies/GLSL/basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);
	// shader.setUniformMat4("ml_matrix", mat4::translation(vec3(4, 3, 0)));

	std::vector<Renderable2D*> sprites;
	srand(time(NULL));

	for (float y = 0; y < 9.0f; y += 0.05)
	{
		for (float x = 0; x < 16.0f; x += 0.05)
		{
			sprites.push_back(new 
#if BATCH_RENDERER
			Sprite
#else
			StaticSprite
#endif
			(x, y, 0.04f, 0.04f, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)
#if !BATCH_RENDERER
			, shader
#endif
			));
		}
	}

#if BATCH_RENDERER
	Sprite sprite(5, 5, 4, 4, maths::vec4(1, 0, 1, 1));
	Sprite sprite2(7, 1, 2, 3, maths::vec4(0.2f, 0, 1, 1));
	BatchRenderer2D renderer;

#else
	StaticSprite sprite(5, 5, 4, 4, maths::vec4(1, 0, 1, 1), shader);
	StaticSprite sprite2(7, 1, 2, 3, maths::vec4(0.2f, 0, 1, 1), shader);
	Simple2DRenderer renderer;
#endif

	shader.setUniform4f("sh_color", vec4(1.0f, 1.0f, 1.0f, 1.0f));


	// shader.setUniform2f("light_pos", vec2(0.0f, 0.0f));
	while(!window.closed())
	{
		window.clear();

		double x, y;
		window.getMousePosition(x, y);
		shader.setUniform2f("light_pos", vec2((float)(x * 16.0f / 960.0f), (float)(9.0f - y * 9.0f / 540.0f)));

#if BATCH_RENDERER
		renderer.begin();
#endif
		for (int i = 0; i < sprites.size(); ++i)
		{
				renderer.submit(sprites[i]);
		}
		renderer.flush();
#if BATCH_RENDERER
		renderer.end();
#endif
		window.update();
	}

	return 0;
}