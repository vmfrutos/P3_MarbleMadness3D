#include "CreditsState.h"


template<> CreditsState* Ogre::Singleton<CreditsState>::msSingleton = 0;

CreditsState::CreditsState(){
	_window = 0;
	_exitGame = false;

}

CreditsState::~CreditsState(){

}

void
CreditsState::enter ()
{
	initialize();

	CEGUI::MouseCursor::getSingleton().show();
	_window->show();
}

void
CreditsState::exit()
{
	CEGUI::MouseCursor::getSingleton().hide();
	_window->hide();
	finalize();
}

void
CreditsState::pause ()
{
}

void
CreditsState::resume ()
{

}

bool
CreditsState::frameStarted
(const Ogre::FrameEvent& evt) 
{
	return true;
}

bool
CreditsState::frameEnded
(const Ogre::FrameEvent& evt)
{
	if (_exitGame){
		return false;
	}
	return true;
}

void
CreditsState::keyPressed
(const OIS::KeyEvent &e)
{
	CEGUI::System::getSingleton().injectKeyDown(e.key);
	CEGUI::System::getSingleton().injectChar(e.text);
	if (e.key == OIS::KC_ESCAPE) {
		_exitGame = true;
	}
}

void
CreditsState::keyReleased
(const OIS::KeyEvent &e )
{
	CEGUI::System::getSingleton().injectKeyUp(e.key);
}

void
CreditsState::mouseMoved
(const OIS::MouseEvent &evt)
{
	CEGUI::System::getSingleton().injectMouseMove(evt.state.X.rel, evt.state.Y.rel);
}

void
CreditsState::mousePressed
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	CEGUI::System::getSingleton().injectMouseButtonDown(CeguiManager::convertMouseButton(id));
}

void
CreditsState::mouseReleased
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	CEGUI::System::getSingleton().injectMouseButtonUp(CeguiManager::convertMouseButton(id));
}

CreditsState*
CreditsState::getSingletonPtr ()
{
	return msSingleton;
}

CreditsState&
CreditsState::getSingleton ()
{ 
	assert(msSingleton);
	return *msSingleton;
}

string CreditsState::getName (){
	return "CreditsState";

}

void CreditsState::finalize(){
	if (_window) {
		_window->destroy();
		_window = 0;
	}
}
void CreditsState::initialize(){

	CEGUI::Window* _sheet = CeguiManager::getSheet();

	//Se crea el layout
	_window  = CEGUI::WindowManager::getSingleton().loadWindowLayout("credits.layout");

	CEGUI::ImagesetManager::getSingleton().createFromImageFile("CreditsBackGroud", "creditsBackGround.png");

	// Se estable la imagen
	_window->getChild("CreditsScreen/Fondo")->setProperty("Image", "set:CreditsBackGroud image:full_image");

	_window->getChild("CreditsScreen/Fondo")->getChild("CreditsBackButton")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&CreditsState::clickBack,this));
	_window->getChild("CreditsScreen/Fondo")->getChild("CreditsBackButton")->subscribeEvent(CEGUI::PushButton::EventMouseLeavesArea,CEGUI::Event::Subscriber(&CreditsState::mouseOutButton,this));
	_window->getChild("CreditsScreen/Fondo")->getChild("CreditsBackButton")->subscribeEvent(CEGUI::PushButton::EventMouseEntersArea,CEGUI::Event::Subscriber(&CreditsState::mouseInButton,this));

	_sheet->addChildWindow(_window);


}

bool
CreditsState::clickBack(const CEGUI::EventArgs &e){

	popState();
	return true;
}


bool
CreditsState::mouseInButton(const CEGUI::EventArgs &e){

	const CEGUI::MouseEventArgs& we = static_cast<const CEGUI::MouseEventArgs&>(e);
	CEGUI::String senderID = we.window->getName();

	_window->getChild("CreditsScreen/Fondo")->getChild(senderID)->setAlpha(1.0);
	return true;
}

/**
 * Metodo que se ejecuta cuando el raton se quita de encima de un botón
 */
bool
CreditsState::mouseOutButton(const CEGUI::EventArgs &e){

	const CEGUI::MouseEventArgs& we = static_cast<const CEGUI::MouseEventArgs&>(e);
	CEGUI::String senderID = we.window->getName();

	_window->getChild("CreditsScreen/Fondo")->getChild(senderID)->setAlpha(0.4);
	return true;
}

