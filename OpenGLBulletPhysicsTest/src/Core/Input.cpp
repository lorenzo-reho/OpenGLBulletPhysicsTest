#include "Input.h"

namespace Input {
	bool _keys[400];
	bool _keysReleased[400];
	
	bool _mouseButton[12];
	bool _mouseButtonReleased[12];
	bool _mouseWheelDown;
	bool _mouseWheelUp;

	bool _isRecordingCursor = false;

	double _lastX = 0;
	double _lastY = 0;


}

void Input::Update() {
	_mouseWheelDown = false;
	_mouseWheelUp = false;

	GLFWwindow* window = GL::GetWindowPtr();

	for (int i = 32; i < 349; i++) {
		_keys[i] = glfwGetKey(window, i) == GLFW_PRESS;
		_keysReleased[i] = glfwGetKey(window, i) == GLFW_RELEASE;
	}
	
	for (int i = 0; i < 12; i++) {
		_mouseButton[i] = glfwGetMouseButton(window, i) == GLFW_PRESS;
		_mouseButtonReleased[i] = glfwGetMouseButton(window, i) == GLFW_RELEASE;
	}

	if (GL::GetMouseWheelOffsetY() < 0) {
		_mouseWheelDown = true;
	}
	else if (GL::GetMouseWheelOffsetY() > 0) {
		_mouseWheelUp = true;
	}

	GL::SetMouseWheelOffsetY(0);
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


void Input::SetCursorPos(double x, double y) {
	GLFWwindow* window = GL::GetWindowPtr();
	glfwSetCursorPos(window, x, y);
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

bool Input::IsMouseWheelDown() {
	return _mouseWheelDown;
}

bool Input::IsMouseWheelUp() {
	return _mouseWheelUp;
}

