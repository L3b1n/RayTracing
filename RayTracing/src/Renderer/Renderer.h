#pragma once

#include "Core/Ray.h"
#include "Core/Image.h"
#include "Core/Camera.h"

#include <glm/glm.hpp>

#include <memory>

namespace RayTracing
{

	class Renderer
	{
	public:
		Renderer() = default;

		void OnResize(uint32_t width, uint32_t height);
		void Render(const Camera& camera);

		std::shared_ptr<Image> GetFinalImage() const { return m_FinalImage; }

	private:
		glm::vec4 TraceRay(const Ray& ray);

	private:
		uint32_t* m_ImageData = nullptr;

		std::shared_ptr<Image> m_FinalImage;
	};

}