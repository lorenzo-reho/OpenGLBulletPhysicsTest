#include "Input.h"

namespace Input {
	bool _keys[400];
	bool _keysReleased[400];
	
	bool _mouseButton[12];
	bool _mouseButtonReleased[12];


}

void Input::Update() {

	GLFWwindow* window = GL::GetWindowPtr();

	for (int i = 32; i < 349; i++) {
		_keys[i] = glfwGetKey(window, i) == GLFW_PRESS;
		_keysReleased[i] = glfwGetKey(window, i) == GLFW_RELEASE;
	}
	
	for (int i = 0; i < 12; i++) {
		_mouseButton[i] = glfwGetMouseButton(window, i) == GLFW_PRESS;
		_mouseButtonReleased[i] = glfwGetMouseButton(window, i) == GLFW_RELEASE;
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


bool Input::IsKeyPressed(int key) {
	return _keys[key] ;
}

bool Input::IsKeyReleased(int key) {
	return _keysReleased[key];
}

bool Input::IsMousePressed(int code) {
	return _mouseButton[code];
}


bool Input::IsMouseReleased(int code) {
	return _mouseButtonReleased[code];
}
