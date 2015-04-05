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
	_modalWindow = new Modalwindow("modalWindow.layout");
	_modalWindow->setText("Game Over.\nPress any key.");
	_modalWindow->show();

	// Se consulta a LevelCompletedState para saber si se ha completado algún nivel y hay que establecer record
	int levelComplete = LevelCompletedState::getSingletonPtr()->getLevelComplete();
	if (levelComplete >0){ // No se pone record, porque no se ha completado ningún nivel
		_setRecord = true;
	} else {
		_setRecord = false;
	}
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
		gotoSetRecord();
	} else {
		gotoIntro();
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

void GameOverState::gotoSetRecord(){
	changeState(SetRecordState::getSingletonPtr());
}

void GameOverState::gotoIntro(){

	changeState(IntroState::getSingletonPtr());
}
