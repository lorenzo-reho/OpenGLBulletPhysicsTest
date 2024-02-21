#include "Engine.h"

#include<iostream>
#include<set>


const float RED = 20 / 255.0f;
const float GREEN = 20 / 255.0f;
const float BLUE = 20 / 255.0f;

float deltaTime;
float currentTime;
float lastTime;


bool physicsRun = true;

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
	Shader geometryShader("res/shaders/geometry.vert", "res/shaders/geometry.frag");
	Shader collisionDebugShader("res/shaders/collisionDebug.vert", "res/shaders/collisionDebug.frag");

	ShaderManager::_base = &base;
	ShaderManager::_cubemap = &cubemapShader;
	ShaderManager::_geometry = &geometryShader;
	ShaderManager::_collisionDebug = &collisionDebugShader;

	Camera camera(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0, 0.0f, -1.0f), 5.0f);

	Physics::InitializePhysics();
	Renderer::Init();

	Cube cube(glm::vec3(0.0f, -10.0f, 0.0f), glm::vec3(30.0f, 1.0f, 30.0f), glm::vec3(138 / 255.0f, 138 / 255.0f, 138 / 255.0f));
	Cube cube1(glm::vec3(-0.6f, 30.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0, 1.0, 0));
	Cube cube2(glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0, 0.0, 1.0));
	Cube lightCube(glm::vec3(0, -3.0, 0), glm::vec3(0.4f, 0.4f, 0.4f), glm::vec3(1.0, 1.0, 1.0));


	btBoxShape* pBoxShape = new btBoxShape(btVector3(12.1f, 0.01f, 12.1f));
	btBoxShape* pBoxShape1 = new btBoxShape(btVector3(0.5f, 0.5f, 0.5f));
	btBoxShape* pBoxShape2 = new btBoxShape(btVector3(0.5f, 0.5f, 0.5f));
	btBoxShape* pBoxShape3 = new btBoxShape(btVector3(0.9f, 2.45f, 3.2f));
	btBoxShape* pBoxShape4 = new btBoxShape(btVector3(1.2f, 2.0f, 2.5f));

	/*
	cube.CreateRigidBody(pBoxShape, 0.0f);
	cube.RegisterRigidBody();

	cube1.CreateRigidBody(pBoxShape1, 1.0f);
	cube1.RegisterRigidBody();

	cube2.CreateRigidBody(pBoxShape2, 1.0f);
	cube2.RegisterRigidBody();
	*/
	// Scene::_cubes.push_back(&cube);
	// Scene::_cubes.push_back(&cube1);
	// Scene::_cubes.push_back(&cube2);
	
	// PointLight* pointLight = new PointLight(glm::vec3(0, -3.0, 0), glm::vec3(1, 1, 1), 20.0f, 1.0f, 0.2f, 1.0f, 1.0f);
	PointLight* pointLight = new PointLight(glm::vec3(0, -3.0, 0), glm::vec3(1, 1, 1), 20.0f, 1.0f);
	Scene::_pointLights.push_back(pointLight);

	// Scene::_cubes.push_back(&lightCube);

	vector<std::string> faces
	{
			"res/textures/right.png",
			"res/textures/left.png",
			"res/textures/top.png",
			"res/textures/bottom.png",
			"res/textures/front.png",
			"res/textures/back.png"
	};

	Sky sky(faces);
	sky.CreateSky();

	Scene::_sky = &sky;

	Model *mLocker= new Model("res/models/locker2.obj");
	Model *mFloor= new Model("res/models/floor.obj");
	Model *mBed = new Model("res/models/bed.obj");


	GameObject floor(glm::vec3(0.0f, -10.0f, 0.0f), mFloor, "Floor1");
	floor.CreateRigidBody(pBoxShape, 0.0);
	floor.RegisterRigidBody();

	GameObject locker(glm::vec3(-5.0f, 0.0f, 0.0f), mLocker, "Locker1");
	locker.CreateRigidBody(pBoxShape3, 1.0);
	locker.RegisterRigidBody();

	GameObject bed(glm::vec3(3.0f, -5.0f, -7.5f), mBed, "Bed1");
	bed.CreateRigidBody(pBoxShape4, 1.0);
	bed.RegisterRigidBody();

	GameObject bed1(glm::vec3(7.0f, -5.0f, -7.5f), mBed, "Bed2");
	bed1.CreateRigidBody(pBoxShape4, 1.0);
	bed1.RegisterRigidBody();

	GameObject bed2(glm::vec3(-1.0f, -5.0f, -7.5f), mBed, "Bed3");
	bed2.CreateRigidBody(pBoxShape4, 1.0);
	bed2.RegisterRigidBody();

	Scene::_gameObjects.push_back(&floor);
	Scene::_gameObjects.push_back(&locker);
	Scene::_gameObjects.push_back(&bed);
	Scene::_gameObjects.push_back(&bed1);
	Scene::_gameObjects.push_back(&bed2);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	
	EditingMenu::Init(GL::GetWindowPtr());

	while (GL::IsWindowOpen()) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(RED, GREEN, BLUE, 1.0f);

		EditingMenu::GenerateFrame();
		// ImGui::ShowDemoWindow();

		
		

		currentTime = (float)glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		Input::Update();
		camera.Update(deltaTime);

		for (GameObject* gameObject : Scene::_gameObjects) {
			gameObject->Update(GL::_editingMenu);
		}

		Renderer::Render(camera);

		GL::ProcessInput();

		if (GL::_editingMenu) {
			if(physicsRun){
				Scene::ResetAllGameObject();
			}

			physicsRun = false;
			EditingMenu::ShowModelGeneratorWidget();
			EditingMenu::ShowSceneWidget();
			EditingMenu::ShowTransformWidget();
		}
		else {
			Physics::StepSimulation(deltaTime);
			if (!physicsRun) {
				Scene::ResetAllGameObjectRigidBody();
				physicsRun = true;
			}
			
		}

		EditingMenu::Render();
		GL::SwapBuffersAndPoll();

	}

	EditingMenu::Shutdown();
	GL::Shutdown();

}
