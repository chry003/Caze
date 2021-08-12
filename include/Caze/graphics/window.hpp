#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace caze { namespace graphics {

#define MAX_KEYS 	1024
#define MAX_BUTTONS 32

	class Window
	{
	private:
		const char *m_title;
		int m_width, m_height;
		GLFWwindow *m_window;
		bool m_closed;

		bool m_Keys[MAX_KEYS];
		bool m_MouseButtons[MAX_BUTTONS];
		double mx, my;
	public:
		Window(const char *title, int widht, int height);
		~Window();
		void clear() const;
		void update();
		bool closed() const;

		inline int getWidht() const { return m_width; };
		inline int getHeight() const { return m_height; };

		bool isKeyPressed(unsigned int keycode) const;
		bool isMouseButtonPressed(unsigned int button) const;
		void getMousePosition(double& x, double& y) const;

	private:
		bool init();
		friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		friend void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	};

} }