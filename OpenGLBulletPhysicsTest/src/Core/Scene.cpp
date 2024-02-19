#include "Scene.h"

void Scene::ResetAllGameObjectRigidBody() {
	for (GameObject* gameObject : _gameObjects) {
		gameObject->ResetPhysics();
	}
}

void Scene::ResetAllGameObject() {
	for (GameObject* gameObject : _gameObjects) {
		gameObject->Reset();
	}
}
