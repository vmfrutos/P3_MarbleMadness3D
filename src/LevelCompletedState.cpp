#include "LevelCompletedState.h"

template<> LevelCompletedState* Ogre::Singleton<LevelCompletedState>::msSingleton = 0;

LevelCompletedState::LevelCompletedState(){
	_levelCompleted = 0;
	_time = 0;
	_modalWindow = 0;
}
LevelCompletedState::~LevelCompletedState(){

}

void
LevelCompletedState::enter ()
{
	_modalWindow = new Modalwindow("modalWindow.layout");
	_modalWindow->setText("Completed level " + Ogre::StringConverter::toString(_levelCompleted) + "\n" + Ogre::StringConverter::toString(_time) + " seconds\nPress any key");
	_modalWindow->show();
}

void
LevelCompletedState::exit ()
{
	_modalWindow->hide();
	delete _modalWindow;
	_modalWindow = 0;
}

void
LevelCompletedState::pause ()
{
}

void
LevelCompletedState::resume ()
{
}

bool
LevelCompletedState::frameStarted
(const Ogre::FrameEvent& evt)
{

	return true;
}

bool
LevelCompletedState::frameEnded
(const Ogre::FrameEvent& evt)
{
	return true;
}

void
LevelCompletedState::keyPressed
(const OIS::KeyEvent &e) {

	goToSelectLevelState();

}

void
LevelCompletedState::keyReleased
(const OIS::KeyEvent &e)
{
}

void
LevelCompletedState::mouseMoved
(const OIS::MouseEvent &e)
{
}

void
LevelCompletedState::mousePressed
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

void
LevelCompletedState::mouseReleased
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

LevelCompletedState*
LevelCompletedState::getSingletonPtr ()
{
	return msSingleton;
}

LevelCompletedState&
LevelCompletedState::getSingleton ()
{ 
	assert(msSingleton);
	return *msSingleton;
}

string
LevelCompletedState::getName (){
	return "LevelCompletedState";
}

void
LevelCompletedState::goToSelectLevelState(){
	_levelCompleted++;
	SelectLevelState::getSingletonPtr()->setLevel(_levelCompleted);
	changeState(SelectLevelState::getSingletonPtr());

}
