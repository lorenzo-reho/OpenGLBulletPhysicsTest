#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <BulletDynamics/Dynamics/btDynamicsWorld.h>
#include <btBulletDynamicsCommon.h>
#include <iostream>
#include "Engine.h"

const int WIDTH = 800;
const int HEIGHT = 700;
const float RED = 20 / 255.0f;
const float GREEN = 20 / 255.0f;
const float BLUE = 20 / 255.0f;


/*
// camera control
btVector3 m_cameraPosition; // the camera's current position
btVector3 m_cameraTarget;	 // the camera's lookAt target
float m_nearPlane; // minimum distance the camera will render
float m_farPlane; // farthest distance the camera will render
btVector3 m_upVector; // keeps the camera rotated correctly
float m_cameraDistance; // distance from the camera to its target
float m_cameraPitch; // pitch of the camera 
float m_cameraYaw; // yaw of the camera
int m_screenWidth;
int m_screenHeight;

// core Bullet components
btBroadphaseInterface* m_pBroadphase;
btCollisionConfiguration* m_pCollisionConfiguration;
btCollisionDispatcher* m_pDispatcher;
btConstraintSolver* m_pSolver;
btDynamicsWorld* m_pWorld;


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

*/

int main() {

	Engine::Run();


	return 0;
}