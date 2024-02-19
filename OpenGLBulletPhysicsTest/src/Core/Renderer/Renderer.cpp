#include "Renderer.h"


namespace Renderer {
	glm::mat4 projection;
}

void Renderer::Init() {
	
}

void Renderer::Render(Camera &camera) {

	projection = glm::perspective(1.0f, (float)GL::GetWindowWidth() / (float)GL::GetWindowHeight(), 0.1f, 100.0f);
	/*
	// Render CubeMap
	glDepthMask(GL_FALSE);

	ShaderManager::_cubemap->Use();
	ShaderManager::_cubemap->SetMat4("projection", projection);

	glm::mat4 view = glm::mat4(glm::mat3(camera.GetView()));
	ShaderManager::_cubemap->SetMat4("view", view);

	glBindTexture(GL_TEXTURE_CUBE_MAP, Scene::_sky->GetTextureID());
	glBindVertexArray(Scene::_sky->GetVAO());
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	glDepthMask(GL_TRUE);

	// Render GameObjects
	*/
	
	for (int i = 0; i < Scene::_gameObjects.size(); i++) {
		ShaderManager::_geometry->Use();

		ShaderManager::_geometry->SetMat4("projection", projection);
		ShaderManager::_geometry->SetMat4("view", camera.GetView());
		ShaderManager::_geometry->SetMat4("model", Scene::_gameObjects[i]->GetTransformMat4(false));


		ShaderManager::_geometry->SetVec3("light.ambient", glm::vec3(0.2f));
		ShaderManager::_geometry->SetVec3("light.diffuse", glm::vec3(1.0f));
		ShaderManager::_geometry->SetVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
		ShaderManager::_geometry->SetVec3("cameraPos", camera.GetCameraPos());
		ShaderManager::_geometry->SetVec3("light.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
		ShaderManager::_geometry->SetVec3("light.position", Scene::_pointLights[0]->GetPosition());
		ShaderManager::_geometry->SetVec3("light.lightColor", Scene::_pointLights[0]->GetColor());
		ShaderManager::_geometry->SetFloat("light.intensity", Scene::_pointLights[0]->GetIntensity());
		ShaderManager::_geometry->SetFloat("light.radius", Scene::_pointLights[0]->GetRadius());

		Scene::_gameObjects[i]->Render(ShaderManager::_geometry);

		ShaderManager::_base->Use();

		ShaderManager::_base->SetMat4("projection", projection);
		ShaderManager::_base->SetMat4("view", camera.GetView());
		ShaderManager::_base->SetVec3("color", Scene::_pointLights[0]->GetColor());
		ShaderManager::_base->SetMat4("model", Scene::_pointLights[0]->GetTransformMat4());

		Scene::_pointLights[0]->Render();

		if (GL::_isCollisionDebug) {
			ShaderManager::_collisionDebug->Use();
			ShaderManager::_collisionDebug->SetVec3("color", glm::vec3(0.0, 1.0, 0.0));
			ShaderManager::_collisionDebug->SetMat4("projection", projection);
			ShaderManager::_collisionDebug->SetMat4("view", camera.GetView());
			ShaderManager::_collisionDebug->SetMat4("model", Scene::_gameObjects[i]->GetTransformMat4(true));
			Scene::_gameObjects[i]->RenderCollisionCube();
		}
	}
	
	ShaderManager::_base->Use();

	for (int i = 0; i < Scene::_cubes.size(); i++) {
		ShaderManager::_base->SetMat4("projection", projection);
		ShaderManager::_base->SetMat4("view", camera.GetView());
		ShaderManager::_base->SetMat4("model", Scene::_cubes[i]->GetTransformMat4());
		ShaderManager::_base->SetVec3("color", Scene::_cubes[i]->GetColor());
		ShaderManager::_base->SetVec3("light.ambient", glm::vec3(0.2f));
		ShaderManager::_base->SetVec3("light.diffuse", glm::vec3(0.6f));
		ShaderManager::_base->SetVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
		ShaderManager::_base->SetVec3("cameraPos", camera.GetCameraPos());
		ShaderManager::_geometry->SetVec3("light.position", glm::vec3(0, 0, 0));

		ShaderManager::_base->SetVec3("light.direction", glm::vec3(-0.2f, -1.0f, -0.3f));


		glBindVertexArray(Scene::_cubes[i]->GetVAO());
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

	}
}