#ifndef CUBE_H
#define CUBE_H

#include "Common.h"
#include "Physics.h"

class Cube {
public:
	Cube();
	Cube(glm::vec3 position, glm::vec3 scale, glm::vec3 color);

	glm::mat4 btScalar2mat4(btScalar* matrix);

	void Render();
	unsigned int GetVAO();
	glm::vec3 GetColor();

	glm::mat4 GetTransformMat4();
	void CreateRigidBody(btCollisionShape* pShape, float weight);
	void RegisterRigidBody();
	void SetScale(glm::vec3 size);
	glm::vec3 GetScale();

private:
	unsigned int _VBO, _EBO, _VAO;
	// glm::mat4 transform;
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 color;

	btBoxShape* pBoxShape;
	btTransform bTransform;
	MotionState* m_pMotionState;
	btRigidBody* pRigidBody;
	btRigidBody::btRigidBodyConstructionInfo* rbInfo;
	
	void CreateCube();

};
#endif