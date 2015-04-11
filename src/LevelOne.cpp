#include "LevelOne.h"

LevelOne::LevelOne(const string& groundMesh, const string& groundName): Level(){
	initializeParamsConf();
	printConf();
	initializeLevel(groundMesh,groundName);
}

LevelOne::~LevelOne(){

}

void
LevelOne::initializeLevel(const string& levelMesh, const string& levelName){

	// Se ponen las luces
	setLight();
	// Se crea el suelo
	_groundNode = addTriangleMeshCollisionShape("Ground.mesh","Ground",Vector3::ZERO, Quaternion::IDENTITY,0.8, 0.6, 0);

	// Se añade el nivel
	addTriangleMeshCollisionShape(levelMesh, levelName,Vector3::ZERO, Quaternion::IDENTITY,0.8, 0.6, 0);

	// Se añade el goal
	_goalNode = addTriangleMeshCollisionShape("Goal.mesh", "Goal",Vector3(9.43009,40.015583,-90.266342), Quaternion::IDENTITY,0.8, 0.6, 0);

	// Se añade la lava
	_lavaNode = addTriangleMeshCollisionShape("Lava.mesh","Lava",Vector3::ZERO, Quaternion::IDENTITY,0.8, 0.6, 0);
}

int
LevelOne::getLevelNumber() {
	return 1;
}

void
LevelOne::setLight(){

	_sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_TEXTURE_MODULATIVE);
	_sceneManager->setShadowColour(Ogre::ColourValue(0.5, 0.5, 0.5) );
	_sceneManager->setAmbientLight(Ogre::ColourValue(0.9, 0.9, 0.9));
	_sceneManager->setShadowTextureCount(1);
	_sceneManager->setShadowTextureSize(2048);
	//_sceneManager->setShadowTextureSettings( 1024, 1, PF_X8R8G8B8 );


	Ogre::Light* light = _sceneManager->createLight("Light1");
	light->setDirection(-0.056,-0.998,-75.617767);
	light->setPosition(-38.948658,200,-75.617767);
	light->setType(Ogre::Light::LT_POINT);
	light->setPowerScale(1.0);
	light->setCastShadows(true);
	light->setShadowNearClipDistance(1);
	light->setShadowFarClipDistance(180);

}



bool
LevelOne::isEndOfLive(SceneNode* ball){

	// Se comprueba si la bola colisiona con la lava o con el suelo
	if (colisionNodes(ball,_lavaNode) || colisionNodes(ball,_groundNode)) {
		return true;

	}
	return false;
}

bool
LevelOne::isLevelCompleted(SceneNode* ball){
	// Se comprueba si la bola colisiona con el plano Goal
	if (colisionNodes(ball,_goalNode)) {
		// Se cambia el color de las letras del plano Goal
		((Entity*)_goalNode->getAttachedObject("Goal"))->setMaterialName("goalGreen");
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
