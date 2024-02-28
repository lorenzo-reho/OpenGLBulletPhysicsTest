#pragma once

#include "Common.h"
#include <iostream>
#include <vector>
#include "Sky.h"
#include "Cube.h"
#include "PointLight.h"
#include "Camera.h"
#include "GameObject.h"
#include "Quad.h"

namespace Scene {
	
	inline std::vector<Cube*> _cubes;
	inline std::vector<GameObject*> _gameObjects;
	inline std::vector<PointLight*> _pointLights;

	inline Sky* _sky;
	inline Camera* _camera;
	inline Quad* _screenQuad;

	void ResetAllGameObjectRigidBody();
	void ResetAllGameObject();
	void UpdateAllGameObjectPhysics();



}