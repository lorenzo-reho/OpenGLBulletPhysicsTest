#include "Scene.h"

void Scene::ResetAllGameObjectRigidBody() {
	for (GameObject* gameObject : _gameObjects) {
		gameObject->ResetRigidBody();
	}
}

void Scene::ResetAllGameObject() {
	for (GameObject* gameObject : _gameObjects) {
		gameObject->ResetTransform();
	}
}


void Scene::UpdateAllGameObjectPhysics() {
	for (GameObject* gameObject : _gameObjects) {
		gameObject->UpdatePhysics();
	}
}