#pragma once

#include "Common.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GL.h"

namespace EditingMenu {

	inline bool _debug = false;
	void Init(GLFWwindow* window);
	void GenerateFrame();
	void Render();

	void Shutdown();
	void ShowModelGeneratorWidget();
	void ShowSceneWidget();
	void ShowTransformWidget();

}