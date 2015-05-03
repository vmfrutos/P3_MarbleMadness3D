#include "Enemy.h"

Enemy::Enemy(const string& name,const Vector3& pos,const Quaternion& orientation){

	_name = name;
	_initPos = pos;

	_enemyNode = addConvexHullCollisionShape("Enemy.mesh",_name,_initPos,Quaternion::IDENTITY,0.0, 0.6, 1.0,_sceneManager->getRootSceneNode());

	_enemyRigidBody = 0;

	for (unsigned int i=0;i<_bodies.size();i++){
		if (_bodies[i]->getName() == _name){
			_enemyRigidBody = _bodies[i];
		}
	}

	// Esto evita que el enemigo se caigo. No puede rotar sobre ningun eje.
	_enemyRigidBody->getBulletRigidBody()->setAngularFactor(btVector3(0, 0, 0));


	_animEnemy = ((Entity*)_enemyNode->getAttachedObject(_name))->getAnimationState("enemyAction");
	_animEnemy->setEnabled(true);
	_animEnemy->setLoop(true);

	_speed = 5.0;
	_avanzado = 0;
	_direccion = NORTH;


}

Enemy::~Enemy(){

}

void
Enemy::update(float delta){
	_animEnemy->addTime(delta);
	move(delta);

}

void
Enemy::move(float delta){
	_enemyRigidBody->getBulletRigidBody()->activate(true);

	if (_direccion == NORTH) {
		_avanzado += delta * _speed;
		if (_avanzado <= 10.0){
			_enemyRigidBody->getBulletRigidBody()->translate(btVector3(0.0,0.0,1.0*delta * _speed));

		} else {
			_avanzado = 0;
			_direccion = EAST;
		}
	} else if (_direccion == EAST) {
		_avanzado += delta * _speed;
		if (_avanzado <= 10.0){
			_enemyRigidBody->getBulletRigidBody()->translate(btVector3(-1.0*delta * _speed,0.0,0.0));

		} else {
			_avanzado = 0;
			_direccion = SOUTH;
		}
	} else if (_direccion == SOUTH) {
		_avanzado += delta * _speed;
		if (_avanzado <= 10.0){
			_enemyRigidBody->getBulletRigidBody()->translate(btVector3(0.0,0.0,-1.0*delta * _speed));

		} else {
			_avanzado = 0;
			_direccion = WEST;
		}
	} else if (_direccion == WEST) {
		_avanzado += delta * _speed;
		if (_avanzado <= 10.0){
			_enemyRigidBody->getBulletRigidBody()->translate(btVector3(1.0*delta * _speed,0.0,0.0));

		} else {
			_avanzado = 0;
			_direccion = NORTH;
		}
	}
}


