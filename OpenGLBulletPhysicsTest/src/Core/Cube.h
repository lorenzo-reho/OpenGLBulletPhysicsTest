#include "Common.h"
#include "Physics.h"

class Cube {
public:
	Cube(glm::vec3 position, glm::vec3 scale);

	glm::mat4 btScalar2mat4(btScalar* matrix);

	void CreateCube();
	unsigned int GetVAO();
	glm::mat4 GetTransformMat4();
	void CreateRigidBody(btBoxShape* pShape, float weight);
	void RegisterRigidBody();
	
private:
	unsigned int _VBO, _EBO, _VAO;
	// glm::mat4 transform;
	glm::vec3 position;
	glm::vec3 scale;

	btBoxShape* pBoxShape;
	btTransform bTransform;
	MotionState* m_pMotionState;
	btRigidBody* pRigidBody;
	btRigidBody::btRigidBodyConstructionInfo* rbInfo;

};
