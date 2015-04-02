#include "LevelOne.h"

LevelOne::LevelOne(const string& groundMesh, const string& groundName): Level(){
	_lavaNode = NULL;
	initializeParamsConf();
	printConf();
	initializeLevel(groundMesh,groundName);
}

LevelOne::~LevelOne(){

}

void
LevelOne::initializeLevel(const string& groundMesh, const string& groundName){

	// Se ponen las luces
	setLight();
	// Se crea el suelo
	addGround(groundMesh, groundName);

	// Se añade la lava
	addLava("Lava.mesh","Lava");
}

int
LevelOne::getLevelNumber() {
	return 1;
}

void
LevelOne::setLight(){
	Ogre::Light* light = _sceneManager->createLight("Light1");
	light->setDirection(Ogre::Vector3(0.0,80.0,0.0));
	light->setPosition(0,0,0);
	light->setType(Ogre::Light::LT_DIRECTIONAL);
	light->setPowerScale(1.7299998998641968);
	light->setCastShadows(true);

	Ogre::Light* light2 = _sceneManager->createLight("Light2");
	light2->setDirection(Ogre::Vector3(-124.08334,74.37983,-74.70168));
	light2->setPosition(-81.55,50.415,-91.68);
	light2->setType(Ogre::Light::LT_DIRECTIONAL);
	light2->setPowerScale(1.7299998998641968);
	light2->setCastShadows(true);
}

void
LevelOne::addLava(const string& lavaMesh, const string& lavaName){
	_lavaNode = _sceneManager->createSceneNode(lavaName);
	Entity* LavaEnt = _sceneManager->createEntity(lavaName, lavaMesh);
	LavaEnt->setCastShadows(false);

	_lavaNode->attachObject(LavaEnt);
	_sceneManager->getRootSceneNode()->addChild(_lavaNode);


	// Se crea un objetp StaticMeshToShapeConverter a partir de la mesh de las zonas de lava
	OgreBulletCollisions::StaticMeshToShapeConverter *trimeshConverter = new OgreBulletCollisions::StaticMeshToShapeConverter(LavaEnt);

	// Se crea obtiene la forma de colision basada en triangulos TriangleMeshCollisionShape
	OgreBulletCollisions::TriangleMeshCollisionShape *lavaTrimesh = trimeshConverter->createTrimesh();

	// TODO: Probar en la teoría pone que es mas eficiente!!!!!!
	//OgreBulletCollisions::ConvexHullCollisionShape *groundConvex = trimeshConverter->createConvex();

	// Se crea el rigbody
	OgreBulletDynamics::RigidBody *rigidLava = new OgreBulletDynamics::RigidBody(lavaName, _world);
	rigidLava->setShape(_lavaNode, lavaTrimesh, 0.8, 0.6, 0, Vector3::ZERO, Quaternion::IDENTITY);
	delete trimeshConverter;

	// Se añade la forma de colision y el cuerpo rigido a las colas correspondientes
	_bodies.push_back(rigidLava);
	_shapes.push_back(lavaTrimesh);
}

bool
LevelOne::colisionWithLava(SceneNode* node){
	btCollisionWorld *bulletWorld=_world->getBulletCollisionWorld();
	int numManifolds=bulletWorld->getDispatcher()->getNumManifolds();

	for (int i=0;i<numManifolds;i++) {
		btPersistentManifold* contactManifold = bulletWorld->getDispatcher()->getManifoldByIndexInternal(i);
		btCollisionObject* obA = const_cast<btCollisionObject*>(contactManifold->getBody0());
		btCollisionObject* obB = const_cast<btCollisionObject*>(contactManifold->getBody1());

		OgreBulletCollisions::Object *obFinded = _world->findObject(node);
		OgreBulletCollisions::Object *obLava = _world->findObject(_lavaNode);

		OgreBulletCollisions::Object *obOB_A = _world->findObject(obA);
		OgreBulletCollisions::Object *obOB_B = _world->findObject(obB);

		if (obOB_A == obFinded){
			cout << "obOB_A" << obOB_A->getWorldPosition() << endl;
		}

		if (obOB_B == obFinded){
			cout << "obOB_B" << obOB_B->getWorldPosition() << endl;
		}

		if (obOB_A == obFinded || obOB_B == obFinded){
			if (obOB_A == obLava || obOB_B == obLava){
				return true;
			}
		}
	}
	return false;
}

bool
LevelOne::isEndOfLive(SceneNode* ball){

	// Se comprueba si la bola colisiona con la lava
	if (colisionWithLava(ball)) {
		return true;
	}
	return false;
}

void
LevelOne::initializeParamsConf() {
	_initPositionBall = Properties::getSingletonPtr()->getPropertyVector("level1.ballPosition");
	_timeToComplete = Properties::getSingletonPtr()->getPropertyFloat("level1.timeToComplete");
}

void
LevelOne::printConf() {
	Ogre::LogManager::getSingletonPtr()->logMessage("************** Level *****************");
	Ogre::LogManager::getSingletonPtr()->logMessage("level1.ballPosition: " + StringConverter::toString(_initPositionBall));
	Ogre::LogManager::getSingletonPtr()->logMessage("level1.timeToComplete: " + StringConverter::toString(_timeToComplete));
	Ogre::LogManager::getSingletonPtr()->logMessage("***************************************");
}
