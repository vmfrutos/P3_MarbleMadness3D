#include "SelectLevelState.h"

template<> SelectLevelState* Ogre::Singleton<SelectLevelState>::msSingleton = 0;

SelectLevelState::SelectLevelState() {
	_modalWindow = 0;
	_numberOfLevels = 0;
	_nextLevelNumber = 0;
	_gameCompleted = false;
}
SelectLevelState::~SelectLevelState() {

}

void SelectLevelState::enter() {
	cout << "SelectLevelState::enter" << endl;
	_numberOfLevels = Properties::getSingletonPtr()->getPropertyInt(
			"game.numberOfLevels");

	_modalWindow = new Modalwindow("modalWindowFull.layout");
	_contador.reset();

	if (_nextLevelNumber > _numberOfLevels) {
		// Se han completado todos los niveles
		_gameCompleted = true;
		_modalWindow->setText("Game completed.");
	} else {
		_gameCompleted = false;
		_modalWindow->setText("Level " + Ogre::StringConverter::toString(_nextLevelNumber) + ".");
	}

	_modalWindow->show();

}

void SelectLevelState::exit() {
	_modalWindow->hide();
	delete _modalWindow;
	_modalWindow = 0;

}

void SelectLevelState::pause() {
}

void SelectLevelState::resume() {
}

bool SelectLevelState::frameStarted(const Ogre::FrameEvent& evt) {
	_contador.incrementar(evt.timeSinceLastFrame);

	if (_contador.getSegundosTranscurridos() > 1) { // Se esperan 1 segundos con la ventana y se pasa al estado PlayState
		if (!_gameCompleted) {
			gotoToPlayState();
		} else {
			gotoSetRecord();
		}

	}

	return true;
}

bool SelectLevelState::frameEnded(const Ogre::FrameEvent& evt) {

	return true;
}

void SelectLevelState::keyPressed(const OIS::KeyEvent &e) {
	gotoToPlayState();
}

void SelectLevelState::keyReleased(const OIS::KeyEvent &e) {
}

void SelectLevelState::mouseMoved(const OIS::MouseEvent &e) {
}

void SelectLevelState::mousePressed(const OIS::MouseEvent &e,
		OIS::MouseButtonID id) {
}

void SelectLevelState::mouseReleased(const OIS::MouseEvent &e,
		OIS::MouseButtonID id) {
}

SelectLevelState*
SelectLevelState::getSingletonPtr() {
	return msSingleton;
}

SelectLevelState&
SelectLevelState::getSingleton() {
	assert(msSingleton);
	return *msSingleton;
}

string SelectLevelState::getName() {
	return "SelectLevelState";
}

void SelectLevelState::gotoToPlayState() {
	PlayState::getSingletonPtr()->setLevel(_nextLevelNumber);
	changeState(PlayState::getSingletonPtr());
}

void SelectLevelState::gotoSetRecord(){
	changeState(SetRecordState::getSingletonPtr());
}
