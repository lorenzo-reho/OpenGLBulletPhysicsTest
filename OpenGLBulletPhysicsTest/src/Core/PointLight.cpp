#include "PointLight.h"

PointLight::PointLight(glm::vec3 position, glm::vec3 color, float radius, float intensity) {
	this->radius = radius;
	this->intensity = intensity;
	this->position = position;
	this->color = color;
	
	ambient = 0.2f;
	diffuse = 1.0f;
	specular = 1.0f;

	cube = new Cube();
}

PointLight::PointLight(glm::vec3 position, glm::vec3 color, float radius, float intensity, float ambient, float diffuse, float specular) {
	this->radius = radius;
	this->intensity = intensity;
	this->position = position;
	this->color = color;
	this->ambient= ambient;
	this->diffuse = diffuse;
	this->specular= specular;

	cube = new Cube();
}

void PointLight::Render() {
	cube->Render();
}

float PointLight::GetIntensity() {
	return intensity;
}

float PointLight::GetRadius() {
	return radius;
}
float PointLight::GetAmbient() {
	return ambient;
}
float PointLight::GetDiffuse() {
	return diffuse;
}
float PointLight::GetSpecular() {
	return specular;
}

glm::vec3 PointLight::GetColor() {
	return color;
}

glm::vec3 PointLight::GetPosition() {
	return position;
}


void PointLight::SetIntensity(float intensity) {
	this->intensity = intensity;
}

void PointLight::SetRadius(float radius) {
	this->radius = radius;
}

void PointLight::SetAmbient(float ambient) {
	this->ambient = ambient;
}
void PointLight::SetDiffuse(float diffuse) {
	this->diffuse = diffuse;
}
void PointLight::SetSpecular(float specular) {
	this->specular = specular;
}


void PointLight::SetPosition(glm::vec3 position) {
	this->position = position;
}


glm::mat4 PointLight::GetTransformMat4() {
	glm::mat4 model(1.0);
	model = glm::translate(model, position);
	model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));

	return model;
}
