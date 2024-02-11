#include "Physics.h"

namespace Physics {
	// core Bullet components
	btBroadphaseInterface* m_pBroadphase;
	btCollisionConfiguration* m_pCollisionConfiguration;
	btCollisionDispatcher* m_pDispatcher;
	btConstraintSolver* m_pSolver;
	btDynamicsWorld* m_pWorld;

	MotionState* m_pMotionState;
	// a simple clock for counting time
	btClock m_clock;

}

void Physics::InitializePhysics() {

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
}

btDynamicsWorld* Physics::GetDynamicsWorld() {
	return m_pWorld;
}

void Physics::StepSimulation(float deltaTime) {
	if(m_pWorld)
		m_pWorld->stepSimulation(deltaTime);
}
