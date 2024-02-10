#include "Engine.h"


const float RED = 20 / 255.0f;
const float GREEN = 20 / 255.0f;
const float BLUE = 20 / 255.0f;

void Engine::Run() {
	int error = GL::Init(800, 700);

	if (error == 1) {
		std::cerr << "Impossible to initialize GLFW" << std::endl;
		return;
	}
	else if (error == 2) {
		std::cerr << "Impossible to create window" << std::endl;
		return;
	}
	else if (error == 3) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return;
	}

	Shader base("res/shaders/base.vert", "res/shaders/base.frag");

	Renderer::Init();
	// Cube cube;

	while (GL::IsWindowOpen()) {
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(RED, GREEN, BLUE, 1.0f);

		Renderer::Render(base);

		GL::ProcessInput();
		GL::SwapBuffersAndPoll();
	}


}
