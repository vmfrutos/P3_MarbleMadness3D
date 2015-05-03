#include "LevelOne.h"

LevelOne::LevelOne(const string& groundMesh, const string& groundName): Level(){
	initializeParamsConf();
	printConf();
	initializeLevel(groundMesh,groundName);

	_launcherMode = false;
	_shootMode = false;
	_zone = ZONE1;
	timeCurrentZone = _timeToComplete;
}

LevelOne::~LevelOne(){

}

void
LevelOne::initializeLevel(const string& levelMesh, const string& levelName){

	// Se ponen las luces
	setLight();

	// Se añade el nivel
	addTriangleMeshCollisionShape(levelMesh, levelName,Vector3::ZERO, Quaternion::IDENTITY,0.8, 0.6, 0,_sceneManager->getRootSceneNode());
	//addConvexHullCollisionShape(levelMesh, levelName,Vector3::ZERO, Quaternion::IDENTITY,0.8, 0.6, 0,_sceneManager->getRootSceneNode());

	// Se crea el suelo
	_groundNode = addTriangleMeshCollisionShape("Ground.mesh","Ground",Vector3::ZERO, Quaternion::IDENTITY,0.8, 0.6, 0,_sceneManager->getRootSceneNode());


	// Se añade el goal
	_goalNode = addTriangleMeshCollisionShape("Goal.mesh", "Goal",Vector3(90.220467,10.058404,84.455559), Quaternion::IDENTITY,0.8, 0.6, 0,_sceneManager->getRootSceneNode());

	// Se añade la lava
	for (int i=1; i<=numLavaNodes;i++){
		//String meshName = StringConverter::toString("Lava" + i +".mesh");
		String meshName = "Lava";
		meshName.append(StringConverter::toString(i));
		meshName.append(".mesh");
		SceneNode* lava = addTriangleMeshCollisionShape(meshName.c_str(),"Lava" + i,Vector3::ZERO, Quaternion::IDENTITY,0.8, 0.6, 0,_sceneManager->getRootSceneNode());
		_lavaNodes.push_back(lava);
	}
	//_lavaNode = addTriangleMeshCollisionShape("Lava.mesh","Lava",Vector3::ZERO, Quaternion::IDENTITY,0.8, 0.6, 0,_sceneManager->getRootSceneNode());
	///_lavaNode = addConvexHullCollisionShape("Lava.mesh","Lava",Vector3::ZERO, Quaternion::IDENTITY,0.8, 0.6, 0,_sceneManager->getRootSceneNode());


	Enemy* enemy = new Enemy("Enemy1", Vector3(-32.441811,43.918213,-92.461182), Quaternion::IDENTITY);
	_enemyList.push_back(enemy);

	enemy = new Enemy("Enemy2", Vector3(-42.02232,43.918213,-81.868141), Quaternion::IDENTITY);
	_enemyList.push_back(enemy);

	enemy = new Enemy("Enemy3", Vector3(31.363861,43.173988,-35.965965), Quaternion::IDENTITY);
	_enemyList.push_back(enemy);

	enemy = new Enemy("Enemy4", Vector3(31.363861,22.969601,35.994324), Quaternion::IDENTITY);
	_enemyList.push_back(enemy);

	enemy = new Enemy("Enemy5", Vector3(10.135189,22.969601,35.994324), Quaternion::IDENTITY);
	_enemyList.push_back(enemy);

	enemy = new Enemy("Enemy6", Vector3(-40.063362,22.969601,35.994324), Quaternion::IDENTITY);
	_enemyList.push_back(enemy);


	//_lanzadera = new Lanzadera("lanz1",Vector3(67.43,43.66,-84.42));
	_lanzadera = new Lanzadera("lanz1",Vector3(67.43,40.0,-84.42));

	_zoneOneLimit = addStaticPlane("zoneOneLimit",Quaternion::IDENTITY,Vector3(-34.280739,44.106258,-44.940426),4,6);
	_zoneTwoLimit = addStaticPlane("zoneTwoLimit",Quaternion::IDENTITY,Vector3(31.444683,42.106258,-60.636444),4,6);
	_zoneThreeLimit = addStaticPlane("zoneThreeLimit",Quaternion::IDENTITY,Vector3(50.132198,42.106258,-9.181412),4,6);
	_zoneFourLimit = addStaticPlane("zoneFourLimit",Quaternion::IDENTITY,Vector3(-48.582283,22.06946,59.136009),4,6);

	PlayState::getSingletonPtr()->getHud()->setInfo("Zone 1");
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
	//_sceneManager->setShadowTextureSize(16384/2);
	//_sceneManager->setShadowTextureSettings( 1024, 1, PF_X8R8G8B8 );


	Ogre::Light* light = _sceneManager->createLight("Light1");
	//light->setDirection(-0.056,-0.998,-75.617767);
	//light->setPosition(-38.948658,200,-75.617767);

	light->setDirection(0,0,0);
	light->setPosition(0,350,0);

	light->setType(Ogre::Light::LT_POINT);
	light->setPowerScale(1.0);
	light->setCastShadows(true);
	light->setShadowNearClipDistance(1);
	light->setShadowFarClipDistance(400);

/*

	Ogre::Light* light2 = _sceneManager->createLight("Light2");

	light2->setDirection(0,0,0);
	light2->setPosition(-100,200,100);

	light2->setType(Ogre::Light::LT_POINT);
	light2->setPowerScale(1.0);
	light2->setCastShadows(true);
	light2->setShadowNearClipDistance(1);
	light2->setShadowFarClipDistance(300);

	Ogre::Light* light3 = _sceneManager->createLight("Light3");

	light3->setDirection(0,0,0);
	light3->setPosition(100,200,-100);

	light3->setType(Ogre::Light::LT_POINT);
	light3->setPowerScale(1.0);
	light3->setCastShadows(true);
	light3->setShadowNearClipDistance(1);
	light3->setShadowFarClipDistance(300);

	Ogre::Light* light4 = _sceneManager->createLight("Light4");

	light4->setDirection(0,0,0);
	light4->setPosition(-100,200,-100);

	light4->setType(Ogre::Light::LT_POINT);
	light4->setPowerScale(1.0);
	light4->setCastShadows(true);
	light4->setShadowNearClipDistance(1);
	light4->setShadowFarClipDistance(300);
*/



}



bool
LevelOne::isEndOfLive(SceneNode* ball){

	// Se comprueba si la bola colisiona con la lava o con el suelo
	//if (colisionNodes(ball,_lavaNode) || colisionNodes(ball,_groundNode)) {


	if (colisionNodes(ball,_groundNode)){
		return true;
	} else  {
		// Se comprueba si hay colision con enemigo
		for (unsigned int i=0; i<_enemyList.size();i++){
			if (colisionNodes(ball,_enemyList[i]->getSceneNode())){
				return true;
			}
		}

		// Se comprueba si hay colision con Lava
		for (unsigned int i=0; i<_lavaNodes.size();i++){
			if (colisionNodes(ball,_lavaNodes[i])){
				return true;
			}
		}
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
	_zoneTwoPositionBall = Properties::getSingletonPtr()->getPropertyVector("level1.ballPositionZone2");
	_zoneThreePositionBall = Properties::getSingletonPtr()->getPropertyVector("level1.ballPositionZone3");
	_zoneFourPositionBall = Properties::getSingletonPtr()->getPropertyVector("level1.ballPositionZone4");
	_zoneFivePositionBall = Properties::getSingletonPtr()->getPropertyVector("level1.ballPositionZone5");
	_timeToComplete = Properties::getSingletonPtr()->getPropertyFloat("level1.timeToComplete");
}

void
LevelOne::printConf() {
	Ogre::LogManager::getSingletonPtr()->logMessage("************** Level *****************");
	Ogre::LogManager::getSingletonPtr()->logMessage("level1.ballPosition: " + StringConverter::toString(_initPositionBall));
	Ogre::LogManager::getSingletonPtr()->logMessage("level1.ballPositionZone2: " + StringConverter::toString(_zoneTwoPositionBall));
	Ogre::LogManager::getSingletonPtr()->logMessage("level1.ballPositionZone3: " + StringConverter::toString(_zoneThreePositionBall));
	Ogre::LogManager::getSingletonPtr()->logMessage("level1.ballPositionZone4: " + StringConverter::toString(_zoneFourPositionBall));
	Ogre::LogManager::getSingletonPtr()->logMessage("level1.ballPositionZone5: " + StringConverter::toString(_zoneFivePositionBall));
	Ogre::LogManager::getSingletonPtr()->logMessage("level1.timeToComplete: " + StringConverter::toString(_timeToComplete));
	Ogre::LogManager::getSingletonPtr()->logMessage("***************************************");
}

void LevelOne::update(float delta){
	for (unsigned int i=0; i<_enemyList.size();i++){
		_enemyList[i]->update(delta);

	}

	_lanzadera->update(delta);
	checkTriggers();
}

void LevelOne::keyPressed(enum OIS::KeyCode key){

	if (_launcherMode) {
		if (key == OIS::KC_S){ // subir elevador
			_lanzadera->elevatorUp();
		} else if (key == OIS::KC_X){ // bajar elevador
			_lanzadera->elevatorDown();
		} else if (key == OIS::KC_Z){ // bajar elevador
			_lanzadera->elevatorStop();
		} else if (key == OIS::KC_E){
			_lanzadera->rotateSoporteLeft();
		} else if (key == OIS::KC_R){
			_lanzadera->rotateSoporteRight();
		} else if (key == OIS::KC_Q){
			_lanzadera->rotateCanyonUp();
		} else if (key == OIS::KC_A){
			_lanzadera->rotateCanyonDown();
		}

	}
	if (_shootMode) {
		if (key == OIS::KC_SPACE){
			_lanzadera->settingShootPower();
		}
	}

}

void LevelOne::keyReleased(enum OIS::KeyCode key){
	if (_launcherMode) {
		if (key == OIS::KC_R || key == OIS::KC_E){
			_lanzadera->rotateSoporteStop();
		} else if (key == OIS::KC_Q || key == OIS::KC_A){
			_lanzadera->rotateCanyonStop();
		}
	}

	if (_shootMode) {

		if (key == OIS::KC_SPACE){
			_lanzadera->shoot();
			_shootMode = false;
			PlayState::getSingletonPtr()->getHud()->setInfo("Zone 3\ns/x: Elevator up/down\ne/r: Canyon left/right\nq/a: Canyon up/down\nspace: Fire");
		}
	}
}


void
LevelOne::checkTriggers(){

	// Se comprueba si la bola esta en el canyon
	Ball* ball = PlayState::getSingletonPtr()->getBall();
	SceneNode* canyonnode = _lanzadera->getCanyonNode();
	if (colisionNodes(ball->getSceneNode(),canyonnode)){
		_shootMode = true;
	} else {
		_shootMode = false;
	}

	// Se comprueba si la bola colisiona con los planos de cambio de Zona
	if (colisionNodes(ball->getSceneNode(),_zoneOneLimit)){
		_zone = ZONE2;
		// Se almacena el instante temporal en el que se pas ade zona.
		// En caso de perder una vida se comienza en la zona con el mismo tiempo con el que se llegó
		timeCurrentZone = PlayState::getSingletonPtr()->getHud()->getCurrentTime();
		PlayState::getSingletonPtr()->getHud()->setInfo("Zone 2");
	} else if (colisionNodes(ball->getSceneNode(),_zoneTwoLimit)){
		_zone = ZONE3;
		timeCurrentZone = PlayState::getSingletonPtr()->getHud()->getCurrentTime();
		_launcherMode = true;
		PlayState::getSingletonPtr()->getHud()->setInfo("Zone 3\ns/x: Elevator up/down\ne/r: Canyon left/right\nq/a: Canyon up/down\nspace: Fire");
	} else if (colisionNodes(ball->getSceneNode(),_zoneThreeLimit)){
		_zone = ZONE4;
		timeCurrentZone = PlayState::getSingletonPtr()->getHud()->getCurrentTime();
		_launcherMode = false;
		PlayState::getSingletonPtr()->getHud()->setInfo("Zone 4");
	} else if (colisionNodes(ball->getSceneNode(),_zoneFourLimit)){
		_zone = ZONE5;
		timeCurrentZone = PlayState::getSingletonPtr()->getHud()->getCurrentTime();
		PlayState::getSingletonPtr()->getHud()->setInfo("Zone 5");
	}

}

Vector3
LevelOne::getInitPositionBall(){

	Vector3 pos;
	if (_zone == ZONE1){
		pos = _initPositionBall;
	} else if (_zone == ZONE2){
		pos = _zoneTwoPositionBall;
	} else if (_zone == ZONE3){
		pos = _zoneThreePositionBall;
	} else if (_zone == ZONE4){
		pos = _zoneFourPositionBall;
	} else if (_zone == ZONE5){
		pos = _zoneFivePositionBall;
	}

	return pos;

};

float
LevelOne::getTimeToComplete(){

	return timeCurrentZone;
}

