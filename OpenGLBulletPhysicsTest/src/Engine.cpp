#include "Engine.h"
#include <btBulletDynamicsCommon.h>
#include "Core/MotionState.h"

const float RED = 20 / 255.0f;
const float GREEN = 20 / 255.0f;
const float BLUE = 20 / 255.0f;

float deltaTime;
float currentTime;
float lastTime;


// core Bullet components
btBroadphaseInterface* m_pBroadphase;
btCollisionConfiguration* m_pCollisionConfiguration;
btCollisionDispatcher* m_pDispatcher;
btConstraintSolver* m_pSolver;
btDynamicsWorld* m_pWorld;

MotionState* m_pMotionState;

// a simple clock for counting time
btClock m_clock;

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
	Camera camera(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0, 0.0f, -1.0f), 5.0f);


	// create the collision configuration
	m_pCollisionConfiguration = new btDefaultCollisionConfiguration();
	// create the dispatcher
	m_pDispatcher = new btCollisionDispatcher(m_pCollisionConfiguration);
	// create the broadphase
	m_pBroadphase = new btDbvtBroadphase();
	// create the constraint solver
	m_pSolver = new btSequentialImpulseConstraintSolver();
	// create the world
	m_pWorld = new btDiscreteDynamicsWorld(m_pDispatcher, m_pBroadphase, m_pSolver, m_pCollisionConfiguration);

	btBoxShape* pBoxShape = new btBoxShape(btVector3(1.0f, 1.0f, 1.0f));
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(0.0f, 0.0f, 0.0f));
	
	m_pMotionState = new MotionState(transform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(1.0f, m_pMotionState, pBoxShape);
	btRigidBody* pRigidBody = new btRigidBody(rbInfo);
	
	m_pWorld->addRigidBody(pRigidBody);

	Renderer::Init();

	while (GL::IsWindowOpen()) {
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(RED, GREEN, BLUE, 1.0f);

		currentTime = (float)glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		Input::Update();

		if (m_pWorld) {
			m_pWorld->stepSimulation(deltaTime);
		}

		btScalar transform[16];
		glm::mat4 glmTransform;
		if (m_pMotionState) {
	
			m_pMotionState->GetWorldTransform(transform);
			
			glmTransform = glm::mat4(transform[0], transform[1], transform[2], transform[3],
				transform[4], transform[5], transform[6], transform[7],
				transform[8], transform[9], transform[10], transform[11],
				transform[12], transform[13], transform[14], transform[15]);
		}


		// Richiamo l'Update di tutti gli oggetti di scena
		camera.Update(deltaTime);

		// Renderizzo gli oggetti di scena
		Renderer::Render(glmTransform, camera, base);

		GL::ProcessInput();
		GL::SwapBuffersAndPoll();
	}


}
