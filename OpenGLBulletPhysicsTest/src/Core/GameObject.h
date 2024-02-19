#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Common.h"
#include "Physics.h"
#include "Renderer/Model.h"
#include "Cube.h"
#include "GL.h"


class GameObject {

public:
	
	GameObject(glm::vec3 position, Model *model, string name);
	
	void Update(bool debug); 
	void Render(Shader *shader);
	void RenderCollisionCube();

	glm::mat4 GetTransformMat4(bool applyCollisionScale);
	glm::vec3 GetPosition();
	void SetPosition(glm::vec3 position);

	void CreateRigidBody(btCollisionShape* pShape, float weight);
	void RegisterRigidBody();
	void UpdateRigidBodyTransform();
	string GetName();
	void SetName(string name);
	void Reset();
	void ResetPhysics();


private:
	
	Cube *collisionCube;
	Model* model;
	glm::vec3 position;
	glm::mat4 transform;
	glm::mat4 initTransform;

	btBoxShape* pBoxShape;
	btTransform bTransform;
	MotionState* m_pMotionState;
	btRigidBody* pRigidBody;
	btRigidBody::btRigidBodyConstructionInfo* rbInfo;

	string name;
	glm::mat4 btScalar2mat4(btScalar* matrix);
};

#endif