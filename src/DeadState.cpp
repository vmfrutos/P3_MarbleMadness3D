#include "DeadState.h"

template<> DeadState* Ogre::Singleton<DeadState>::msSingleton = 0;

DeadState::DeadState(){
	_modalWindow = 0;

}
DeadState::~DeadState(){

}

void
DeadState::enter ()
{
	_modalWindow = new Modalwindow("modalWindow.layout");
	_modalWindow->setText("Try again.\nPress any key to continue.");
	GameSound::getSingletonPtr()->playSoundFX(GameSound::FX_DEAD);
	_modalWindow->show();

}

void
DeadState::exit ()
{
	_modalWindow->hide();
	delete _modalWindow;
	_modalWindow = 0;
}

void
DeadState::pause ()
{
}

void
DeadState::resume ()
{
}

bool
DeadState::frameStarted
(const Ogre::FrameEvent& evt)
{
	return true;
}

bool
DeadState::frameEnded
(const Ogre::FrameEvent& evt)
{

	return true;
}

void
DeadState::keyPressed
(const OIS::KeyEvent &e) {

	// Si se pulsa cualquier tecla se resetea la bola  vuelve al estado anterior (PlayState)

	// Se posiciona la bola en el punto inicial
	Ball* _ball = PlayState::getSingletonPtr()->getBall();
	Level* _currentLevel = PlayState::getSingletonPtr()->getCurrentLevel();
	Hud* _hud = PlayState::getSingletonPtr()->getHud();

	// Se resetean la bola y el hud
	_ball->resetBall(_currentLevel->getInitPositionBall());
	_hud->resetTime(_currentLevel->getTimeToComplete());
	popState();

}

void
DeadState::keyReleased
(const OIS::KeyEvent &e)
{
}

void
DeadState::mouseMoved
(const OIS::MouseEvent &e)
{
}

void
DeadState::mousePressed
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

void
DeadState::mouseReleased
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

DeadState*
DeadState::getSingletonPtr ()
{
	return msSingleton;
}

DeadState&
DeadState::getSingleton ()
{ 
	assert(msSingleton);
	return *msSingleton;
}

string
DeadState::getName (){
	return "DeadState";
}
