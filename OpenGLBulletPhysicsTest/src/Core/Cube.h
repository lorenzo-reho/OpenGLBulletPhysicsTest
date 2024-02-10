#pragma once
#include "Common.h"

class Cube {
public:
	Cube();

	void CreateCube();
	unsigned int GetVAO();

private:
	unsigned int _VBO, _EBO, _VAO;

};
