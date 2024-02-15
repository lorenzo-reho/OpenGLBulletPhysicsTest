#pragma once

#include "Common.h"
#include <iostream>
#include <vector>
#include "Sky.h"
#include "Cube.h"
#include "GameObject.h"



namespace Scene {
	
	inline std::vector<Cube*> _cubes;
	inline std::vector<GameObject*> _gameObjects;

	inline Sky* _sky;

}