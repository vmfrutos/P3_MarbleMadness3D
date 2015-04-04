#include "SetRecordState.h"

template<> SetRecordState* Ogre::Singleton<SetRecordState>::msSingleton = 0;
SetRecordState::SetRecordState(){

	_initialiced = false;
	_window = 0;
	_exit = false;

}
SetRecordState::~SetRecordState(){
	if (_window) {
		_window->destroy();
		_window = 0;

	}
}

void
SetRecordState::enter ()
{
	if (!_initialiced) {
		initialize();
		_initialiced = true;
	}
	_exit = false;
	cout << "Se va a establecer el texto" << endl;
	setText("Set your Nickname.");
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
	_window->show();
	CEGUI::MouseCursor::getSingleton().show();

}

void SetRecordState::hide(){
	_window->hide();
	//CEGUI::MouseCursor::getSingleton().hide();
}

void SetRecordState::setText(const std::string& text){

	_window->getChild("InputTextWindow/Fondo")->getChild("Text")->setText(text);

}


bool
SetRecordState::clickButton(const CEGUI::EventArgs &e){

	_exit = true;
	return true;
}




