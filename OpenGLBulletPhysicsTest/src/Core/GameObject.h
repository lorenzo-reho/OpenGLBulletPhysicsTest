#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Common.h"
#include "Physics.h"
#include "Renderer/Model.h"
#include "Cube.h"

class GameObject {

public:
	
	GameObject(glm::vec3 position, Model *model);
	
	void Update(); 
	void Render(Shader *shader);
	void RenderCollisionCube();

	glm::mat4 GetTransformMat4(bool applyCollisionScale);
	void CreateRigidBody(btCollisionShape* pShape, float weight);
	void RegisterRigidBody();

private:
	
	Cube *collisionCube;
	Model* model;
	glm::vec3 position;
	btBoxShape* pBoxShape;
	btTransform bTransform;
	MotionState* m_pMotionState;
	btRigidBody* pRigidBody;
	btRigidBody::btRigidBodyConstructionInfo* rbInfo;

	string name;
	glm::mat4 btScalar2mat4(btScalar* matrix);
};

#endif