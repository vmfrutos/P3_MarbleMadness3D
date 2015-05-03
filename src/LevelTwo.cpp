#include "LevelTwo.h"

LevelTwo::LevelTwo(const string& groundMesh, const string& groundName): Level(){
	initializeParamsConf();
	printConf();
	initializeLevel(groundMesh,groundName);
}

LevelTwo::~LevelTwo(){

}

void
LevelTwo::initializeLevel(const string& levelMesh, const string& levelName){

	// Se ponen las luces
	setLight();
	// Se crea el suelo
	_groundNode = addTriangleMeshCollisionShape("Ground.mesh","Ground",Vector3::ZERO, Quaternion::IDENTITY,0.8, 0.6, 0,_sceneManager->getRootSceneNode());

	// Se añade el nivel
	addTriangleMeshCollisionShape(levelMesh, levelName,Vector3::ZERO, Quaternion::IDENTITY,0.8, 0.6, 0,_sceneManager->getRootSceneNode());

	// Se añade el goal
	_goalNode = addTriangleMeshCollisionShape("Goal.mesh", "Goal",Vector3(9.43009,40.015583,-90.266342), Quaternion::IDENTITY,0.8, 0.6, 0,_sceneManager->getRootSceneNode());

	// Se añade la lava
	_lavaNode = addTriangleMeshCollisionShape("Lava.mesh","Lava",Vector3::ZERO, Quaternion::IDENTITY,0.8, 0.6, 0,_sceneManager->getRootSceneNode());
}

int
LevelTwo::getLevelNumber() {
	return 2;
}

void
LevelTwo::setLight(){
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



bool
LevelTwo::isEndOfLive(SceneNode* ball){

	// Se comprueba si la bola colisiona con la lava o con el suelo
	if (colisionNodes(ball,_lavaNode) || colisionNodes(ball,_groundNode)) {
		return true;

	}
	return false;
}

bool
LevelTwo::isLevelCompleted(SceneNode* ball){
	// Se comprueba si la bola colisiona con el plano Goal
	if (colisionNodes(ball,_goalNode)) {
		// Se cambia el color de las letras del plano Goal
		((Entity*)_goalNode->getAttachedObject("Goal"))->setMaterialName("goalGreen");
		return true;

	}
	return false;
}

void
LevelTwo::initializeParamsConf() {
	_initPositionBall = Properties::getSingletonPtr()->getPropertyVector("level2.ballPosition");
	_timeToComplete = Properties::getSingletonPtr()->getPropertyFloat("level2.timeToComplete");
}

void
LevelTwo::printConf() {
	Ogre::LogManager::getSingletonPtr()->logMessage("************** Level *****************");
	Ogre::LogManager::getSingletonPtr()->logMessage("level2.ballPosition: " + StringConverter::toString(_initPositionBall));
	Ogre::LogManager::getSingletonPtr()->logMessage("level2.timeToComplete: " + StringConverter::toString(_timeToComplete));
	Ogre::LogManager::getSingletonPtr()->logMessage("***************************************");
}

void
LevelTwo::update(float delta){

}

void
LevelTwo::keyPressed(enum OIS::KeyCode key){

}

void LevelTwo::keyReleased(enum OIS::KeyCode key){

}
