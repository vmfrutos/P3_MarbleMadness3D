#include "IntroState.h"
#include "PlayState.h"

template<> IntroState* Ogre::Singleton<IntroState>::msSingleton = 0;

IntroState::IntroState(){
	_exitGame = false;
	_window = 0;
	_initialized = false;

	_root = 0;
	_sceneMgr = 0;
	_viewport = 0;
	_camera = 0;
}

IntroState::~IntroState(){
	if (_window) {
		_window->destroy();
	}
}

void
IntroState::enter ()
{

	_root = Ogre::Root::getSingletonPtr();

	_sceneMgr = _root->createSceneManager(Ogre::ST_GENERIC, "SceneManager");
	_camera = _sceneMgr->createCamera("IntroCamera");
	_viewport = _root->getAutoCreatedWindow()->addViewport(_camera);
	_viewport->setBackgroundColour(Ogre::ColourValue(1.0, 1.0, 1.0));

	_exitGame = false;

	if (!_initialized) {
		initialize();
		_initialized = true;
	}

	CEGUI::MouseCursor::getSingleton().show();

	_window->show();
}

void
IntroState::exit()
{
	CEGUI::MouseCursor::getSingleton().hide();
	_window->hide();

	// Se vacia el scene manager
	_sceneMgr->clearScene();


	if (_root) {
		if (_sceneMgr) {
			_root->destroySceneManager(_sceneMgr);
		}
		_root->getAutoCreatedWindow()->removeAllViewports();
	}

}

void
IntroState::pause ()
{
}

void
IntroState::resume ()
{
}

bool
IntroState::frameStarted
(const Ogre::FrameEvent& evt) 
{
	return true;
}

bool
IntroState::frameEnded
(const Ogre::FrameEvent& evt)
{
	if (_exitGame)
		return false;

	return true;
}

void
IntroState::keyPressed
(const OIS::KeyEvent &e)
{
	CEGUI::System::getSingleton().injectKeyDown(e.key);
	CEGUI::System::getSingleton().injectChar(e.text);
}

void
IntroState::keyReleased
(const OIS::KeyEvent &e )
{
	CEGUI::System::getSingleton().injectKeyUp(e.key);
	if (e.key == OIS::KC_ESCAPE) {
		_exitGame = true;
	}
}

void
IntroState::mouseMoved
(const OIS::MouseEvent &evt)
{
	CEGUI::System::getSingleton().injectMouseMove(evt.state.X.rel, evt.state.Y.rel);
}

void
IntroState::mousePressed
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	CEGUI::System::getSingleton().injectMouseButtonDown(CeguiManager::convertMouseButton(id));
}

void
IntroState::mouseReleased
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	CEGUI::System::getSingleton().injectMouseButtonUp(CeguiManager::convertMouseButton(id));
}

IntroState*
IntroState::getSingletonPtr ()
{
	return msSingleton;
}

IntroState&
IntroState::getSingleton ()
{ 
	assert(msSingleton);
	return *msSingleton;
}

string IntroState::getName (){
	return "IntroState";

}

void IntroState::initialize(){

	CEGUI::Window* _sheet = CeguiManager::getSheet();

	//Se crea el layout
	_window  = CEGUI::WindowManager::getSingleton().loadWindowLayout("intro.layout");

	_window->getChild("Play")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&IntroState::clickPlay,this));
	_window->getChild("Records")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&IntroState::clickRecords,this));
	_window->getChild("Credits")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&IntroState::clickCredits,this));
	_window->getChild("Exit")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&IntroState::clickExit,this));
	_sheet->addChildWindow(_window);


}

bool
IntroState::clickPlay(const CEGUI::EventArgs &e){

	// Se establece el numero de vidas inicial
	PlayState::getSingletonPtr()->setNumLives(3);

	// Se establece el nivel inicial
	SelectLevelState::getSingletonPtr()->setLevel(1);
	changeState(SelectLevelState::getSingletonPtr());
	return true;
}

bool
IntroState::clickRecords(const CEGUI::EventArgs &e){
	return true;
}

bool
IntroState::clickCredits(const CEGUI::EventArgs &e){
	return true;
}

bool
IntroState::clickExit(const CEGUI::EventArgs &e){
	_exitGame = true;
	return true;
}
