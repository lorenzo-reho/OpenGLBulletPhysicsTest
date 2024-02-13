#include "EditingMenu.h"


// https://github.com/ocornut/imgui/issues/4430
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
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();
	FileSystem::ExtractModels("res/models");


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

	for (int i = 0; i < FileSystem::_modelsPath.size(); i++)
	{

		char label[128];
		sprintf_s(label, "%s", FileSystem::_modelsPath[i].c_str());
		if (ImGui::Selectable(label, _selectedModel == i))
			_selectedModel = i;
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

	for (int i = 0; i < 10; i++)
	{
		char label[128];
		sprintf_s(label, "Scene element %d", i);
		if (ImGui::Selectable(label, _selectedSceneObject == i))
			_selectedSceneObject = i;
	}

	ImGui::End();
}

void EditingMenu::ShowTransformWidget() {

	ImGui::Begin("Transform");
	float sliderMin = -100;
	float sliderMax = +100;


	if (ImGui::TreeNode("Translate")) {
		static float xt, yt, zt;

		ImGui::SliderFloat("X", &xt, sliderMin, sliderMax, "%.3f", ImGuiSliderFlags_None);
		ImGui::SliderFloat("Y", &yt, sliderMin, sliderMax, "%.3f", ImGuiSliderFlags_None);
		ImGui::SliderFloat("Z", &zt, sliderMin, sliderMax, "%.3f", ImGuiSliderFlags_None);

		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Rotate")) {
	
		static float xr, yr, zr;

		ImGui::SliderFloat("X", &xr, sliderMin, sliderMax, "%.3f", ImGuiSliderFlags_None);
		ImGui::SliderFloat("Y", &yr, sliderMin, sliderMax, "%.3f", ImGuiSliderFlags_None);
		ImGui::SliderFloat("Z", &zr, sliderMin, sliderMax, "%.3f", ImGuiSliderFlags_None);

		ImGui::TreePop();
	}

	ImGui::End();
}