#ifndef GL_H
#define GL_H

#include "Common.h"
#include <iostream>
// #include "Renderer/Renderer.h"
// #include "EditingMenu.h"


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
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	inline bool _editingMenu = false;
	inline bool _isCollisionDebug = false;
}
#endif