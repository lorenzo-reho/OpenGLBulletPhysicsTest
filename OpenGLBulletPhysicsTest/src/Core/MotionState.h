#ifndef BULLETOPENGL_OPENGLMOTIONSTATE_H
#define BULLETOPENGL_OPENGLMOTIONSTATE_H

#include <btBulletCollisionCommon.h>

class MotionState : public btDefaultMotionState {
public:
	MotionState(const btTransform& transform) : btDefaultMotionState(transform) {}

	void GetWorldTransform(btScalar* transform) {
		btTransform trans;
		getWorldTransform(trans);
		trans.getOpenGLMatrix(transform);
	}
};

#endif //BULLETOPENGL_OPENGLMOTIONSTATE_H