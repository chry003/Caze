#include "graphics/window.hpp"


namespace caze { namespace graphics {

	void window_resize(GLFWwindow *window, int width, int height);
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

	Window::Window(const char *title, int width, int height)
	{
		m_title = title;
		m_width = width;
		m_height = height;
		if(!init())
			glfwTerminate();

		for (int i = 0; i < MAX_KEYS; ++i)
			m_Keys[i] = false;


		for (int i = 0; i < MAX_BUTTONS; ++i)
			m_MouseButtons[i] = false;
	}

	Window::~Window()
	{
		glfwTerminate();
	}

	bool Window::init()
	{
		if (!glfwInit())
		{
			std::cout << "Failed to initialize GLFW!" << std::endl;
			return false;
		}

		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	    
		m_window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);

		if (!m_window)
		{
			std::cout << "Failed to create GLFW window!" << std::endl;
			return false;
		}

		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, this);
		glfwSetWindowSizeCallback(m_window, window_resize);
		glfwSetKeyCallback(m_window, key_callback);
		glfwSetMouseButtonCallback(m_window, mouse_button_callback);
		glfwSetCursorPosCallback(m_window, cursor_position_callback);
		
    	gladLoadGL();

		return true;
	}

	void Window::clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::update()
	{
		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
			std::cout << "OpenGL Err: " << error << std::endl;

		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}

	bool Window::closed() const
	{
		return glfwWindowShouldClose(m_window) == 1;
	}

	void window_resize(GLFWwindow *window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Window* win = (Window*) glfwGetWindowUserPointer(window);
		win->m_Keys[key] = action != GLFW_RELEASE;
	}

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		Window* win = (Window*) glfwGetWindowUserPointer(window);
		win->m_MouseButtons[button] = action != GLFW_RELEASE;
	}

	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		Window* win = (Window*) glfwGetWindowUserPointer(window);
		win->mx = xpos;
		win->my = ypos;
	}


	bool Window::isKeyPressed(unsigned int keycode) const
	{
		if (keycode >= MAX_KEYS)
			return false;
		return m_Keys[keycode];
	}

	bool Window::isMouseButtonPressed(unsigned int button) const
	{
		if (button >= MAX_BUTTONS)
			return false;
		return m_MouseButtons[button];
	}

	void Window::getMousePosition(double& x, double& y) const
	{
		x = mx;
		y = my;
	}
} }