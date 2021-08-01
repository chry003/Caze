#pragma once

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
using namespace std;

#include <stdlib.h>
#include <string.h>

#include <glad/glad.h>

namespace caze { namespace graphics {

	class Shader
	{
	private:
		GLuint m_ShaderID;
		const char* m_VertPath;
		const char* m_FragPath;
	public:
		Shader(const char* vertPath, const char* fragPath);
		~Shader();

		void enable() const;
		void disable() const;
		GLuint getShader() const;
	private:
		GLuint load();
	};

} }