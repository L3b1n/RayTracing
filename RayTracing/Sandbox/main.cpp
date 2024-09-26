#include "Core/Image.h"
#include "Core/Timer.h"
#include "Core/Camera.h"
#include "Core/Application.h"

#include "Renderer/Renderer.h"

bool g_ApplicationRunning = true;

class ExampleLayer : public RayTracing::Layer
{
public:
	ExampleLayer()
		: m_Camera(45.0f, 0.1f, 100.0f)
	{
	}

	virtual void OnUpdate(RayTracing::TimeStep ts) override
	{
		m_Camera.OnUpdate(ts);
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::Text("Last render: %.3fms", m_LastRenderTime);
		if (ImGui::Button("Render"))
		{
			Render();
		}
		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("Viewport");

		m_ViewportWidth  = (uint32_t)ImGui::GetContentRegionAvail().x;
		m_ViewportHeight = (uint32_t)ImGui::GetContentRegionAvail().y;

		auto image = m_Renderer.GetFinalImage();
		if (image)
			ImGui::Image(image->GetDescriptorSet(), { (float)image->GetWidth(), (float)image->GetHeight()}, ImVec2(0, 1), ImVec2(1, 0));

		ImGui::End();
		ImGui::PopStyleVar();

		Render();
	}

	void Render()
	{
		RayTracing::Timer timer;

		m_Renderer.OnResize(m_ViewportWidth, m_ViewportHeight);
		m_Camera.OnResize(m_ViewportWidth, m_ViewportHeight);
		m_Renderer.Render(m_Camera);

		m_LastRenderTime = timer.ElapsedMillis();
	}

private:
	float m_LastRenderTime = 0.0f;

	uint32_t m_ViewportWidth = 0;
	uint32_t m_ViewportHeight = 0;

	RayTracing::Camera m_Camera;
	RayTracing::Renderer m_Renderer;
};

int main(int argc, char** argv)
{
	RayTracing::ApplicationSpecification spec;
	spec.Name = "Walnut Example";

	RayTracing::Application* app = new RayTracing::Application(spec);
	app->PushLayer<ExampleLayer>();
	app->SetMenubarCallback([app]()
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Exit"))
				{
					app->Close();
				}
				ImGui::EndMenu();
			}
		});

	while (g_ApplicationRunning)
	{
		app->Run();
		delete app;
	}
	return 0;
}