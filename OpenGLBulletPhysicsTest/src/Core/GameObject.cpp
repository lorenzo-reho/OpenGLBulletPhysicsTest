#include "GameObject.h"

/*
TODO: 
Modularizzare decomposizione transform in Utils.cpp
Funzione per passare da bullet a glm e viceversa
*/

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

    // applico la fisica al transform
    if (m_pMotionState && !debug) {
        
        btScalar transform[16];
        m_pMotionState->GetWorldTransform(transform);

        // Utils.cpp
        glm::mat4 tempTransform = glm::mat4(transform[0], transform[1], transform[2], transform[3],
            transform[4], transform[5], transform[6], transform[7],
            transform[8], transform[9], transform[10], transform[11],
            transform[12], transform[13], transform[14], transform[15]);

        this->transform = tempTransform;
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

// Utils.cpp
glm::mat4 GameObject::btScalar2mat4(btScalar* matrix) {
    return glm::mat4(
        matrix[0], matrix[1], matrix[2], matrix[3],
        matrix[4], matrix[5], matrix[6], matrix[7],
        matrix[8], matrix[9], matrix[10], matrix[11],
        matrix[12], matrix[13], matrix[14], matrix[15]);
}


glm::mat4 GameObject::GetTransformMat4(bool applyCollisionScale) {
    /*
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
    */
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
    /*
    btTransform transform;
    // transform = pRigidBody->getWorldTransform();
    m_pMotionState->getWorldTransform(transform);
    return glm::vec3(transform.getOrigin().getX(), transform.getOrigin().getY(), transform.getOrigin().getZ());
    */
    
    return transform[3];
    
}

void GameObject::UpdateRigidBodyTransform() {
    btTransform transform;
    m_pMotionState->getWorldTransform(transform);
    pRigidBody->activate(true);
    pRigidBody->setWorldTransform(transform);
}

void GameObject::SetPosition(glm::vec3 position) {
    /*
    bTransform.setOrigin(btVector3(position.x, position.y, position.z));
    bTransform.setRotation(pRigidBody->getOrientation());

    // pRigidBody->activate(true);
    // pRigidBody->setWorldTransform(bTransform);

    m_pMotionState->setWorldTransform(bTransform);
    */
    
    //Utils.cpp
    glm::vec3 curr = transform[3];
    transform = glm::translate(transform, glm::vec3(position.x-curr.x, position.y-curr.y, position.z-curr.z));
    initTransform = transform;
}

void GameObject::ResetPhysics() {

    Physics::GetDynamicsWorld()->removeRigidBody(pRigidBody);

    pRigidBody->activate(true);

    // imposto la posizione e rotazione del rigidbody a partire dal transform
    btTransform trans;
    trans.setIdentity();

    glm::vec3 position = initTransform[3];
    trans.setOrigin(btVector3(position.x, position.y, position.z));
    
    // TODO: impostare la rotazione
    // bTransform.setRotation(pRigidBody->getOrientation());
    pRigidBody->clearForces();
    pRigidBody->setLinearVelocity(btVector3(0, 0, 0));
    pRigidBody->setAngularVelocity(btVector3(0, 0, 0));

    // pRigidBody->clearGravity();

    pRigidBody->setWorldTransform(trans);
    
    Physics::GetDynamicsWorld()->addRigidBody(pRigidBody);

}

void GameObject::Reset() {
    transform = initTransform;
   
}