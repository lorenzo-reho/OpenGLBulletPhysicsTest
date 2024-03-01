#include "Renderer.h"


namespace Renderer {
	glm::mat4 projection;
}

void Renderer::Init() {
	GBuffer::Init();
}

void Renderer::Render(Camera &camera, EditorCamera &editorCamera, MODE currentMode) {

	projection = glm::perspective(1.0f, (float)GL::GetWindowWidth() / (float)GL::GetWindowHeight(), 0.1f, 100.0f);
	

	// Render GameObjects
	
	glm::mat4 view(1.0f);
	glm::vec3 cameraPos(0.0f);

	if (currentMode == GAME) {
		view = camera.GetView();
		cameraPos = camera.GetCameraPos();
	}
	else{
		view = editorCamera.GetView();
		cameraPos = editorCamera.GetCameraPos();
	}

	/*
	glDepthMask(GL_FALSE);

	ShaderManager::_cubemap->Use();
	ShaderManager::_cubemap->SetMat4("projection", projection);

	// glm::mat4 view = glm::mat4(glm::mat3(camera.GetView()));
	ShaderManager::_cubemap->SetMat4("view", glm::mat4(glm::mat3(view)));

	glBindTexture(GL_TEXTURE_CUBE_MAP, Scene::_sky->GetTextureID());
	glBindVertexArray(Scene::_sky->GetVAO());
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	glDepthMask(GL_TRUE);
	*/
	// per ogni fonte di luce renderizzo il cubo corrispondente


	/*
	for(int i = 0; i < Scene::_pointLights.size(); i++){

		ShaderManager::_base->Use();

		ShaderManager::_base->SetMat4("projection", projection);
		ShaderManager::_base->SetMat4("view", view);
		ShaderManager::_base->SetVec3("color", Scene::_pointLights[i]->GetColor());
		ShaderManager::_base->SetMat4("model", Scene::_pointLights[i]->GetTransformMat4());

		Scene::_pointLights[i]->Render();
	}
	*/


	glBindFramebuffer(GL_FRAMEBUFFER, GBuffer::_gBuffer);
	glClearColor(20/255.0f, 20 / 255.0f, 20 / 255.0f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ShaderManager::_gBuffer->Use();

	for (int i = 0; i < Scene::_gameObjects.size(); i++) {
		ShaderManager::_gBuffer->SetMat4("projection", projection);
		ShaderManager::_gBuffer->SetMat4("view", view);
		ShaderManager::_gBuffer->SetMat4("model", Scene::_gameObjects[i]->GetTransformMat4(false));
		Scene::_gameObjects[i]->Render(ShaderManager::_gBuffer);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, GBuffer::_gPosition);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, GBuffer::_gNormal);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, GBuffer::_gAlbedoSpec);

	ShaderManager::_lighting->Use();

	ShaderManager::_lighting->SetInt("gPosition", 0);
	ShaderManager::_lighting->SetInt("gNormal", 1);
	ShaderManager::_lighting->SetInt("gAlbedoSpec", 2);

	ShaderManager::_lighting->SetVec3("cameraPos", cameraPos);
	ShaderManager::_lighting->SetVec3("light.ambient", glm::vec3(Scene::_pointLights[0]->GetAmbient()));
	ShaderManager::_lighting->SetVec3("light.diffuse", glm::vec3(Scene::_pointLights[0]->GetDiffuse()));
	ShaderManager::_lighting->SetVec3("light.specular", glm::vec3(Scene::_pointLights[0]->GetSpecular()));
	// ShaderManager::_lighting->SetVec3("light.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
	ShaderManager::_lighting->SetVec3("light.position", Scene::_pointLights[0]->GetPosition());
	ShaderManager::_lighting->SetVec3("light.lightColor", Scene::_pointLights[0]->GetColor());
	ShaderManager::_lighting->SetFloat("light.intensity", Scene::_pointLights[0]->GetIntensity());
	ShaderManager::_lighting->SetFloat("light.radius", Scene::_pointLights[0]->GetRadius());

	// ShaderManager::_quad->Use();

	// Scene::_screenQuad->Render(ShaderManager::_quad, GBuffer::_gAlbedoSpec);
	Scene::_screenQuad->Render();

	// copio il depth buffer del gbuffer nel depth buffer del default framebuffer e successivamente
	// tenendo conto delle informazioni del gbuffer depth buffer renderizzo gli altri elementi della scena
	glBindFramebuffer(GL_READ_FRAMEBUFFER, GBuffer::_gBuffer);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glBlitFramebuffer(0, 0, GL::GetWindowWidth(), GL::GetWindowHeight(), 0, 0, GL::GetWindowWidth(), GL::GetWindowHeight(), GL_DEPTH_BUFFER_BIT, GL_NEAREST);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	

	// renderizzo le fonti di luce
	ShaderManager::_base->Use();

	ShaderManager::_base->SetMat4("projection", projection);
	ShaderManager::_base->SetMat4("view", view);

	for (int i = 0; i < Scene::_pointLights.size(); i++) {
		ShaderManager::_base->SetVec3("color", Scene::_pointLights[i]->GetColor());
		ShaderManager::_base->SetMat4("model", Scene::_pointLights[i]->GetTransformMat4());

		Scene::_pointLights[i]->Render();
	}

	// renderizzo le collision mesh
	for (int i = 0; i < Scene::_gameObjects.size(); i++) {
		if (GL::_isCollisionDebug) {
			ShaderManager::_collisionDebug->Use();
			ShaderManager::_collisionDebug->SetVec3("color", glm::vec3(0.0, 1.0, 0.0));
			ShaderManager::_collisionDebug->SetMat4("projection", projection);
			ShaderManager::_collisionDebug->SetMat4("view", view);
			ShaderManager::_collisionDebug->SetMat4("model", Scene::_gameObjects[i]->GetTransformMat4(true));
			Scene::_gameObjects[i]->RenderCollisionCube();
		}
	}


	/*
	for (int i = 0; i < Scene::_gameObjects.size(); i++) {
		ShaderManager::_geometry->Use();

		ShaderManager::_geometry->SetMat4("projection", projection);
		ShaderManager::_geometry->SetMat4("view", view);
		ShaderManager::_geometry->SetMat4("model", Scene::_gameObjects[i]->GetTransformMat4(false));


		// TODO: Separare la gestione dell'illuminazione tramite framebuffer
		ShaderManager::_geometry->SetVec3("cameraPos", cameraPos);
		ShaderManager::_geometry->SetVec3("light.ambient", glm::vec3(Scene::_pointLights[0]->GetAmbient()));
		ShaderManager::_geometry->SetVec3("light.diffuse", glm::vec3(Scene::_pointLights[0]->GetDiffuse()));
		ShaderManager::_geometry->SetVec3("light.specular", glm::vec3(Scene::_pointLights[0]->GetSpecular()));
		ShaderManager::_geometry->SetVec3("light.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
		ShaderManager::_geometry->SetVec3("light.position", Scene::_pointLights[0]->GetPosition());
		ShaderManager::_geometry->SetVec3("light.lightColor", Scene::_pointLights[0]->GetColor());
		ShaderManager::_geometry->SetFloat("light.intensity", Scene::_pointLights[0]->GetIntensity());
		ShaderManager::_geometry->SetFloat("light.radius", Scene::_pointLights[0]->GetRadius());

		Scene::_gameObjects[i]->Render(ShaderManager::_geometry);
		
		// Renderizzo le collisionmesh di gameobject
		if (GL::_isCollisionDebug) {
			ShaderManager::_collisionDebug->Use();
			ShaderManager::_collisionDebug->SetVec3("color", glm::vec3(0.0, 1.0, 0.0));
			ShaderManager::_collisionDebug->SetMat4("projection", projection);
			ShaderManager::_collisionDebug->SetMat4("view", view);
			ShaderManager::_collisionDebug->SetMat4("model", Scene::_gameObjects[i]->GetTransformMat4(true));
			Scene::_gameObjects[i]->RenderCollisionCube();
		}
	}
	

	ShaderManager::_base->Use();

	for (int i = 0; i < Scene::_cubes.size(); i++) {
		ShaderManager::_base->SetMat4("projection", projection);
		ShaderManager::_base->SetMat4("view",view);
		ShaderManager::_base->SetMat4("model", Scene::_cubes[i]->GetTransformMat4());
		ShaderManager::_base->SetVec3("color", Scene::_cubes[i]->GetColor());
		ShaderManager::_base->SetVec3("light.ambient", glm::vec3(0.2f));
		ShaderManager::_base->SetVec3("light.diffuse", glm::vec3(0.6f));
		ShaderManager::_base->SetVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
		ShaderManager::_base->SetVec3("cameraPos", cameraPos);
		ShaderManager::_geometry->SetVec3("light.position", glm::vec3(0, 0, 0));

		ShaderManager::_base->SetVec3("light.direction", glm::vec3(-0.2f, -1.0f, -0.3f));


		glBindVertexArray(Scene::_cubes[i]->GetVAO());
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

	}

	*/
}