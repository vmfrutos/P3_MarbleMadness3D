#include <Level.h>




Level::Level():PhysicWorld(){

	initializeParamsConf();
	printConf();
}

Level::~Level(){

}

void
Level::addGround(const string& groundMesh, const string& groundName) {
	// Creacion de la entidad y del SceneNode del plano
	SceneNode* PlanoNode = _sceneManager->createSceneNode(groundName);
	Entity* PlanoEnt = _sceneManager->createEntity(groundName, groundMesh);
	PlanoEnt->setCastShadows(false);

	PlanoNode->attachObject(PlanoEnt);
	_sceneManager->getRootSceneNode()->addChild(PlanoNode);


	// Se crea un objetp StaticMeshToShapeConverter a partir de la mesh del suelo
	OgreBulletCollisions::StaticMeshToShapeConverter *trimeshConverter = new OgreBulletCollisions::StaticMeshToShapeConverter(PlanoEnt);

	// Se crea obtiene la forma de colision basada en triangulos TriangleMeshCollisionShape
	OgreBulletCollisions::TriangleMeshCollisionShape *groundTrimesh = trimeshConverter->createTrimesh();

	// TODO: Probar en la teoría pone que es mas eficiente!!!!!!
	//OgreBulletCollisions::ConvexHullCollisionShape *groundConvex = trimeshConverter->createConvex();

	// Se crea el rigbody
	OgreBulletDynamics::RigidBody *rigidPlane = new OgreBulletDynamics::RigidBody(groundName, _world);
	rigidPlane->setShape(PlanoNode, groundTrimesh, _restitution, _friction, _mass, Vector3::ZERO, Quaternion::IDENTITY);
	delete trimeshConverter;

	// Se añade la forma de colision y el cuerpo rigido a las colas correspondientes
	_bodies.push_back(rigidPlane);
	_shapes.push_back(groundTrimesh);

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
