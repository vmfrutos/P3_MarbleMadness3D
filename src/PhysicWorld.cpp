#include "PhysicWorld.h"

// Variables staticas que pueden usar los herederos de PhysicWorld
SceneManager* PhysicWorld::_sceneManager;
std::deque <OgreBulletDynamics::RigidBody *> PhysicWorld::_bodies;
std::deque <OgreBulletCollisions::CollisionShape *> PhysicWorld::_shapes;
OgreBulletDynamics::DynamicsWorld * PhysicWorld::_world;
OgreBulletCollisions::DebugDrawer * PhysicWorld::_debugDrawer;

// Variables staticas que no pueden usar los herederos de PhysicWorld
float PhysicWorld::_gravity;
Vector3 PhysicWorld::_wordlBounds;
bool PhysicWorld::_setDebugDrawer;


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
		_debugDrawer->setDebugMode(btIDebugDraw::DBG_DrawConstraints);
		_debugDrawer->setDebugMode(btIDebugDraw::DBG_DrawConstraintLimits);


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

SceneNode*
PhysicWorld::addTriangleMeshCollisionShape(
		const string& mesh,
		const string& name,
		const Vector3& pos,
		const Quaternion& orientation,
		const float restitution,
		const float friction,
		const float mass,
		SceneNode* parent){
	SceneNode* node = _sceneManager->createSceneNode(name);
	Entity* ent = _sceneManager->createEntity(name, mesh);
	ent->setCastShadows(false);

	node->attachObject(ent);
	parent->addChild(node);


	// Se crea un objetp StaticMeshToShapeConverter a partir de la mesh de las zonas de lava
	OgreBulletCollisions::StaticMeshToShapeConverter *trimeshConverter = new OgreBulletCollisions::StaticMeshToShapeConverter(ent);

	// Se crea obtiene la forma de colision basada en triangulos TriangleMeshCollisionShape
	OgreBulletCollisions::TriangleMeshCollisionShape *colisionShape = trimeshConverter->createTrimesh();

	// TODO: Probar en la teoría pone que es mas eficiente!!!!!!
	//OgreBulletCollisions::ConvexHullCollisionShape *groundConvex = trimeshConverter->createConvex();

	// Se crea el rigbody
	OgreBulletDynamics::RigidBody *rigidBody = new OgreBulletDynamics::RigidBody(name, _world);
	rigidBody->setShape(node, colisionShape, restitution, friction, mass, pos, orientation);
	delete trimeshConverter;

	// Se añade la forma de colision y el cuerpo rigido a las colas correspondientes
	_bodies.push_back(rigidBody);
	_shapes.push_back(colisionShape);

	return node;
}

SceneNode*
PhysicWorld::addConvexHullCollisionShape(
		const string& mesh,
		const string& name,
		const Vector3& pos,
		const Quaternion& orientation,
		const float restitution,
		const float friction,
		const float mass,
		SceneNode* parent){
	SceneNode* node = _sceneManager->createSceneNode(name);
	Entity* ent = _sceneManager->createEntity(name, mesh);
	ent->setCastShadows(false);

	node->attachObject(ent);
	parent->addChild(node);


	// Se crea un objetp StaticMeshToShapeConverter a partir de la mesh de las zonas de lava
	OgreBulletCollisions::StaticMeshToShapeConverter *trimeshConverter = new OgreBulletCollisions::StaticMeshToShapeConverter(ent);

	// Se crea obtiene la forma de colision basada en triangulos TriangleMeshCollisionShape
	//OgreBulletCollisions::TriangleMeshCollisionShape *colisionShape = trimeshConverter->createTrimesh();

	// TODO: Probar en la teoría pone que es mas eficiente!!!!!!
	OgreBulletCollisions::ConvexHullCollisionShape *groundConvex = trimeshConverter->createConvex();

	// Se crea el rigbody
	OgreBulletDynamics::RigidBody *rigidBody = new OgreBulletDynamics::RigidBody(name, _world);
	rigidBody->setShape(node, groundConvex, restitution, friction, mass, pos, orientation);
	delete trimeshConverter;

	// Se añade la forma de colision y el cuerpo rigido a las colas correspondientes
	_bodies.push_back(rigidBody);
	_shapes.push_back(groundConvex);

	return node;
}


SceneNode*
PhysicWorld::addRigidBody(
		OgreBulletCollisions::CollisionShape* collisionShape,
		const string& mesh,
		const string& name,
		const Vector3& pos,
		const Quaternion& orientation,
		const float restitution,
		const float friction,
		const float mass,
		SceneNode* parent){
	SceneNode* node = _sceneManager->createSceneNode(name);
	Entity* ent = _sceneManager->createEntity(name, mesh);
	ent->setCastShadows(false);

	node->attachObject(ent);
	parent->addChild(node);

	// Se crea el rigbody
	OgreBulletDynamics::RigidBody *rigidBody = new OgreBulletDynamics::RigidBody(name, _world);
	rigidBody->setShape(node, collisionShape, restitution, friction, mass, pos, orientation);
	//delete trimeshConverter;

	// Se añade la forma de colision y el cuerpo rigido a las colas correspondientes
	_bodies.push_back(rigidBody);
	_shapes.push_back(collisionShape);

	return node;
}

SceneNode*
PhysicWorld::addStaticPlane(
		const string& name,
		const Quaternion& orientation,
		const Vector3& pos,
		const float sizeX,
		const float sizeY){

	SceneNode* node = _sceneManager->createSceneNode(name);
	Entity* ent = _sceneManager->createEntity(name, "Plane.mesh");
	ent->setCastShadows(false);

	node->attachObject(ent);
	_sceneManager->getRootSceneNode()->addChild(node);
	node->setPosition(pos);
	node->setVisible(false);

	OgreBulletCollisions::BoxCollisionShape *box = new OgreBulletCollisions::BoxCollisionShape(Vector3(sizeX,sizeY,0.2));

	// Se crea el rigbody
	OgreBulletDynamics::RigidBody *rigidBody = new OgreBulletDynamics::RigidBody(name, _world);
	rigidBody->setShape(node, box, 0.0, 0.0, 0.0, pos, orientation);
	rigidBody->getBulletRigidBody()->setAngularFactor(btVector3(0, 0, 0));

	// Esto es para que este plano no colisione con nada
	rigidBody->getBulletRigidBody()->setCollisionFlags(rigidBody->getBulletRigidBody()->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);

	// Se añade la forma de colision y el cuerpo rigido a las colas correspondientes
	_bodies.push_back(rigidBody);
	_shapes.push_back(box);

	return node;
}

bool
PhysicWorld::colisionNodes(SceneNode* node1, SceneNode* node2){
	btCollisionWorld *bulletWorld=_world->getBulletCollisionWorld();
	int numManifolds=bulletWorld->getDispatcher()->getNumManifolds();

	for (int i=0;i<numManifolds;i++) {
		btPersistentManifold* contactManifold = bulletWorld->getDispatcher()->getManifoldByIndexInternal(i);
		btCollisionObject* obA = const_cast<btCollisionObject*>(contactManifold->getBody0());
		btCollisionObject* obB = const_cast<btCollisionObject*>(contactManifold->getBody1());

		OgreBulletCollisions::Object *obFinded1 = _world->findObject(node1);
		OgreBulletCollisions::Object *obFinded2 = _world->findObject(node2);

		OgreBulletCollisions::Object *obOB_A = _world->findObject(obA);
		OgreBulletCollisions::Object *obOB_B = _world->findObject(obB);

		if (obOB_A == obFinded1 || obOB_B == obFinded1){
			if (obOB_A == obFinded2 || obOB_B == obFinded2){
				cout << "colision entre [" << obOB_A->getName() + "] y [" << obOB_B->getName() << "]" << endl;
				cout << "Posicion de objeto A [" << StringConverter::toString(obOB_A->getWorldPosition()) << endl;
				cout << "Posicion de objeto B [" << StringConverter::toString(obOB_B->getWorldPosition()) << endl;
				return true;
			}
		}
	}
	return false;
}



