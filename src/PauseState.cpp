#include "PauseState.h"

template<> PauseState* Ogre::Singleton<PauseState>::msSingleton = 0;

PauseState::PauseState(){
	_modalWindow= 0;
}
PauseState::~PauseState(){

}


void
PauseState::enter (){
	_modalWindow = new Modalwindow("modalWindow.layout");
	_modalWindow->setText("Paused\nPress any key to continue.");
	_modalWindow->show();
}

void
PauseState::exit ()
{
	_modalWindow->hide();
	delete _modalWindow;
	_modalWindow = 0;
}

void
PauseState::pause ()
{
}

void
PauseState::resume ()
{
}

bool
PauseState::frameStarted
(const Ogre::FrameEvent& evt)
{
	return true;
}

bool
PauseState::frameEnded
(const Ogre::FrameEvent& evt)
{
	return true;
}

void
PauseState::keyPressed
(const OIS::KeyEvent &e) {
		popState();
}

void
PauseState::keyReleased
(const OIS::KeyEvent &e)
{
}

void
PauseState::mouseMoved
(const OIS::MouseEvent &e)
{
}

void
PauseState::mousePressed
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

void
PauseState::mouseReleased
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

PauseState*
PauseState::getSingletonPtr ()
{
	return msSingleton;
}

PauseState&
PauseState::getSingleton ()
{ 
	assert(msSingleton);
	return *msSingleton;
}

string
PauseState::getName (){
	return "PauseState";
}
