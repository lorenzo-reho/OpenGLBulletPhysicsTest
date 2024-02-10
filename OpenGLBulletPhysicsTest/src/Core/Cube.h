#include "Common.h"
#include "Physics.h"

class Cube {
public:
	Cube();

	void CreateCube();
	unsigned int GetVAO();
	glm::mat4 GetTransformMat4();

private:
	unsigned int _VBO, _EBO, _VAO;
	glm::mat4 transform;

	btBoxShape* pBoxShape;
	btTransform bTransform;
	MotionState* m_pMotionState;
	btRigidBody* pRigidBody;

};
