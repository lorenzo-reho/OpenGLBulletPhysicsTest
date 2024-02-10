#include "Renderer.h"

Cube _cube;
glm::mat4 projection;
glm::mat4 view;
glm::mat4 model;

void Renderer::Init() {
	_cube.CreateCube();
	
}

void Renderer::Render(Camera &camera, Shader &shader) {

	shader.Use();

	projection = glm::perspective(glm::radians(60.0f), (float)GL::GetWindowWidth()/ (float)GL::GetWindowHeight(), 0.1f, 100.0f);
	view = glm::mat4(1.0f);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
	model = glm::rotate(model, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	shader.SetMat4("projection", projection);
	shader.SetMat4("view", camera.GetView());
	shader.SetMat4("model", model);


	glBindVertexArray(_cube.GetVAO());
	glDrawArrays(GL_TRIANGLES, 0, 36);


	glBindVertexArray(0);

}