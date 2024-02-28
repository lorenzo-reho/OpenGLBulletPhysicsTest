#pragma once

#include "GL.h"
#include "Renderer/Shader.h"

class Quad {
public:
	Quad();
	void Render(Shader *shader, unsigned int texture);
	void Render();

	unsigned int GetVAO();

private:
	unsigned int _VBO, _VAO;
	// glm::mat4 transform;
	
	void CreateQuad();

};