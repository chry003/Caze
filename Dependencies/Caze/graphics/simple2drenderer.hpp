#pragma once

#include <deque>
#include "renderer2d.hpp"

namespace caze { namespace graphics {

	class Simple2DRenderer : public Renderer2D
	{
	private:
		std::deque<const Renderable2D*> m_RenderQueue;
	public:
		void submit(const Renderable2D* renderable) override;
		void flush() override;
	};
} }