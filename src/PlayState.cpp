#include "PlayState.h"
#include "PauseState.h"

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
	_state = STATE_PLAYING;
	_currentLevelNumber = 1;

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


	// Se inicializa el hud
	_hud = new Hud();

	// Se inicializan los valores de configuracion
	initializeParamsConf();

	// Se imprimen los parametro sconfigurables
	printConf();

	// Se inicializa el mundo fisico
	PhysicWorld::initializeWorld(_sceneMgr);

	// Se inicializa la escena
	createScene();

}

void
PlayState::exit ()
{
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
	PhysicWorld::stepSimulation(deltaT);
	float fps;


	if (deltaT == 0.0) {
		fps = 1000; // esto es por evitar división por 0 en equipos muy rápidos
	} else {
		fps = 1.0f / deltaT;
	}

	if (_state == STATE_PLAYING) {

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

		// Se le consulta al nivel actual si se ha producido algun evento que mate a la bola
		if (_currentLevel->isEndOfLive(_ball->getSceneNode()))
			_state = STATE_END;

		// Se consulta si ha terminado el tiempo
		cout << "Segundos restantes: " <<_hud->getCurrentTime() << endl;
		if (_hud->getCurrentTime() <= 0){
			_state = STATE_END;
		}


		// Se actualiza la camara en función de la posición de la bola
		_camera->updateCamera(_ball->getPosition());

		// Se actualiza el hud
		_hud->update(deltaT,fps);

	} else if (_state == STATE_END) {
		gameEnd();
	}

	return true;
}

bool
PlayState::frameEnded
(const Ogre::FrameEvent& evt)
{
	Ogre::Real deltaT = evt.timeSinceLastFrame;
	PhysicWorld::stepSimulation(deltaT);

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
		pushState(PauseState::getSingletonPtr());
	}

	if (e.key == OIS::KC_1) {
		PhysicWorld::showDebugShapes(true);
	}

	if (e.key == OIS::KC_2) {
		PhysicWorld::showDebugShapes(false);
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

	if (e.key == OIS::KC_A) {
		_hud->decreaseLive();
	}

	if (e.key == OIS::KC_S) {
		_hud->setInfo("Mensaje de prueba largo, aqui se puede poner todo esto y mucho mas");
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

void
PlayState::createScene(){

	// En función del nivel se crea la bola y el terreno
	if (_currentLevelNumber == 1) {

		// Se instancia el nivel correspondiente
		_currentLevel = new LevelOne("Level1.mesh","Level1");
	}

	// Se instancia la bola
	_ball = new Ball("Sphere.mesh","Ball",_currentLevel->getInitPositionBall());
	_hud->setLevel(_currentLevelNumber);
	_hud->resetTime(_currentLevel->getTimeToComplete());
}

void
PlayState::initializeParamsConf(){
	_currentLevelNumber = Properties::getSingletonPtr()->getPropertyInt("game.startLevel");
}

void
PlayState::printConf(){
	Ogre::LogManager::getSingletonPtr()->logMessage("************ PlayState ***************");
	Ogre::LogManager::getSingletonPtr()->logMessage("game.startLevel: " + StringConverter::toString(_currentLevelNumber));
	Ogre::LogManager::getSingletonPtr()->logMessage("***************************************");
}

void
PlayState::gameEnd(){

	// Se decrementa una vida. Si la vida es la ultima (endGame == true)
	bool endGame = _hud->decreaseLive();
	if (endGame){
		// Se han acabado las vidas

	} else {
		reset();
		_state = STATE_PLAYING;
	}

}

void
PlayState::reset(){
	_ball->resetBall(_currentLevel->getInitPositionBall());
	_camera->updateCamera(_ball->getPosition());
	_hud->setLevel(_currentLevelNumber);
	_hud->resetTime(_currentLevel->getTimeToComplete());

}
