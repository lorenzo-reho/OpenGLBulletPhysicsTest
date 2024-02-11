#ifndef CAMERA_H
#define CAMERA_H

#include "Common.h"
#include "Input.h"

enum Direction {
	FORWARD,
	BACK,
	LEFT,
	RIGHT,
	UP, 
	DOWN
};

class Camera {
private:
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;

	float speed = 8.0f;
	double yaw = -90.0f;
	double pitch = 0.0f;
	double lastX = 0.0f;
	double lastY = 0.0f;

	bool firstMouse = true;

public:
	Camera(glm::vec3 cameraPos, glm::vec3 cameraFront, float speed) {
		this->cameraFront = cameraFront;
		this->cameraPos = cameraPos;
		this->speed = speed;
		cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	}

	void Move(Direction direction, float deltaTime) {
		if (direction == FORWARD) {
			cameraPos += cameraFront * speed * deltaTime;
		}
		if (direction == BACK) {
			cameraPos -= cameraFront * speed * deltaTime;
		}
		if (direction == LEFT) {
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * speed * deltaTime;
		}
		if (direction == RIGHT) {
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * speed * deltaTime;
		}
		if (direction == UP) {
			cameraPos += cameraUp * speed * deltaTime;
		}
		if (direction == DOWN) {
			cameraPos -= cameraUp * speed * deltaTime;
		}
	}

	void Rotate(float deltaTime, Utils::MousePosition mousePosition) {
		if (firstMouse) {

			lastX = mousePosition.x;
			lastY = mousePosition.y;

			firstMouse = false;
		}

		double xOffset = mousePosition.x - lastX;
		double yOffset = lastY - mousePosition.y;

		lastX = mousePosition.x;
		lastY = mousePosition.y;

		// std::cout << "X: " << lastX << " " << "Y: " << lastY << std::endl;

		double sensitivity = 0.1f;

		yaw += xOffset * sensitivity;
		pitch += yOffset * sensitivity;

		cameraFront.z = (float)sin(glm::radians(yaw)) * (float)cos(glm::radians(pitch));
		cameraFront.x = (float)cos(glm::radians(yaw)) * (float)cos(glm::radians(pitch));;
		cameraFront.y = (float)sin(glm::radians(pitch));


		cameraFront = glm::normalize(cameraFront);

	}

	void Update(float deltaTime) {
		if (Input::IsPressed(GLFW_KEY_W)) Move(FORWARD, deltaTime);
		if (Input::IsPressed(GLFW_KEY_A)) Move(LEFT, deltaTime);
		if (Input::IsPressed(GLFW_KEY_S)) Move(BACK, deltaTime);
		if (Input::IsPressed(GLFW_KEY_D)) Move(RIGHT, deltaTime);
		if (Input::IsPressed(GLFW_KEY_SPACE)) Move(UP, deltaTime);
		if (Input::IsPressed(GLFW_KEY_LEFT_SHIFT)) Move(DOWN, deltaTime);

		Rotate(deltaTime, Input::GetCursorPos());

	}

	glm::mat4 GetView() {
		return glm::lookAt(cameraPos, cameraPos+cameraFront, cameraUp);
	}

};

#endif