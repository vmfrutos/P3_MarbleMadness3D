#include "SetRecordState.h"

template<> SetRecordState* Ogre::Singleton<SetRecordState>::msSingleton = 0;
SetRecordState::SetRecordState(){

	_maxLevel = 0;
	_time = 0;
	_initialized = false;
	_window = 0;
	_exit = false;

}
SetRecordState::~SetRecordState(){
	/*
	if (_window) {
		_window->destroy();
		_window = 0;

	}
	*/
}

void
SetRecordState::enter ()
{
	if (!_initialized) {
		initialize();
		_initialized = true;
	}


	// Se obtienen del estado LevelCompletedState el maximo nivel alcanzado y el tiempo en completarlo
	_maxLevel = LevelCompletedState::getSingletonPtr()->getLevelComplete();
	_time = LevelCompletedState::getSingletonPtr()->getTime();
	_exit = false;
	setText("Level: " + Ogre::StringConverter::toString(_maxLevel) + "\nTime to complete level: " + Ogre::StringConverter::toString(_time) + " seconds\nSet your nickname please.");
	show();
}

void
SetRecordState::exit ()
{
	hide();

}

void
SetRecordState::pause ()
{
}

void
SetRecordState::resume ()
{
}

bool
SetRecordState::frameStarted
(const Ogre::FrameEvent& evt)
{
	if (_exit)
		return false;
	return true;
}

bool
SetRecordState::frameEnded
(const Ogre::FrameEvent& evt)
{

	return true;
}

void
SetRecordState::keyPressed
(const OIS::KeyEvent &e) {
	CEGUI::System::getSingleton().injectKeyDown(e.key);
	CEGUI::System::getSingleton().injectChar(e.text);
}

void
SetRecordState::keyReleased
(const OIS::KeyEvent &e)
{
	CEGUI::System::getSingleton().injectKeyUp(e.key);
	if (e.key == OIS::KC_ESCAPE) {
		_exit = true;
	}
}

void
SetRecordState::mouseMoved
(const OIS::MouseEvent &evt)
{
	CEGUI::System::getSingleton().injectMouseMove(evt.state.X.rel, evt.state.Y.rel);
}

void
SetRecordState::mousePressed
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	CEGUI::System::getSingleton().injectMouseButtonDown(CeguiManager::convertMouseButton(id));
}

void
SetRecordState::mouseReleased
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	CEGUI::System::getSingleton().injectMouseButtonUp(CeguiManager::convertMouseButton(id));
}

SetRecordState*
SetRecordState::getSingletonPtr ()
{
	return msSingleton;
}

SetRecordState&
SetRecordState::getSingleton ()
{
	assert(msSingleton);
	return *msSingleton;
}

string
SetRecordState::getName (){
	return "SetRecordState";
}




void SetRecordState::initialize(){

	CEGUI::Window* _sheet = CeguiManager::getSheet();

	//Se crea el layout
	_window  = CEGUI::WindowManager::getSingleton().loadWindowLayout("inputTextWindow.layout");

	// Se crean los ImageSet
	CEGUI::ImagesetManager::getSingleton().createFromImageFile("ModalWindowBackGroud", "WindowBackGround.png");

	// Se establecen imagenes a los widgets
	_window->getChild("InputTextWindow/Fondo")->setProperty("Image", "set:ModalWindowBackGroud image:full_image");

	_window->getChild("InputTextWindow/Fondo")->getChild("Buton")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&SetRecordState::clickButton,this));

	_sheet->addChildWindow(_window);

	_window->hide();

}

void SetRecordState::show(){
	if (_window){
		_window->show();
		CEGUI::MouseCursor::getSingleton().show();
	}

}

void SetRecordState::hide(){
	if (_window){
		_window->hide();
		CEGUI::MouseCursor::getSingleton().hide();
	}
}

void SetRecordState::setText(const std::string& text){
	if (_window){
		_window->getChild("InputTextWindow/Fondo")->getChild("Text")->setText(text);
	}

}


bool
SetRecordState::clickButton(const CEGUI::EventArgs &e){

	string nickname = _window->getChild("InputTextWindow/Fondo")->getChild("NameEdit")->getText().c_str();

	if (nickname != "") {
		Record record;
		record.setNickname(nickname);
		record.setLevel(_maxLevel);
		record.setTime(_time);
		RecordsManager::getSingletonPtr()->addRecord(record);
	}
	gotoToIntroState();
	return true;
}

void SetRecordState::gotoToIntroState(){
	changeState(IntroState::getSingletonPtr());
}




