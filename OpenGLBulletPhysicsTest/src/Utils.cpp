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

glm::quat Utils::ExtractRotationFromMat4(glm::mat4 transform) {
    return glm::quat_cast(transform);
}


// this implementation assumes normalized quaternion
// converts to Euler angles in 3-2-1 sequence
glm::vec3 Utils::ToEulerAngles(glm::quat q) {
    glm::highp_vec3 angles;
    double M_PI = 3.14159265358979323846;
    // roll (x-axis rotation)
    double sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
    double cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
    angles.x = std::atan2(sinr_cosp, cosr_cosp);

    // pitch (y-axis rotation)
    double sinp = std::sqrt(1 + 2 * (q.w * q.y - q.x * q.z));
    double cosp = std::sqrt(1 - 2 * (q.w * q.y - q.x * q.z));
    angles.y= 2 * std::atan2(sinp, cosp) - M_PI / 2;

    // yaw (z-axis rotation)
    double siny_cosp = 2 * (q.w * q.z + q.x * q.y);
    double cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
    angles.z = std::atan2(siny_cosp, cosy_cosp);

    return angles;
}
