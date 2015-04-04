#include "Hud.h"

Hud::Hud(){
	_numLives = 3;
	_hud = 0;

	initialize();

	_startAlertTime = Properties::getSingletonPtr()->getPropertyInt("game.startAlertTime");
}
Hud::~Hud(){

	cout << "PlayState::~Hud() 01" << endl;

	if (_timeText) {
		//CeguiManager::getSheet()->removeChildWindow(_timeText);
		cout << "PlayState::~Hud() 02" << endl;
		_timeText->destroy();
		cout << "PlayState::~Hud() 03" << endl;
		_timeText = NULL;
		cout << "PlayState::~Hud() 04" << endl;
	}
	if (_fpsText) {
		//CeguiManager::getSheet()->removeChildWindow(_fpsText);
		cout << "PlayState::~Hud() 05" << endl;
		_fpsText->destroy();
		cout << "PlayState::~Hud() 06" << endl;
		_fpsText = NULL;
		cout << "PlayState::~Hud() 07" << endl;
	}
	if (_hud) {
		//CeguiManager::getSheet()->removeChildWindow(_hud);
		cout << "PlayState::~Hud() 08" << endl;
		_hud->destroy();
		cout << "PlayState::~Hud() 09" << endl;
		_hud = NULL;
		cout << "PlayState::~Hud() 10" << endl;
	}
}

void Hud::initialize(){

	CEGUI::Window* _sheet = CeguiManager::getSheet();

	//_sheet = CEGUI::WindowManager::getSingletonPtr()->createWindow("DefaultWindow","SheetHud");
	//CEGUI::System::getSingleton().setGUISheet(_sheet);

	// Se crea el layout
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

	_timeText =_hud->getChild("Hud/Fondo")->getChild("TimeBox")->getChild("TimeText");
	_fpsText =_hud->getChild("Hud/Fondo")->getChild("FpsBox")->getChild("FpsText");

}

void Hud::update(float delta, float fps){
	_contador.decrementar(delta);
	int currentSecond = (int)_contador.getSegundosTranscurridos();

	// Se establece a verde el color del contador
	_timeText->setProperty("TextColours","FF00FF00");
	if (currentSecond <= _startAlertTime){
		// si es impar se pone rojo el color del contador
		if (currentSecond % 2 != 0) {
			_timeText->setProperty("TextColours","FFFF0000");
		}

		// Sonido de alarma
	}
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

void
Hud::addInfo(const string& info){
	const CEGUI::String currentInfo = _hud->getChild("Hud/Fondo")->getChild("InfoBox")->getChild("InfoText")->getText();
	_hud->getChild("Hud/Fondo")->getChild("InfoBox")->getChild("InfoText")->setText(currentInfo + "\n" + info);
}

int
Hud::getNumLives(){
	return _numLives;
}

void Hud::resetTime(float time){
	_contador.reset(time);
	_timeText->setText(_contador.getContadorMinSecStr());
}

float Hud::getCurrentTime(){
	return _contador.getSegundosTranscurridos();
}

int
Hud::getElapsedTime(){
	return _contador.getValorInicial() - (int) _contador.getSegundosTranscurridos();
}

