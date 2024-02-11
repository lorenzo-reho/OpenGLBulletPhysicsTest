#ifndef BULLETOPENGL_OPENGLMOTIONSTATE_H
#define BULLETOPENGL_OPENGLMOTIONSTATE_H

#include <btBulletCollisionCommon.h>
#include "Common.h"

class MotionState : public btDefaultMotionState {
public:
	MotionState(const btTransform& transform) : btDefaultMotionState(transform) {}

	void GetWorldTransform(btScalar* transform) {
		btTransform trans;
		getWorldTransform(trans);

		/*
		btQuaternion rotation = trans.getRotation(); 
		btVector3 transform = trans.getOrigin();

		glm::mat4 RotationMatrix = glm::toMat4(glm::quat(rotation.getW(), rotation.getX(), rotation.getY(), rotation.getZ()));
		glm::vec3 glm::vec3(v.getX(), v.getY(), v.getZ());
		*/

		trans.getOpenGLMatrix(transform);
	}
};

#endif //BULLETOPENGL_OPENGLMOTIONSTATE_H