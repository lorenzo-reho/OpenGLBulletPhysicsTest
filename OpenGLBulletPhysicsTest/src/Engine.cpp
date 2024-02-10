#include "Engine.h"


const float RED = 20 / 255.0f;
const float GREEN = 20 / 255.0f;
const float BLUE = 20 / 255.0f;

float deltaTime;
float currentTime;
float lastTime;

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
	Camera camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0, 0.0f, -1.0f), 5.0f);

	Renderer::Init();
	// Cube cube;

	while (GL::IsWindowOpen()) {
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(RED, GREEN, BLUE, 1.0f);

		currentTime = (float)glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		Input::Update();

		// Richiamo l'Update di tutti gli oggetti di scena
		camera.Update(deltaTime);

		// Renderizzo gli oggetti di scena
		Renderer::Render(camera, base);

		GL::ProcessInput();
		GL::SwapBuffersAndPoll();
	}


}
