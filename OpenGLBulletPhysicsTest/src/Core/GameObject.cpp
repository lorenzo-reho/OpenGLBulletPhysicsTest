#include "GameObject.h"

GameObject::GameObject(glm::vec3 position, Model *model) {
	this->position = position;
    this->model = model;
    bTransform.setIdentity();
    bTransform.setOrigin(btVector3(position.x, position.y, position.z));
    m_pMotionState = new MotionState(bTransform);
    collisionCube = new Cube();
}

void GameObject::Update() {

}

void GameObject::Render(Shader *shader) {
	model->Draw(shader);
}

void GameObject::RenderCollisionCube() {
    collisionCube->Render();
}

void GameObject::CreateRigidBody(btCollisionShape* pShape, float weight) {

    btVector3 localInertia(0, 0, 0);

    if (weight != 0.0f)
        pShape->calculateLocalInertia(weight, localInertia);


    //Casting forzato da sistemare
    btBoxShape* boxShape = (btBoxShape*) pShape;
      
    btVector3 bScale = boxShape->getHalfExtentsWithMargin();
    glm::vec3 scale = glm::vec3(bScale.getX()*2, bScale.getY() * 2, bScale.getZ() * 2);

    collisionCube->SetScale(scale);

    rbInfo = new btRigidBody::btRigidBodyConstructionInfo(weight, m_pMotionState, pShape, localInertia);
    pRigidBody = new btRigidBody(*rbInfo);
}

void GameObject::RegisterRigidBody() {
    Physics::GetDynamicsWorld()->addRigidBody(pRigidBody);
}

glm::mat4 GameObject::btScalar2mat4(btScalar* matrix) {
    return glm::mat4(
        matrix[0], matrix[1], matrix[2], matrix[3],
        matrix[4], matrix[5], matrix[6], matrix[7],
        matrix[8], matrix[9], matrix[10], matrix[11],
        matrix[12], matrix[13], matrix[14], matrix[15]);
}


glm::mat4 GameObject::GetTransformMat4(bool applyCollisionScale) {

    if (m_pMotionState) {
        btScalar transform[16];
        m_pMotionState->GetWorldTransform(transform);

        glm::mat4 tempTransform = glm::mat4(transform[0], transform[1], transform[2], transform[3],
            transform[4], transform[5], transform[6], transform[7],
            transform[8], transform[9], transform[10], transform[11],
            transform[12], transform[13], transform[14], transform[15]);

        if(applyCollisionScale)
            tempTransform = glm::scale(tempTransform, collisionCube->GetScale());

        return tempTransform;
    }

    return glm::mat4(1.0);
}
