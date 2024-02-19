#pragma once

#include "Common.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "FileSystem.h"
#include "Scene.h"

namespace EditingMenu {

	inline static int _selectedModel = -1;
	inline static int _selectedSceneObject = -1;

	void Init(GLFWwindow* window);
	void GenerateFrame();
	void Render();

	void Shutdown();
	void ShowModelGeneratorWidget();
	void ShowSceneWidget();
	void ShowTransformWidget();

}