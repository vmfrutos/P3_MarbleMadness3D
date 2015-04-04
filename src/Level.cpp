#include <Level.h>




Level::Level():PhysicWorld(){

	initializeParamsConf();
	printConf();
}

Level::~Level(){

}


void
Level::initializeParamsConf() {
	_restitution = Properties::getSingletonPtr()->getPropertyFloat("ground.restitution");
	_friction = Properties::getSingletonPtr()->getPropertyFloat("ground.friction");
	_mass = Properties::getSingletonPtr()->getPropertyFloat("ground.mass");
}

void Level::printConf() {
	Ogre::LogManager::getSingletonPtr()->logMessage("************** Level *****************");
	Ogre::LogManager::getSingletonPtr()->logMessage("ground.restitution: " + StringConverter::toString(_restitution));
	Ogre::LogManager::getSingletonPtr()->logMessage("ground.friction: " + StringConverter::toString(_friction));
	Ogre::LogManager::getSingletonPtr()->logMessage("ground.mass: " + StringConverter::toString(_mass));
	Ogre::LogManager::getSingletonPtr()->logMessage("***************************************");
}

SceneNode*
Level::addTriangleMeshCollisionShape(
		const string& mesh,
		const string& name,
		const Vector3& pos,
		const Quaternion& orientation,
		const float restitution,
		const float friction,
		const float mass){
	SceneNode* node = _sceneManager->createSceneNode(name);
	Entity* ent = _sceneManager->createEntity(name, mesh);
	ent->setCastShadows(false);

	node->attachObject(ent);
	_sceneManager->getRootSceneNode()->addChild(node);


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


bool
Level::colisionNodes(SceneNode* node1, SceneNode* node2){
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
				return true;
			}
		}
	}
	return false;
}
