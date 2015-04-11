#include "RecordsState.h"


template<> RecordsState* Ogre::Singleton<RecordsState>::msSingleton = 0;

RecordsState::RecordsState(){
	_window = 0;
	_exitGame = false;

}

RecordsState::~RecordsState(){

}

void
RecordsState::enter ()
{
	initialize();
	CEGUI::MouseCursor::getSingleton().show();
	cargarRecords();
	_window->show();
}

void
RecordsState::exit()
{
	CEGUI::MouseCursor::getSingleton().hide();
	_window->hide();
	finalize();
}

void
RecordsState::pause ()
{

}

void
RecordsState::resume ()
{
}

bool
RecordsState::frameStarted
(const Ogre::FrameEvent& evt) 
{
	return true;
}

bool
RecordsState::frameEnded
(const Ogre::FrameEvent& evt)
{
	if (_exitGame){
		return false;
	}
	return true;
}

void
RecordsState::keyPressed
(const OIS::KeyEvent &e)
{
	CEGUI::System::getSingleton().injectKeyDown(e.key);
	CEGUI::System::getSingleton().injectChar(e.text);
	if (e.key == OIS::KC_ESCAPE) {
		_exitGame = true;
	}
}

void
RecordsState::keyReleased
(const OIS::KeyEvent &e )
{
	CEGUI::System::getSingleton().injectKeyUp(e.key);
}

void
RecordsState::mouseMoved
(const OIS::MouseEvent &evt)
{
	CEGUI::System::getSingleton().injectMouseMove(evt.state.X.rel, evt.state.Y.rel);
}

void
RecordsState::mousePressed
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	CEGUI::System::getSingleton().injectMouseButtonDown(CeguiManager::convertMouseButton(id));
}

void
RecordsState::mouseReleased
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	CEGUI::System::getSingleton().injectMouseButtonUp(CeguiManager::convertMouseButton(id));
}

RecordsState*
RecordsState::getSingletonPtr ()
{
	return msSingleton;
}

RecordsState&
RecordsState::getSingleton ()
{ 
	assert(msSingleton);
	return *msSingleton;
}

string RecordsState::getName (){
	return "RecordsState";

}

void RecordsState::finalize(){
	if (_window) {
		_window->destroy();
		_window = 0;
	}
}
void RecordsState::initialize(){

	CEGUI::Window* _sheet = CeguiManager::getSheet();

	//Se crea el layout
	_window  = CEGUI::WindowManager::getSingleton().loadWindowLayout("records.layout");

	CEGUI::ImagesetManager::getSingleton().createFromImageFile("RecordsBackGroud", "recordsBackGround.png");

	// Se estable la imagen
	_window->getChild("RecordScreen/Fondo")->setProperty("Image", "set:RecordsBackGroud image:full_image");


	_window->getChild("RecordScreen/Fondo")->getChild("RecordsBackButton")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&RecordsState::clickBack,this));
	_window->getChild("RecordScreen/Fondo")->getChild("RecordsBackButton")->subscribeEvent(CEGUI::PushButton::EventMouseLeavesArea,CEGUI::Event::Subscriber(&RecordsState::mouseOutButton,this));
	_window->getChild("RecordScreen/Fondo")->getChild("RecordsBackButton")->subscribeEvent(CEGUI::PushButton::EventMouseEntersArea,CEGUI::Event::Subscriber(&RecordsState::mouseInButton,this));

	_sheet->addChildWindow(_window);


}

bool
RecordsState::clickBack(const CEGUI::EventArgs &e){

	popState();
	return true;
}


bool
RecordsState::mouseInButton(const CEGUI::EventArgs &e){

	const CEGUI::MouseEventArgs& we = static_cast<const CEGUI::MouseEventArgs&>(e);
	CEGUI::String senderID = we.window->getName();

	_window->getChild("RecordScreen/Fondo")->getChild(senderID)->setAlpha(1.0);
	return true;
}

/**
 * Metodo que se ejecuta cuando el raton se quita de encima de un botón
 */
bool
RecordsState::mouseOutButton(const CEGUI::EventArgs &e){

	const CEGUI::MouseEventArgs& we = static_cast<const CEGUI::MouseEventArgs&>(e);
	CEGUI::String senderID = we.window->getName();

	_window->getChild("RecordScreen/Fondo")->getChild(senderID)->setAlpha(0.4);
	return true;
}

void
RecordsState::cargarRecords(){
	// Se le pide la lista de records al RecordsManager
	std::vector<Record> list = RecordsManager::getSingletonPtr()->getRecords();

	int numItems = list.size();
	if (numItems > 5) {
		// Si hay mas de 5 se cogen los 5 primeros (La lista esta ordenada
		numItems = 5;
	}

	for (int i=0; i<numItems;i++){
		_window->getChild("RecordScreen/Fondo")->getChild("Nombre" + Ogre::StringConverter::toString(i+1))->setText(list[i].getNickName());
		_window->getChild("RecordScreen/Fondo")->getChild("Nivel" + Ogre::StringConverter::toString(i+1))->setText(Ogre::StringConverter::toString(list[i].getLevel()));
		_window->getChild("RecordScreen/Fondo")->getChild("Tiempo" + Ogre::StringConverter::toString(i+1))->setText(list[i].getTimeStr());
	}


}
