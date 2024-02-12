#include "Renderer.h"


namespace Renderer {
	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4 model;
}

void Renderer::Init() {
	
}

void Renderer::Render(Camera &camera, Shader &shader, Cube &cube, Cube &cube1, Cube& cube2) {

	shader.Use();

	projection = glm::perspective(glm::radians(60.0f), (float)GL::GetWindowWidth()/ (float)GL::GetWindowHeight(), 0.1f, 100.0f);
	
	shader.SetMat4("projection", projection);
	shader.SetMat4("view", camera.GetView());
	shader.SetMat4("model", cube.GetTransformMat4());
	shader.SetVec3("color", glm::vec3(0.0, 108/255.0f, 103 / 255.0f));


	glBindVertexArray(cube.GetVAO());
	glDrawArrays(GL_TRIANGLES, 0, 36);

	shader.SetMat4("view", camera.GetView());
	shader.SetMat4("model", cube1.GetTransformMat4());
	shader.SetVec3("color", glm::vec3(0.0, 1.0, 0));

	glBindVertexArray(cube1.GetVAO());
	glDrawArrays(GL_TRIANGLES, 0, 36);

	shader.SetMat4("view", camera.GetView());
	shader.SetMat4("model", cube2.GetTransformMat4());
	shader.SetVec3("color", glm::vec3(0.0, 0.0, 1.0));

	glBindVertexArray(cube2.GetVAO());
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindVertexArray(0);

}