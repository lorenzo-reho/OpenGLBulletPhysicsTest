#include "Engine.h"
#include "Core/Physics.h"

const float RED = 185 / 255.0f;
const float GREEN = 226 / 255.0f;
const float BLUE = 245 / 255.0f;

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
	Shader cubemapShader("res/shaders/cubemap.vert", "res/shaders/cubemap.frag");

	Camera camera(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0, 0.0f, -1.0f), 5.0f);

	Physics::InitializePhysics();
	Renderer::Init();

	Cube cube(glm::vec3(0.0f, -10.0f, 0.0f), glm::vec3(30.0f, 1.0f, 30.0f), glm::vec3(138 / 255.0f, 138 / 255.0f, 138 / 255.0f));
	Cube cube1(glm::vec3(0.0f, 30.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0, 1.0, 0));
	Cube cube2(glm::vec3(-0.6f, 10.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0, 0.0, 1.0));


	cube.CreateCube();
	cube1.CreateCube();
	cube2.CreateCube();


	btBoxShape* pBoxShape = new btBoxShape(btVector3(15, 0.5f, 15.0f));
	btBoxShape* pBoxShape1 = new btBoxShape(btVector3(0.5f, 0.5f, 0.5f));
	btBoxShape* pBoxShape2 = new btBoxShape(btVector3(0.5f, 0.5f, 0.5f));


	cube.CreateRigidBody(pBoxShape, 0.0f);
	cube.RegisterRigidBody();

	cube1.CreateRigidBody(pBoxShape1, 1.0f);
	cube1.RegisterRigidBody();

	cube2.CreateRigidBody(pBoxShape2, 1.0f);
	cube2.RegisterRigidBody();

	Scene::_cubes.push_back(&cube);
	Scene::_cubes.push_back(&cube1);
	Scene::_cubes.push_back(&cube2);

	vector<std::string> faces
	{
			"res/textures/right.jpg",
			"res/textures/left.jpg",
			"res/textures/top.jpg",
			"res/textures/bottom.jpg",
			"res/textures/front.jpg",
			"res/textures/back.jpg"
	};

	Sky sky(faces);
	sky.CreateSky();

	Scene::_sky = &sky;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);

	
	while (GL::IsWindowOpen()) {
		glClearColor(RED, GREEN, BLUE, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		EditingMenu::GenerateFrame();
		// ImGui::ShowDemoWindow();


		currentTime = (float)glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		Input::Update();
		Physics::StepSimulation(deltaTime);

		camera.Update(deltaTime);
		Renderer::Render(camera, base, cubemapShader);

		GL::ProcessInput();

		if(EditingMenu::_debug){
			EditingMenu::ShowModelGeneratorWidget();
			EditingMenu::ShowSceneWidget();
			EditingMenu::ShowTransformWidget();
		}

		EditingMenu::Render();

		GL::SwapBuffersAndPoll();

	}

	EditingMenu::Shutdown();


}
