#include "Hud.h"

template<> int Hud::_numLives;
Hud::Hud(){
	_hud = 0;

	initialize();

	_startAlertTime = Properties::getSingletonPtr()->getPropertyInt("game.startAlertTime");
}
Hud::~Hud(){
	if (_hud) {
		_hud->hide();
		_hud->destroy();
		_hud = 0;
	}

}

void Hud::initialize(){

	CEGUI::Window* _sheet = CeguiManager::getSheet();

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
		GameSound::getSingletonPtr()->playSoundFX(GameSound::FX_ALARM);
	}

	if (currentSecond == 0){

		// Si esta sonando la alarma se quita
		if (GameSound::getSingletonPtr()->isPlayingSoundFX(GameSound::FX_ALARM)){
			GameSound::getSingletonPtr()->stopSoundFX(GameSound::FX_ALARM);
		}
	}

	_timeText->setText(_contador.getContadorMinSecStr());
	_fpsText->setText(Ogre::StringConverter::toString((int)fps));
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
Hud::setNumLives(int lives) {
	_numLives = lives;
	if (_numLives == 2){
		_hud->getChild("Hud/Fondo")->getChild("Live3")->hide();

	} else if (_numLives == 1){
		_hud->getChild("Hud/Fondo")->getChild("Live3")->hide();
		_hud->getChild("Hud/Fondo")->getChild("Live2")->hide();

	}
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

