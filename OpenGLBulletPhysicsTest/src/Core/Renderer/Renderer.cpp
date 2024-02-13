#include "Renderer.h"


namespace Renderer {
	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4 model;
}

void Renderer::Init() {
	
}

void Renderer::Render(Camera &camera, Shader &shader) {


	shader.Use();

	projection = glm::perspective(glm::radians(60.0f), (float)GL::GetWindowWidth() / (float)GL::GetWindowHeight(), 0.1f, 100.0f);

	for (int i = 0; i < Scene::_cubes.size(); i++) {
		shader.SetMat4("projection", projection);
		shader.SetMat4("view", camera.GetView());
		shader.SetMat4("model", Scene::_cubes[i].GetTransformMat4());
		shader.SetVec3("color", Scene::_cubes[i].GetColor());

		glBindVertexArray(Scene::_cubes[i].GetVAO());
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

	}


}