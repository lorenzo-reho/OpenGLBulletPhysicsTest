#pragma once

#include "Common.h"
#include "Input.h"


class EditorCamera {

private:
	glm::vec3 cameraPos;
	glm::vec3 cameraFocus;
	glm::vec3 cameraUp;
	glm::vec3 forward;
	float yaw = 0;
	float pinch = 0;
	float distance = 10.0f;
	bool firstClick = false;
	double lastX = 0;
	double lastY = 0;

public:
	
	EditorCamera( glm::vec3 cameraFocus) {
		this->cameraFocus = cameraFocus;
		this->forward = glm::vec3(0, 0, 1);
		
		cameraPos = cameraFocus + glm::vec3(0, 0, 1) * distance;
		cameraUp = glm::vec3(0, 1, 0);
	}

	void ArcBallRotate(float deltaTime, Utils::MousePosition mousePosition) {
		double xOffset = mousePosition.x - lastX;
		double yOffset = lastY - mousePosition.y;

		lastX = mousePosition.x;
		lastY = mousePosition.y;

		double sensitivity = 0.1f;

		yaw += -xOffset * sensitivity;
		pinch += yOffset * sensitivity;

		if (pinch > 89.0) {
			pinch = 89.0;
		}
		if (pinch < -89.0) {
			pinch = -89.0;
		}

		glm::vec3 forward = glm::vec3(0, 0, 1);

		glm::mat4 rot1 = glm::rotate(glm::mat4(1.0), glm::radians(yaw), cameraUp);
		glm::mat4 rot2 = glm::rotate(glm::mat4(1.0), glm::radians(pinch), glm::vec3(1, 0, 0));

		this->forward = glm::vec3(rot1 * rot2 * glm::vec4(forward, 1.0f));


	}

	float CalculateZoomSpeed(float d) {
		d = std::max(d, 0.0f);
		float speed = d * d;
		speed = std::min(speed, 100.0f); // max speed = 100
		return speed;
	}

	void CameraZoom(float deltaTime) {
		if (Input::IsMouseWheelUp()) {
			distance -= deltaTime * CalculateZoomSpeed(distance);
		}

		if (Input::IsMouseWheelDown()) {
			distance += deltaTime * CalculateZoomSpeed(distance);
		}
	}

	void Update(double deltaTime) {

		CameraZoom(deltaTime);

		if (Input::IsMouseReleased(GLFW_MOUSE_BUTTON_3)) {
			firstClick = true;
		}

		if (Input::IsMousePressed(GLFW_MOUSE_BUTTON_3)) {
			if (firstClick) {
				lastX = Input::GetCursorPos().x;
				lastY = Input::GetCursorPos().y;
				firstClick = false;
			}
			ArcBallRotate(deltaTime, Input::GetCursorPos());
		}

		cameraPos = cameraFocus + forward * distance;
	}

	glm::mat4 GetView() {
		return glm::lookAt(cameraPos, cameraFocus, cameraUp);
	}

	glm::vec3 GetCameraPos() {
		return cameraPos;
	}


};