#include "EditingMenu.h"


// https://github.com/ocornut/imgui/issues/4430
// https://github.com/ocornut/imgui/issues/2109
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

	int i = 0;
	for (GameObject *gameObject : Scene::_gameObjects)
	{
		char label[128];
		sprintf_s(label, "%s", gameObject->GetName().c_str());
		if (ImGui::Selectable(label, _selectedSceneObject == i))
			_selectedSceneObject = i;
		i++;
	}

	ImGui::End();
}

void EditingMenu::ShowTransformWidget() {

	ImGui::Begin("Transform");
	
	GameObject* selectedGameObject = NULL;

	if (_selectedSceneObject != -1)
		selectedGameObject = Scene::_gameObjects[_selectedSceneObject];

	if (ImGui::TreeNode("Translate")) {
		float sliderMin = -100;
		float sliderMax = +100;
		static float xt, yt, zt;

		if (selectedGameObject) {
			xt = selectedGameObject->GetPosition().x;
			yt = selectedGameObject->GetPosition().y;
			zt = selectedGameObject->GetPosition().z;
		}


		ImGui::DragFloat("X", &xt, 0.01f, sliderMin, sliderMax, "%.3f", ImGuiSliderFlags_None);
		ImGui::DragFloat("Y", &yt, 0.01f, sliderMin, sliderMax, "%.3f", ImGuiSliderFlags_None);
		ImGui::DragFloat("Z", &zt, 0.01f, sliderMin, sliderMax, "%.3f", ImGuiSliderFlags_None);

		if (selectedGameObject) {
			selectedGameObject->SetPosition(glm::vec3(xt, yt, zt));
			selectedGameObject->ResetTransform();
		}

		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Rotate")) {
		
		float sliderMin = -360;
		float sliderMax = +360;

		static float xr, yr, zr;

		glm::vec3 euler(0);

		if (selectedGameObject) {
			double M_PI = 3.14159265358979323846;
			xr = selectedGameObject->GetRotation().x * 180.0f / M_PI;
			yr = selectedGameObject->GetRotation().y * 180.0f / M_PI;
			zr = selectedGameObject->GetRotation().z * 180.0f / M_PI;
		}


		ImGui::DragFloat("X", &xr, 1.0f, sliderMin, sliderMax, "%.3f", ImGuiSliderFlags_None);
		ImGui::DragFloat("Y", &yr, 1.0f, sliderMin, sliderMax, "%.3f", ImGuiSliderFlags_None);
		ImGui::DragFloat("Z", &zr, 1.0f, sliderMin, sliderMax, "%.3f", ImGuiSliderFlags_None);

		if (selectedGameObject){
			selectedGameObject->SetRotation(glm::vec3(glm::radians(xr), glm::radians(yr), glm::radians(zr)));
			selectedGameObject->ResetTransform();
		}
		ImGui::TreePop();
	}

	ImGui::End();
}