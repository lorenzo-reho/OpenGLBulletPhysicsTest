#ifndef CAMERA_H
#define CAMERA_H

#include "../Common.h"
#include "../Input.h"


enum Direction {
	FORWARD,
	BACK,
	LEFT,
	RIGHT
};

class Camera {
private:
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	float speed = 5.0f;

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
		}\
		if (direction == BACK) {
			cameraPos -= cameraFront * speed * deltaTime;
		}
		if (direction == LEFT) {
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * speed * deltaTime;
		}
		if (direction == RIGHT) {
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * speed * deltaTime;
		}
	}

	void Update(float deltaTime) {
		if (Input::IsPressed(GLFW_KEY_W)) Move(FORWARD, deltaTime);
		if (Input::IsPressed(GLFW_KEY_A)) Move(LEFT, deltaTime);
		if (Input::IsPressed(GLFW_KEY_S)) Move(BACK, deltaTime);
		if (Input::IsPressed(GLFW_KEY_D)) Move(RIGHT, deltaTime);

	}

	glm::mat4 GetView() {
		return glm::lookAt(cameraPos, cameraPos+cameraFront, cameraUp);
	}

};

#endif