#include "Renderer/Renderer.h"

namespace RayTracing
{

	void Renderer::Render()
	{
		for (uint32_t i = 0; i < m_FinalImage->GetWidth() * m_FinalImage->GetHeight(); i++)
		{
			m_ImageData[i] = 0xffff00ff;
		}

		m_FinalImage->SetData(m_ImageData);
	}

	void Renderer::OnResize(uint32_t width, uint32_t height)
	{
		if (m_FinalImage)
		{
			if (m_FinalImage->GetWidth() == width && m_FinalImage->GetHeight() == height)
				return;

			m_FinalImage->Resize(width, height);
		}
		else
		{
			m_FinalImage = std::make_shared<Image>(width, height, ImageFormat::RGBA);
		}
		
		delete[] m_ImageData;
		m_ImageData = new uint32_t[width * height];
	}

}