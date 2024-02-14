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
		shader.SetVec3("light.ambient", glm::vec3(0.2f));
		shader.SetVec3("light.diffuse", glm::vec3(1.0f));
		shader.SetVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
		shader.SetVec3("cameraPos", camera.GetCameraPos());

		shader.SetVec3("light.direction", glm::vec3(-0.2f, -1.0f, -0.3f));


		glBindVertexArray(Scene::_cubes[i].GetVAO());
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

	}


}