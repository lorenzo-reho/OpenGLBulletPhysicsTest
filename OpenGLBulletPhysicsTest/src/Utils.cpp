#include "Utils.h"

glm::mat4 Utils::FromBtScalarToMat4(btScalar scalar[]) {
	return  glm::mat4(scalar[0], scalar[1], scalar[2], scalar[3],
        scalar[4], scalar[5], scalar[6], scalar[7],
        scalar[8], scalar[9], scalar[10], scalar[11],
        scalar[12], scalar[13], scalar[14], scalar[15]);
}

glm::vec3 Utils::ExtractTranslationFromMat4(glm::mat4 transform) {
    return transform[3];
}