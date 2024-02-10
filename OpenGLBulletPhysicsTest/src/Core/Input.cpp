#include "Input.h"

namespace Input {
	bool _keys[400];
}

void Input::Update() {

	GLFWwindow* window = GL::GetWindowPtr();

	// itero i tasti, se è premuto aggiorno il tasto corrente

	for (int i = 32; i <= 349; i++) {
		_keys[i] = glfwGetKey(window, i) == GLFW_PRESS;
	}

}


bool Input::IsPressed(int key) {
	return _keys[key];
}