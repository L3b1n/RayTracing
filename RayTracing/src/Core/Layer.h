#pragma once

#include "Core/TimeStep.h"

namespace RayTracing
{

	class Layer
	{
	public:
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}

		virtual void OnUpdate(TimeStep ts) {}
		virtual void OnImGuiRender() {}
	};

}