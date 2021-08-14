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

#include "maths/maths.hpp"
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

		void setUniform1i(const GLchar* name, int value);
		void setUniform1f(const GLchar* name, float value);
		void setUniform2f(const GLchar* name, const maths::vec2& vector);
		void setUniform3f(const GLchar* name, const maths::vec3& vector);
		void setUniform4f(const GLchar* name, const maths::vec4& vector);
		void setUniformMat4(const GLchar* name, const maths::mat4& matrix);

		void enable() const;
		void disable() const;
		GLuint getShader() const;
	private:
		GLuint load();
		GLint getUniformLocation(const GLchar* name);
	};

} }