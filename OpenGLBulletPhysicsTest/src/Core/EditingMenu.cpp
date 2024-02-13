#include "EditingMenu.h"

void EditingMenu::Init(GLFWwindow *window) {
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;


	// io.IniSavingRate = -1.0f;
	// io.IniFilename = NULL;
	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
	ImGui_ImplOpenGL3_Init();
}

void EditingMenu::GenerateFrame() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void EditingMenu::Shutdown() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void EditingMenu::Render() {
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void EditingMenu::ShowModelGeneratorWidget() {
	ImGui::SetNextWindowSize(ImVec2(300, 0), ImGuiCond_FirstUseEver);
	
	if (!ImGui::Begin("Models"))
	{
		ImGui::End();
		return;
	}

	static int selected = 0;
	{
		for (int i = 0; i < 10; i++)
		{
			char label[128];
			sprintf_s(label, "Model element %d", i);
			if (ImGui::Selectable(label, selected == i))
				selected = i;
		}
	}

	ImGui::Button("Generate");
	ImGui::End();
}

void EditingMenu::ShowSceneWidget() {
	ImGui::SetNextWindowSize(ImVec2(300, 0), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin("Scene"))
	{
		ImGui::End();
		return;
	}

	static int selected = 0;
	{
		for (int i = 0; i < 10; i++)
		{
			char label[128];
			sprintf_s(label, "Scene element %d", i);
			if (ImGui::Selectable(label, selected == i))
				selected = i;
		}
	}

	ImGui::End();
}

void EditingMenu::ShowTransformWidget() {

	ImGui::Begin("Transform");

	if (ImGui::TreeNode("Translate")) {
		static float xt, yt, zt;

		ImGui::SliderFloat("X", &xt, 0.0f, 1.0f, "%.3f", ImGuiSliderFlags_None);
		ImGui::SliderFloat("Y", &yt, 0.0f, 1.0f, "%.3f", ImGuiSliderFlags_None);
		ImGui::SliderFloat("Z", &zt, 0.0f, 1.0f, "%.3f", ImGuiSliderFlags_None);

		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Rotate")) {
	
		static float xr, yr, zr;

		ImGui::SliderFloat("X", &xr, 0.0f, 1.0f, "%.3f", ImGuiSliderFlags_None);
		ImGui::SliderFloat("Y", &yr, 0.0f, 1.0f, "%.3f", ImGuiSliderFlags_None);
		ImGui::SliderFloat("Z", &zr, 0.0f, 1.0f, "%.3f", ImGuiSliderFlags_None);

		ImGui::TreePop();
	}

	ImGui::End();
}