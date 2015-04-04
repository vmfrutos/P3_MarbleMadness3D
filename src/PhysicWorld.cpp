#include "PhysicWorld.h"

// Variables staticas que pueden usar los herederos de PhysicWorld
template<> SceneManager* PhysicWorld::_sceneManager;
template<> std::deque <OgreBulletDynamics::RigidBody *> PhysicWorld::_bodies;
template<> std::deque <OgreBulletCollisions::CollisionShape *> PhysicWorld::_shapes;
template<> OgreBulletDynamics::DynamicsWorld * PhysicWorld::_world;
template<> OgreBulletCollisions::DebugDrawer * PhysicWorld::_debugDrawer;

// Variables staticas que no pueden usar los herederos de PhysicWorld
template<> float PhysicWorld::_gravity;
template<> Vector3 PhysicWorld::_wordlBounds;
template<> bool PhysicWorld::_setDebugDrawer;


PhysicWorld::PhysicWorld() {
}
PhysicWorld::~PhysicWorld(){

}

void PhysicWorld::initializeParamsConf() {
	_gravity = Properties::getSingletonPtr()->getPropertyFloat("world.gravity");
	_wordlBounds = Properties::getSingletonPtr()->getPropertyVector("world.bounds");
	_setDebugDrawer = Properties::getSingletonPtr()->getPropertyBool("world.setDebugDrawer");
}

void
PhysicWorld::finalizeWorld(){
	deleteDeques();

	if (_setDebugDrawer) {
		// Eliminacion de debugDrawer -------------------------
		if (_world && _world->getDebugDrawer()){
			delete _world->getDebugDrawer();
			_world->setDebugDrawer(0);
		}

	}

	// Eliminar mundo dinamico
	if (_world){
		delete _world;
		_world = NULL;
	}
}

void
PhysicWorld::initializeWorld(SceneManager* sceneManager){
	initializeParamsConf();

	_sceneManager = sceneManager;

	// Creacion del mundo (definicion de los limites y la gravedad) ---
	AxisAlignedBox worldBounds = AxisAlignedBox ((_wordlBounds * -1), _wordlBounds);
	Vector3 gravity = Vector3(0, -_gravity, 0);

	_world = new OgreBulletDynamics::DynamicsWorld(_sceneManager,worldBounds, gravity);

	if (_setDebugDrawer) {
		// Creacion del modulo de debug visual de Bullet ------------------
		_debugDrawer = new OgreBulletCollisions::DebugDrawer();
		_debugDrawer->setDrawWireframe(true);
		SceneNode *node = _sceneManager->getRootSceneNode()->createChildSceneNode("debugNode", Vector3::ZERO);
		node->attachObject(static_cast <SimpleRenderable *>(_debugDrawer));
		_world->setDebugDrawer (_debugDrawer);
	}

	// Se imprimen los parámetros configurables
	printConf();
}

void
PhysicWorld::printConf(){
	Ogre::LogManager::getSingletonPtr()->logMessage("*********** Physic World **************");
	Ogre::LogManager::getSingletonPtr()->logMessage("world.gravity: " + StringConverter::toString(_gravity));
	Ogre::LogManager::getSingletonPtr()->logMessage("world.bounds: " + StringConverter::toString(_wordlBounds));
	Ogre::LogManager::getSingletonPtr()->logMessage("world.setDebugDrawer: " + StringConverter::toString(_setDebugDrawer));
	Ogre::LogManager::getSingletonPtr()->logMessage("***************************************");
}

void
PhysicWorld::showDebugShapes(bool value){
	if (_setDebugDrawer) {
		_world->setShowDebugShapes (value);
	}
}

void
PhysicWorld::stepSimulation(float elapsedTime, int maxSubSteps){
	_world->stepSimulation(elapsedTime,maxSubSteps);
}

void
PhysicWorld::deleteDeques(){
	// Eliminar cuerpos rigidos --------------------------------------
	std::deque <OgreBulletDynamics::RigidBody *>::iterator
	itBody = _bodies.begin();
	while (_bodies.end() != itBody) {
		delete *itBody;  ++itBody;
	}

	// Eliminar formas de colision -----------------------------------
	std::deque<OgreBulletCollisions::CollisionShape *>::iterator
	itShape = _shapes.begin();
	while (_shapes.end() != itShape) {
		delete *itShape; ++itShape;
	}

	_bodies.clear();
	_shapes.clear();
}

