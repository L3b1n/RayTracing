#include "Core/Application.h"

#include "Core/Image.h"

class ExampleLayer : public RayTracing::Layer
{
public:
	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Hello");
		ImGui::Button("Button");
		ImGui::End();

		ImGui::ShowDemoWindow();
	}
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
	return 0;
}