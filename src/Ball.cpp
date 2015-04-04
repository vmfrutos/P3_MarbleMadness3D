#include "Ball.h"

Ball::Ball(const string& ballMesh, const string& ballName, Vector3 initPos):PhysicWorld(){
	_ballNode = NULL;
	_ballEnt = NULL;
	initializeParamsConf();
	printConf();
	initializeBall(ballMesh,ballMesh,initPos);


}

Ball::~Ball(){
}

void
Ball::initializeBall(const string& ballMesh, const string& ballName, Vector3 initPos) {

	// Se crea la entidad y el SceneNode de la bola
	_ballNode = _sceneManager->createSceneNode(ballName);
	Entity* _ballEnt = _sceneManager->createEntity(ballName, ballMesh);
	_ballEnt->setCastShadows(true);
	_ballNode->attachObject(_ballEnt);
	_ballNode->setPosition(initPos);
	_sceneManager->getRootSceneNode()->addChild(_ballNode);

	// Se crea obtiene la forma de colision basada en esfera SphereCollisionShape
	_ballShape = new OgreBulletCollisions::SphereCollisionShape(_diameter/2.0);

	// Se crea el rigbody
	_rigidBall = new  OgreBulletDynamics::RigidBody(ballName, _world);
	_rigidBall->setShape(_ballNode, _ballShape, _restitution, _friction, _mass, initPos, Quaternion::IDENTITY);

	// Se añade la forma de colision y el cuerpo rigido a las colas correspondientes
	_bodies.push_back(_rigidBall);
	_shapes.push_back(_ballShape);

}

void
Ball::initializeParamsConf() {
	_restitution = Properties::getSingletonPtr()->getPropertyFloat("ball.restitution");
	_friction = Properties::getSingletonPtr()->getPropertyFloat("ball.friction");
	_mass = Properties::getSingletonPtr()->getPropertyFloat("ball.mass");
	_diameter = Properties::getSingletonPtr()->getPropertyFloat("ball.diameter");
	_impulseForce = Properties::getSingletonPtr()->getPropertyFloat("ball.impulseForce");
}

void
Ball::printConf() {
	Ogre::LogManager::getSingletonPtr()->logMessage("************** Ball ******************");
	Ogre::LogManager::getSingletonPtr()->logMessage("ball.restitution: " + StringConverter::toString(_restitution));
	Ogre::LogManager::getSingletonPtr()->logMessage("ball.friction: " + StringConverter::toString(_friction));
	Ogre::LogManager::getSingletonPtr()->logMessage("ball.mass: " + StringConverter::toString(_mass));
	Ogre::LogManager::getSingletonPtr()->logMessage("ball.diameter: " + StringConverter::toString(_diameter));
	Ogre::LogManager::getSingletonPtr()->logMessage("ball.impulseForce: " + StringConverter::toString(_impulseForce));
	Ogre::LogManager::getSingletonPtr()->logMessage("***************************************");
}

void
Ball::applyImpulse(Vector3 direction, float delta){

	// el impulso se aplica en el centro de la bola
	Vector3 posicion(0.0,0.0,0.0);
	_rigidBall->enableActiveState();
	_rigidBall->applyImpulse(direction * _impulseForce * delta,posicion);
}

const Vector3&
Ball::getPosition() {
	return _ballNode->getPosition();

}

/**
 * Este metodo resetea la bola y la pone en el punto inicial
 */
void
Ball::resetBall(Vector3 pos){

	btVector3 zeroVector(0,0,0);
	btVector3 newPosVector(pos.x, pos.y, pos.z);

	_world->getBulletDynamicsWorld()->removeRigidBody(_rigidBall->getBulletRigidBody());
	_rigidBall->getBulletRigidBody()->clearForces();
	_rigidBall->getBulletRigidBody()->setLinearVelocity(zeroVector);
	_rigidBall->getBulletRigidBody()->setAngularVelocity(zeroVector);
	_rigidBall->getBulletRigidBody()->getWorldTransform().setOrigin(newPosVector);
	_ballNode->translate(pos);
	_world->getBulletDynamicsWorld()->addRigidBody(_rigidBall->getBulletRigidBody());

}

SceneNode*
Ball::getSceneNode(){
	return _ballNode;

}
