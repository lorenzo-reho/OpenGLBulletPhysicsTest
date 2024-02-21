#pragma once

#include "Core/Common.h"
#include "Core/Physics.h"
#include <cmath>

#define _USE_MATH_DEFINES

namespace Utils {
	struct MousePosition {
		double x;
		double y;
	};

	glm::mat4 FromBtScalarToMat4(btScalar scalar[]);
	glm::vec3 ExtractTranslationFromMat4(glm::mat4 transform);
	glm::quat ExtractRotationFromMat4(glm::mat4 transform);

	glm::vec3 ToEulerAngles(glm::quat q);

}