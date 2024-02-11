#include "Input.h"

namespace Input {
	bool _keys[400];
}

void Input::Update() {

	GLFWwindow* window = GL::GetWindowPtr();

	for (int i = 32; i < 349; i++) {
		_keys[i] = glfwGetKey(window, i) == GLFW_PRESS;
	}

}

Utils::MousePosition Input::GetCursorPos() {
	double xpos, ypos;
	GLFWwindow* window = GL::GetWindowPtr();
	glfwGetCursorPos(window, &xpos, &ypos);

	Utils::MousePosition p;
	p.x = xpos;
	p.y = ypos;

	return p;
}


bool Input::IsPressed(int key) {
	return _keys[key];
}