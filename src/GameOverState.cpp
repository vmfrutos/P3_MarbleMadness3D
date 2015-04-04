#include "GameOverState.h"

template<> GameOverState* Ogre::Singleton<GameOverState>::msSingleton = 0;

GameOverState::GameOverState(){
	_modalWindow = 0;
	_setRecord = false;
	_salir = false;
}
GameOverState::~GameOverState(){

}

void
GameOverState::enter ()
{
	_salir = false;

	_modalWindow = new Modalwindow;
	_modalWindow->setText("Game Over.\nPress any key.");
	_modalWindow->show();

	// Se consulta a LevelCompletedState para saber si se ha completado algún nivel y hay que establecer record
	//TODO:

	_setRecord = false;
}

void
GameOverState::exit ()
{
	_modalWindow->hide();
	delete _modalWindow;
	_modalWindow = 0;
}

void
GameOverState::pause ()
{
}

void
GameOverState::resume ()
{
}

bool
GameOverState::frameStarted
(const Ogre::FrameEvent& evt)
{
	if (_salir) {
		return false;
	}
	return true;
}

bool
GameOverState::frameEnded
(const Ogre::FrameEvent& evt)
{
	return true;
}

void
GameOverState::keyPressed
(const OIS::KeyEvent &e) {

	if (_setRecord) {
		_salir = true;
	} else {
		_salir = true;
	}

}

void
GameOverState::keyReleased
(const OIS::KeyEvent &e)
{
}

void
GameOverState::mouseMoved
(const OIS::MouseEvent &e)
{
}

void
GameOverState::mousePressed
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

void
GameOverState::mouseReleased
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

GameOverState*
GameOverState::getSingletonPtr ()
{
	return msSingleton;
}

GameOverState&
GameOverState::getSingleton ()
{ 
	assert(msSingleton);
	return *msSingleton;
}

string
GameOverState::getName (){
	return "GameOverState";
}
