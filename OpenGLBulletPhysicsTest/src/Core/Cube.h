#include "Common.h"
#include "Physics.h"

class Cube {
public:
	Cube(btVector3 position);

	void CreateCube();
	unsigned int GetVAO();
	glm::mat4 GetTransformMat4();
	void CreateRigidBody(btBoxShape* pShape);
	void RegisterRigidBody();


private:
	unsigned int _VBO, _EBO, _VAO;
	// glm::mat4 transform;

	btBoxShape* pBoxShape;
	btTransform bTransform;
	MotionState* m_pMotionState;
	btRigidBody* pRigidBody;
	btRigidBody::btRigidBodyConstructionInfo* rbInfo;

};
