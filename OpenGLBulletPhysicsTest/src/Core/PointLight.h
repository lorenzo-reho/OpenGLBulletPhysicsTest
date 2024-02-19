#pragma once
#include "Common.h"
#include "Cube.h"

class PointLight {

public:
	PointLight(glm::vec3 position, glm::vec3 color,  float radius, float intensity);
	void Render();
	float GetIntensity();
	float GetRadius();
	void SetIntensity(float intensity);
	void SetRadius(float radius);

	glm::vec3 GetPosition();
	glm::vec3 GetColor();

	void SetPosition(glm::vec3 position);

	glm::mat4 GetTransformMat4();

private:
	Cube* cube;
	glm::vec3 position;
	float intensity;
	float radius;
	glm::vec3 color;

};