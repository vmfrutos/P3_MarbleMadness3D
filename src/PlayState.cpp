#include "PlayState.h"


template<> PlayState* Ogre::Singleton<PlayState>::msSingleton = 0;

PlayState::PlayState() {
	_root = 0;
	_win = 0;
	_sceneMgr = 0;
	_viewport = 0;
	_exitGame = false;
	_currentLevel = 0;
	_ball = 0;
	_camera = 0;
	_hud=0;
	_currentLevelNumber = 0;
	_physicWorld = 0;

	KEY_UP = false;
	KEY_DOWN = false;
	KEY_RIGHT = false;
	KEY_LEFT = false;
}

PlayState::~PlayState() {

}

void
PlayState::enter ()
{
	_root = Ogre::Root::getSingletonPtr();

	_win = _root->getAutoCreatedWindow();
	_sceneMgr = _root->createSceneManager(Ogre::ST_GENERIC, "SceneManagerPlay");

	// Se define una camara
	_camera = new ::Camera(_sceneMgr);

	_viewport = _win->addViewport(_camera->getOgreCamera());
	_viewport->setBackgroundColour(Ogre::ColourValue(0.016, 0.454, 0.467));


	// Se inicializan los valores de configuracion
	initializeParamsConf();

	// Se imprimen los parametro sconfigurables
	printConf();

	_physicWorld = new PhysicWorld();

	// Se inicia una nueva partida
	startGame();

}

void
PlayState::exit ()
{
	KEY_UP = false;
	KEY_DOWN = false;
	KEY_RIGHT = false;
	KEY_LEFT = false;

	if (_physicWorld){
		_physicWorld->finalizeWorld();
		delete _physicWorld;
		_physicWorld = NULL;
	}

	if (_hud) {
		delete _hud;
		_hud = NULL;
	}


	// Se elimina el actual nivel si existe
	if (_currentLevel) {
		delete _currentLevel;
	}


	if (_ball) {
		delete _ball;
		_ball = NULL;
	}


	// Se vacia el scene manager
	_sceneMgr->clearScene();


	if (_root) {
		if (_sceneMgr) {
			_root->destroySceneManager(_sceneMgr);
		}
		_root->getAutoCreatedWindow()->removeAllViewports();
	}

}

void
PlayState::pause()
{
	KEY_UP = false;
	KEY_DOWN = false;
	KEY_RIGHT = false;
	KEY_LEFT = false;
}

void
PlayState::resume()
{

}

bool
PlayState::frameStarted
(const Ogre::FrameEvent& evt)
{

	Ogre::Real deltaT = evt.timeSinceLastFrame;

	_physicWorld->stepSimulation(deltaT);


	float fps;


	if (deltaT == 0.0) {
		fps = 1000; // esto es por evitar división por 0 en equipos muy rápidos
	} else {
		fps = 1.0f / deltaT;
	}


	if (KEY_UP) {
		Ogre::Vector3 direction(0,0,1);
		_ball->applyImpulse(direction,deltaT);

	}

	if (KEY_DOWN) {
		Ogre::Vector3 direction(0,0,-1);
		_ball->applyImpulse(direction,deltaT);
	}

	if (KEY_LEFT) {
		Ogre::Vector3 direction(1,0,0);
		_ball->applyImpulse(direction,deltaT);
	}

	if (KEY_RIGHT) {
		Ogre::Vector3 direction(-1,0,0);
		_ball->applyImpulse(direction,deltaT);
	}

	if (_currentLevel->isEndOfLive(_ball->getSceneNode())){
		dead();
		return true;
	}

	// Se consulta si ha terminado el tiempo

	if (_hud->getCurrentTime() <= 0){
		dead();
		return true;
	}

	// Se le consulta al nivel actual si se ha compleatdo con éxito
	if (_currentLevel->isLevelCompleted(_ball->getSceneNode())){
		levelCompleted();
		return true;
	}



	// Se actualiza la camara en función de la posición de la bola
	_camera->updateCamera(_ball->getPosition());



	// Se actualiza el hud
	_hud->update(deltaT,fps);

	return true;

}

bool
PlayState::frameEnded
(const Ogre::FrameEvent& evt)
{

	Ogre::Real deltaT = evt.timeSinceLastFrame;


	_physicWorld->stepSimulation(deltaT);


	if (_exitGame)
		return false;

	return true;
}

void
PlayState::keyPressed
(const OIS::KeyEvent &e)
{

	// Tecla p --> PauseState.
	if (e.key == OIS::KC_P) {
		//pushState(PauseState::getSingletonPtr());
	}

	if (e.key == OIS::KC_1) {
		_physicWorld->showDebugShapes(true);
	}

	if (e.key == OIS::KC_2) {
		_physicWorld->showDebugShapes(false);
	}

	if (e.key == OIS::KC_UP) {
		KEY_UP = true;
	}

	if (e.key == OIS::KC_DOWN) {
		KEY_DOWN = true;
	}

	if (e.key == OIS::KC_LEFT) {
		KEY_LEFT = true;
	}

	if (e.key == OIS::KC_RIGHT) {
		KEY_RIGHT = true;
	}



}

void
PlayState::keyReleased
(const OIS::KeyEvent &e)
{
	if (e.key == OIS::KC_ESCAPE) {
		_exitGame = true;
	}

	if (e.key == OIS::KC_UP) {
		KEY_UP = false;
	}

	if (e.key == OIS::KC_DOWN) {
		KEY_DOWN = false;
	}

	if (e.key == OIS::KC_LEFT) {
		KEY_LEFT = false;
	}

	if (e.key == OIS::KC_RIGHT) {
		KEY_RIGHT = false;
	}
}

void
PlayState::mouseMoved
(const OIS::MouseEvent &e)
{
}

void
PlayState::mousePressed
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

void
PlayState::mouseReleased
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

PlayState*
PlayState::getSingletonPtr ()
{
	return msSingleton;
}

PlayState&
PlayState::getSingleton ()
{ 
	assert(msSingleton);
	return *msSingleton;
}

string
PlayState::getName (){
	return "PlayState";
}

void
PlayState::createScene(){

	// En función del nivel se crea la bola y el terreno
	if (_currentLevelNumber == 1) {

		// Se instancia el nivel correspondiente
		_currentLevel = new LevelOne("Level1.mesh","Level1");
	} else if (_currentLevelNumber == 2) {

		// Se instancia el nivel correspondiente
		_currentLevel = new LevelTwo("Level1.mesh","Level1");
	}

	// Se instancia la bola
	_ball = new Ball("Sphere.mesh","Ball",_currentLevel->getInitPositionBall());
	_hud->setLevel(_currentLevelNumber);
	_hud->resetTime(_currentLevel->getTimeToComplete());
}

void
PlayState::initializeParamsConf(){

}

void
PlayState::printConf(){

}



void
PlayState::startGame(){


	// Se inicializa el hud
	_hud = new Hud();

	// Se inicializa el mundo fisico
	_physicWorld = new PhysicWorld();
	_physicWorld->initializeWorld(_sceneMgr);

	// Se inicializa la escena
	createScene();

}

void
PlayState::dead(){
	// Se comprueba si era la última vida
	bool ultimaVida = _hud->decreaseLive();

	if (ultimaVida){
		changeState(GameOverState::getSingletonPtr());
	} else {
		pushState(DeadState::getSingletonPtr());
	}
}

void
PlayState::levelCompleted(){
	LevelCompletedState::getSingletonPtr()->setLevelComplete(_currentLevelNumber);
	LevelCompletedState::getSingletonPtr()->setTime(_hud->getElapsedTime());
	changeState(LevelCompletedState::getSingletonPtr());

}
