#include "caze.hpp"

int main(int argc, char const *argv[])
{
	
	Window window("Caze", 800, 600);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	while(!window.closed())
	{
		window.clear();
		window.update();
	}

	return 0;
}