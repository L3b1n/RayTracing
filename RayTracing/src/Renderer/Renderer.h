#pragma once

#include "Core/Ray.h"
#include "Core/Scene.h"
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
		void Render(const Scene& scene, const Camera& camera);

		std::shared_ptr<Image> GetFinalImage() const { return m_FinalImage; }

	private:
		struct HitPayload
		{
			float HitDistance;
			glm::vec3 WorldPosition;
			glm::vec3 WorldNormal;

			int ObjectIndex;
		};

	private:
		glm::vec4 RayGen(uint32_t x, uint32_t y);
		HitPayload TraceRay(const Ray& ray);
		HitPayload ClosestHit(const Ray& ray, float hitDistance, int objectIndex);
		HitPayload Miss(const Ray& ray);

	private:
		uint32_t* m_ImageData = nullptr;

		const Scene* m_ActiveScene = nullptr;
		const Camera* m_ActiveCamera = nullptr;

		std::shared_ptr<Image> m_FinalImage;
	};

}