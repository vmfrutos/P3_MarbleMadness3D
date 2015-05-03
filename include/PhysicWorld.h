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
#include "Shapes/OgreBulletCollisionsGImpactShape.h"
#include "Shapes/OgreBulletCollisionsConeShape.h"
#include "Shapes/OgreBulletCollisionsCylinderShape.h"
#include "OgreBulletDynamicsWorld.h"
#include "OgreBulletDynamicsRigidBody.h"
#include "Debug/OgreBulletCollisionsDebugDrawer.h"
#include <BulletCollision/btBulletCollisionCommon.h>

#include "Properties.h"
#include "PhysicWorld.h"

using namespace Ogre;
class PhysicWorld {

public:
	PhysicWorld(SceneManager* sceneManager);
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

	void initializeWorld(SceneManager* sceneManager);
	void finalizeWorld();
	void deleteDeques();
	void showDebugShapes(bool value);
	void stepSimulation(float elapsedTime, int maxSubSteps = 1);

	bool colisionNodes(SceneNode* node1, SceneNode* node2);
	SceneNode* addTriangleMeshCollisionShape(
				const string& mesh,
				const string& name,
				const Vector3& pos,
				const Quaternion& orientation,
				const float restitution,
				const float friction,
				const float mass,
				SceneNode* parent);

	SceneNode* addConvexHullCollisionShape(
				const string& mesh,
				const string& name,
				const Vector3& pos,
				const Quaternion& orientation,
				const float restitution,
				const float friction,
				const float mass,
				SceneNode* parent);

	SceneNode* addRigidBody(
			OgreBulletCollisions::CollisionShape* collisionShape,
			const string& mesh,
			const string& name,
			const Vector3& pos,
			const Quaternion& orientation,
			const float restitution,
			const float friction,
			const float mass,
			SceneNode* parent);

	SceneNode* addStaticPlane(
			const string& name,
			const Quaternion& orientation,
			const Vector3& pos,
			const float sizeX,
			const float sizeY);

private:
	static float _gravity;
	static Vector3 _wordlBounds;
	static bool _setDebugDrawer;
	void initializeParamsConf();
	void printConf();
};
#endif
