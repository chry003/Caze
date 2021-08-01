#include "caze.hpp"

int main(int argc, char const *argv[])
{
	
	Window window("Caze", 800, 600);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	vec2 vector2A(1.0f, 3.0f);
	vec2 vector2B(1.0f, 3.0f);

	vector2A += vector2B;

	std::cout << vector2A << std::endl;

	while(!window.closed())
	{
		window.clear();
		window.update();
	}

	return 0;
}