#include <btBulletDynamicsCommon.h>
#include "MotionState.h"

namespace Physics{

	void InitializePhysics();
	void ShutdownPhysics();
	void StepSimulation(float deltaTime);
	btDynamicsWorld* GetDynamicsWorld();
}