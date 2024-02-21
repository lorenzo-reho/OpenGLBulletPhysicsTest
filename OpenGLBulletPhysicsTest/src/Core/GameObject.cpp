#include "GameObject.h"


GameObject::GameObject(glm::vec3 position, Model *model, string name) {
	this->position = position;
    this->model = model;
    this->name = name;
    this->transform = glm::mat4(1.0);


    // Di base non c'è rotazione
    initTransform = glm::mat4(1.0);
    initTransform = glm::translate(initTransform, position);
    this->transform = initTransform;


    bTransform.setIdentity();
    bTransform.setOrigin(btVector3(position.x, position.y, position.z));
    m_pMotionState = new MotionState(bTransform);
    
    collisionCube = new Cube();
    
    pBoxShape = NULL;
    pRigidBody = NULL;
    rbInfo = NULL;
}

void GameObject::Update(bool debug) {

}

void GameObject::UpdatePhysics() {

    if (m_pMotionState) {
        btScalar scalar[16];
        m_pMotionState->GetWorldTransform(scalar);

        transform = Utils::FromBtScalarToMat4(scalar);
    }
}

void GameObject::Render(Shader *shader) {
	model->Draw(shader);
}

void GameObject::RenderCollisionCube() {
    collisionCube->RenderWireframe();
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

glm::mat4 GameObject::GetTransformMat4(bool applyCollisionScale) {
    if (applyCollisionScale)
       return glm::scale(transform, collisionCube->GetScale());
    else
        return transform;
}

void GameObject::SetName(string name) {
    this->name = name;
}

string GameObject::GetName() {
    return name;
}

glm::vec3 GameObject::GetPosition() {
    return Utils::ExtractTranslationFromMat4(transform);
}


void GameObject::SetPosition(glm::vec3 position) {
    glm::vec3 temp = Utils::ExtractTranslationFromMat4(transform);
    transform = glm::translate(transform, glm::vec3(position.x- temp.x, position.y- temp.y, position.z- temp.z));
    initTransform = transform;
}

void GameObject::ResetRigidBody() {

    Physics::GetDynamicsWorld()->removeRigidBody(pRigidBody);

    pRigidBody->activate(true);
    
    glm::vec3 temp = Utils::ExtractTranslationFromMat4(initTransform);
    bTransform.setOrigin(btVector3(temp.x, temp.y, temp.z));
    
    // TODO: impostare la rotazione
    // bTransform.setRotation(pRigidBody->getOrientation());
    pRigidBody->clearForces();
    pRigidBody->setLinearVelocity(btVector3(0, 0, 0));
    pRigidBody->setAngularVelocity(btVector3(0, 0, 0));

    pRigidBody->setWorldTransform(bTransform);
    
    Physics::GetDynamicsWorld()->addRigidBody(pRigidBody);

}

void GameObject::ResetTransform() {
    transform = initTransform;
   
}