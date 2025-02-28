#include "GL.h"

namespace GL {
	GLFWwindow* _window;
	unsigned int _currentWidth;
	unsigned int _currentHeight;
	int _mouseWheelOffsetY;
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

	if (width == 0 || height == 0) return;
	_currentWidth = width;
	_currentHeight = height;
	glViewport(0, 0, width, height);

	GBuffer::Configure();

}

void GL::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_TAB && action == GLFW_PRESS)
	{
		_editingMenu = !_editingMenu;
		if (_editingMenu) {
			// TODO: questa � la modalit� spettatore in cui la rotazione della visuale avviene tramite
			// la rotellina, non posso accedere alla Camera
			glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		
		}
		else glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	if (key == GLFW_KEY_X && action == GLFW_PRESS)
	{
		_isCollisionDebug = !_isCollisionDebug;
	}

}

void GL::wheel_callback(GLFWwindow* window, double xoffset, double yoffset) {
	_mouseWheelOffsetY = yoffset;
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

int GL::GetMouseWheelOffsetY() {
	return _mouseWheelOffsetY;
}

void GL::SetMouseWheelOffsetY(int v) {
	_mouseWheelOffsetY = v;
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
	glfwSetKeyCallback(_window, key_callback);
	glfwSetScrollCallback(_window, wheel_callback);
    glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwWindowHint(GLFW_SAMPLES, 10);
	// EditingMenu::Init(_window);


	if (GL::_editingMenu) {
		glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		return 3;

	return 0;
}


void GL::Shutdown() {
	glfwTerminate();
}
