#include "Hud.h"

Hud::Hud(float time):_contador(time){
	_numLives = 3;
	_sheet = 0;
	_hud = 0;

	initialize();
}
Hud::~Hud(){
	if (_hud) _hud->destroy();
	if (_sheet) _sheet->destroy();
}

void Hud::initialize(){
	// Se inicializa el layout de CEGUI
	//Sheet
	_sheet = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow","Sheet");

	//Config Window
	_hud  = CEGUI::WindowManager::getSingleton().loadWindowLayout("hud.layout");


	// Se crean los ImageSet
	CEGUI::ImagesetManager::getSingleton().createFromImageFile("ImageBackGroud", "fondoHud.png");
	CEGUI::ImagesetManager::getSingleton().createFromImageFile("ImageLive", "Live.png");
	CEGUI::ImagesetManager::getSingleton().createFromImageFile("ImageTimeBox", "TimeBox.png");
	CEGUI::ImagesetManager::getSingleton().createFromImageFile("ImageLevelBox", "LevelBox.png");
	CEGUI::ImagesetManager::getSingleton().createFromImageFile("ImageFpsBox", "FpsBox.png");
	CEGUI::ImagesetManager::getSingleton().createFromImageFile("ImageInfoBox", "InfoBox.png");


	// Se establecen imagenes a los widgets
	_hud->getChild("Hud/Fondo")->setProperty("Image", "set:ImageBackGroud image:full_image");
	_hud->getChild("Hud/Fondo")->getChild("Live1")->setProperty("Image", "set:ImageLive image:full_image");
	_hud->getChild("Hud/Fondo")->getChild("Live2")->setProperty("Image", "set:ImageLive image:full_image");
	_hud->getChild("Hud/Fondo")->getChild("Live3")->setProperty("Image", "set:ImageLive image:full_image");
	_hud->getChild("Hud/Fondo")->getChild("TimeBox")->setProperty("Image", "set:ImageTimeBox image:full_image");
	_hud->getChild("Hud/Fondo")->getChild("LevelBox")->setProperty("Image", "set:ImageLevelBox image:full_image");
	_hud->getChild("Hud/Fondo")->getChild("FpsBox")->setProperty("Image", "set:ImageFpsBox image:full_image");
	_hud->getChild("Hud/Fondo")->getChild("InfoBox")->setProperty("Image", "set:ImageInfoBox image:full_image");


	_sheet->addChildWindow(_hud);
	CEGUI::System::getSingleton().setGUISheet(_sheet);



	CEGUI::MouseCursor::getSingleton().hide();

	_timeText =_hud->getChild("Hud/Fondo")->getChild("TimeBox")->getChild("TimeText");
	_fpsText =_hud->getChild("Hud/Fondo")->getChild("FpsBox")->getChild("FpsText");

}

void Hud::update(float delta, float fps){
	_contador.decrementar(delta);
	_timeText->setText(_contador.getContadorMinSecStr());
	_fpsText->setText(Ogre::StringConverter::toString(fps));
}

/**
 * Si la se acaban las vidas retorna true
 */
bool Hud::decreaseLive(){
	if (_numLives == 3) {
		_hud->getChild("Hud/Fondo")->getChild("Live3")->hide();
		_numLives--;
		return false;
	} else if (_numLives == 2){
		_hud->getChild("Hud/Fondo")->getChild("Live2")->hide();
		_numLives--;
		return false;
	} else if (_numLives == 1){
		_hud->getChild("Hud/Fondo")->getChild("Live1")->hide();
		_numLives--;
		return true;
	}

	return true;
}

void
Hud::setLevel(int level){
	_hud->getChild("Hud/Fondo")->getChild("LevelBox")->getChild("LevelText")->setText(Ogre::StringConverter::toString(level));
}

void
Hud::setInfo(const string& info){
	_hud->getChild("Hud/Fondo")->getChild("InfoBox")->getChild("InfoText")->setText(info);
}

int
Hud::getNumLives(){
	return _numLives;
}
