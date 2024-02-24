#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include "../Utils.h"

struct Transform {
	glm::vec3 position = glm::vec3(0);
	glm::vec3 rotation = glm::vec3(0);
	// glm::quat rotation;
	glm::vec3 scale = glm::vec3(1);
	glm::mat4 to_mat4() {
		glm::mat4 m = glm::translate(glm::mat4(1), position);
		
		m *= glm::mat4_cast(glm::quat(rotation));
		
		m = glm::scale(m, scale);
		return m;
	};
};
