#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Common.h"
#include "Physics.h"
#include "Renderer/Model.h"

class GameObject {

public:
	
	GameObject(glm::vec3 position, Model *model);
	
	void Update(); 
	void Render(Shader &shader);

	glm::mat4 btScalar2mat4(btScalar* matrix);
	glm::mat4 GetTransformMat4();
	void CreateRigidBody(btCollisionShape* pShape, float weight);
	void RegisterRigidBody();


private:
	Model* model;
	glm::vec3 position;
	btBoxShape* pBoxShape;
	btTransform bTransform;
	MotionState* m_pMotionState;
	btRigidBody* pRigidBody;
	btRigidBody::btRigidBodyConstructionInfo* rbInfo;
};

#endif