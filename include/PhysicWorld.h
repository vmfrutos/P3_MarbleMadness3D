#ifndef __PHYSIC_WORLD_H__
#define __PHYSIC_WORLD_H__

#include <Ogre.h>
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

#include "Properties.h"
#include "PhysicWorld.h"

using namespace Ogre;
class PhysicWorld {

public:
	PhysicWorld();
	virtual ~PhysicWorld();
public:

	// Colas para gestionas los cuerpos rigidos y las formas de colision
	static std::deque <OgreBulletDynamics::RigidBody *>         _bodies;
	static std::deque <OgreBulletCollisions::CollisionShape *>  _shapes;


	// Mundo fisico
	static OgreBulletDynamics::DynamicsWorld * _world;
	static OgreBulletCollisions::DebugDrawer * _debugDrawer;

	// Gestor de escena
	static SceneManager * _sceneManager;

	static void initializeWorld(SceneManager* sceneManager);
	static void showDebugShapes(bool value);
	static void stepSimulation(float elapsedTime, int maxSubSteps = 1);

private:
	static float _gravity;
	static Vector3 _wordlBounds;
	static bool _setDebugDrawer;
	static void initializeParamsConf();
	static void printConf();
};
#endif
