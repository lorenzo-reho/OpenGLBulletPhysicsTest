#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Common.h"
#include "Physics.h"
#include "Renderer/Model.h"
#include "Cube.h"
#include "GL.h"
#include "../Utils.h"



class GameObject {

public:
	
	GameObject(glm::vec3 position, Model *model, string name);
	
	void Update(bool debug); 
	void UpdatePhysics();

	void Render(Shader *shader);
	void RenderCollisionCube();

	
	void CreateRigidBody(btCollisionShape* pShape, float weight);
	void RegisterRigidBody();
	void ResetTransform();
	void ResetRigidBody();

	string GetName();
	glm::mat4 GetTransformMat4(bool applyCollisionScale);
	glm::vec3 GetPosition();
	void SetPosition(glm::vec3 position);
	void SetName(string name);

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
};

#endif