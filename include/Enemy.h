#ifndef __ENEMY_H__
#define __ENEMY_H__

#include <Ogre.h>
#include "PlayState.h"
#include <OgreBulletDynamicsRigidBody.h>
#include <Shapes/OgreBulletCollisionsStaticPlaneShape.h>
#include <Shapes/OgreBulletCollisionsBoxShape.h>
#include "Utils/OgreBulletCollisionsMeshToShapeConverter.h"
#include "Shapes/OgreBulletCollisionsTrimeshShape.h"
#include "Shapes/OgreBulletCollisionsCompoundShape.h"
#include "Shapes/OgreBulletCollisionsTrimeshShape.h"
#include "Shapes/OgreBulletCollisionsSphereShape.h"
#include "Shapes/OgreBulletCollisionsConvexHullShape.h"
#include "OgreBulletDynamicsWorld.h"
#include "OgreBulletDynamicsRigidBody.h"
#include "Debug/OgreBulletCollisionsDebugDrawer.h"
#include <BulletCollision/btBulletCollisionCommon.h>

#include "PhysicWorld.h"

using namespace Ogre;
using namespace std;

class Enemy : public PhysicWorld {
public:
	Enemy(const string& name,const Vector3& pos,const Quaternion& orientation);
	~Enemy();
	void update(float delta);
	void move(float delta);
	SceneNode* getSceneNode(){return _enemyNode;};
	//bool collisionWithBall(SceneNode* node);

private:
	SceneNode* _enemyNode;
	AnimationState *_animEnemy;
	Vector3 _initPos;
	OgreBulletDynamics::RigidBody* _enemyRigidBody;


	float _avanzado;
	float _speed;
	int _direccion;

	string _name;

	const int NORTH = 0;
	const int EAST = 1;
	const int SOUTH =2;
	const int WEST = 3;

	//void createConstraintEnemy();

};
#endif
