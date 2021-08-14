#pragma once

#include <glad/glad.h>

namespace caze { namespace graphics {

	class Buffer
	{
	private:
		GLuint m_BufferID;
		GLuint m_ComponenetCount;
	public:
		Buffer(GLfloat* data, GLsizei count, GLuint componenetCount);
		~Buffer();

		void bind() const;
		void unbind() const;

		inline GLuint getComponentCount() const { return m_ComponenetCount; }
	};

} }