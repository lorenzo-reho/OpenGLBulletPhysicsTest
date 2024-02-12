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
    // glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwWindowHint(GLFW_SAMPLES, 10);

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	
	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(_window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
	ImGui_ImplOpenGL3_Init();

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		return 3;

	return 0;
}

