#pragma once

#include "Common.h"
#include <iostream>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "EditingMenu.h"

namespace GL {
	int Init(int width, int height);
	void Shutdown();

	GLFWwindow* GetWindowPtr();
	void ProcessInput();
	unsigned int GetWindowWidth();
	unsigned int GetWindowHeight();
	bool IsWindowOpen();
	void SwapBuffersAndPoll();
	void resize_callback(GLFWwindow* window, int width, int height);
}