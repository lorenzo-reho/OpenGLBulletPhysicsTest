#ifndef GL_H
#define GL_H

#include "Common.h"
#include <iostream>
#include "GBuffer.h"
//#include "Renderer/Renderer.h"
//#include "EditingMenu.h"

namespace GL {
	int Init(int width, int height);
	void Shutdown();

	GLFWwindow* GetWindowPtr();
	void ProcessInput();
	unsigned int GetWindowWidth();
	unsigned int GetWindowHeight();
	int GetMouseWheelOffsetY();
	void SetMouseWheelOffsetY(int v);

	bool IsWindowOpen();
	void SwapBuffersAndPoll();
	void resize_callback(GLFWwindow* window, int width, int height);
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void wheel_callback(GLFWwindow* window, double xoffset, double yoffset);

	inline bool _editingMenu = true;
	inline bool _isCollisionDebug = false;
}
#endif