#pragma once


#include "maths/maths.hpp"
#include <glad/glad.h>
#include "graphics/renderable2d.hpp"


namespace caze { namespace graphics {

	class Renderer2D
	{
	public:
		virtual void submit(const Renderable2D* renderable) = 0;
		virtual void flush() = 0;
	};

} }