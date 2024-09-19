#pragma once

#include "Core/Image.h"

#include <glm/glm.hpp>

#include <memory>

namespace RayTracing
{

	class Renderer
	{
	public:
		Renderer() = default;

		void OnResize(uint32_t width, uint32_t height);
		void Render();

		std::shared_ptr<Image> GetFinalImage() const { return m_FinalImage; }

	private:
		glm::vec4 PerPixel(glm::vec2 coord);

	private:
		uint32_t* m_ImageData = nullptr;

		std::shared_ptr<Image> m_FinalImage;
	};

}