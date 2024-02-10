#include "GL.h"

namespace GL {
	GLFWwindow* _window;
	unsigned int _currentWidth;
	unsigned int _currentHeight;

}

GLFWwindow* GL::GetWindowPtr() {
	
	return _window;
}

void GL::ProcessInput() {

	if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(_window, 1);
	}


}

bool GL::IsWindowOpen() {
	return !glfwWindowShouldClose(_window);
}

void GL::resize_callback(GLFWwindow* window, int width, int height) {
	_currentWidth = width;
	_currentHeight = height;

	glViewport(0, 0, width, height);
}

void GL::SwapBuffersAndPoll() {
	glfwSwapBuffers(_window);
	glfwPollEvents();

}

unsigned int GL::GetWindowWidth() {
	return _currentWidth;
}

unsigned int GL::GetWindowHeight() {
	return _currentHeight;
}

int GL::Init(int width, int height) {

	if (!glfwInit())
		return 1;


	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_window = glfwCreateWindow(width, height, "TestPhysics", NULL, NULL);
	if (!_window) {
		return 2;
	}

	_currentWidth = width;
	_currentHeight = height;

	glfwMakeContextCurrent(_window);
	glfwSetFramebufferSizeCallback(_window, resize_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		return 3;

	return 0;
}

