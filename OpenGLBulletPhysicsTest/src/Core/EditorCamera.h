#pragma once

#include "Common.h"
#include "Input.h"


class EditorCamera {

private:
	glm::vec3 cameraPos;
	glm::vec3 cameraFocus;
	glm::vec3 cameraUp;
	glm::vec3 forward;
	glm::vec3 up;
	glm::vec3 right;

	float yaw = 0;
	float pinch = 0;
	float distance = 10.0f;
	bool firstClick = false;

public:
	
	EditorCamera(glm::vec3 cameraFocus) {
		this->cameraFocus = cameraFocus;
		this->forward = glm::vec3(0, 0, 1);
		this->up = glm::vec3(0, 1, 0);
		this->right = glm::vec3(1, 0, 0);

		pinch = -30.0f;

		SetForwardRotation();

		// cameraPos = cameraFocus + forward * distance;
		cameraUp = glm::vec3(0, 1, 0);
	}

	void SetForwardRotation() {

		glm::vec3 tempForward = glm::vec3(0, 0, 1);
		glm::vec3 tempRight= glm::vec3(1, 0, 0);
		glm::vec3 tempUp = glm::vec3(0, 1, 0);

		glm::mat4 rot1 = glm::rotate(glm::mat4(1.0), glm::radians(yaw), cameraUp);
		glm::mat4 rot2 = glm::rotate(glm::mat4(1.0), glm::radians(pinch), glm::vec3(1, 0, 0));

		forward = glm::vec3(rot1 * rot2 * glm::vec4(tempForward, 1.0f));
		right = glm::vec3(rot1 * rot2 * glm::vec4(tempRight, 1.0f));
		up = glm::vec3(rot1 * rot2 * glm::vec4(tempUp, 1.0f));

	}

	void ArcBallRotate(float deltaTime, double deltaX, double deltaY) {
		double sensitivity = 0.1f;
		
		yaw += -deltaX * sensitivity;
		pinch += -deltaY * sensitivity;

		if (pinch > 89.0) {
			pinch = 89.0;
		}
		if (pinch < -89.0) {
			pinch = -89.0;
		}
		SetForwardRotation();
	}

	float CalculateZoomSpeed(float d) {
		d = std::max(d, 0.0f);
		float speed = d * d;
		speed = std::min(speed, 100.0f);
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

	void UpdateFocus(double deltaTime, double deltaX, double deltaY) {

		float speed = 5.0f;
		cameraFocus += -right * (float)deltaX * speed * (float)deltaTime;
		cameraFocus += up * (float)deltaY * speed * (float)deltaTime;


		// m_FocalPoint += GetUpDirection() * delta.y * ySpeed * m_Distance;

	}

	void Update(double deltaTime) {

		if (Input::IsKeyPressed(GLFW_KEY_LEFT_ALT)) {
			if (Input::IsMousePressed(GLFW_MOUSE_BUTTON_LEFT))
				UpdateFocus(deltaTime, Input::GetDeltaX(), Input::GetDeltaY());
		}

		CameraZoom(deltaTime);

		if (Input::IsMousePressed(GLFW_MOUSE_BUTTON_3))
			ArcBallRotate(deltaTime, Input::GetDeltaX(), Input::GetDeltaY());

		if (Input::IsKeyPressed(GLFW_KEY_O)) {
			FocusToOrigin();
		}

		cameraPos = cameraFocus + forward * distance;
	}

	void FocusToOrigin() {
		distance = 10.0f;
		cameraFocus = glm::vec3(0);
	}

	glm::mat4 GetView() {
		return glm::lookAt(cameraPos, cameraFocus, cameraUp);
	}

	glm::vec3 GetCameraPos() {
		return cameraPos;
	}


};