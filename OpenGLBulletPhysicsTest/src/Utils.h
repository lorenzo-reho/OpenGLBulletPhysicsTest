#pragma once

#include "Core/Common.h"
#include "Core/Physics.h"


namespace Utils {
	struct MousePosition {
		double x;
		double y;
	};

	glm::mat4 FromBtScalarToMat4(btScalar scalar[]);
	glm::vec3 ExtractTranslationFromMat4(glm::mat4 transform);
}