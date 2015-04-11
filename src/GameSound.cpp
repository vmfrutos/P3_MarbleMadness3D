#include "GameSound.h"

template<> GameSound* Ogre::Singleton<GameSound>::msSingleton = 0;

GameSound::GameSound() {
	_pTrackManager = 0;
	_pSoundFXManager = 0;
}
GameSound::~GameSound (){

}

void GameSound::initialize() {
	// Se inicializan los gestores de sonido (track y FX)
	_pTrackManager = new TrackManager;
	_pSoundFXManager = new SoundFXManager;

	_audioDead = _pSoundFXManager->load("dead.wav");
	_audioNewLevel = _pSoundFXManager->load("newLevel.wav");
	_audioGameOver = _pSoundFXManager->load("gameOver.wav");

}

void
GameSound::playSoundFX(int fx) {

	if (FX_NEW_LEVEL == fx) {
		cout << "sonando _audioNewLevel" << endl;
		_audioNewLevel->play(FX_NEW_LEVEL,0);

	} else if (FX_DEAD == fx) {
		cout << "sonando _audioGameOver" << endl;
		_audioDead->play(FX_DEAD,0);

	} else if (FX_GAME_OVER == fx) {
		_audioGameOver->play(FX_GAME_OVER,0);

	} /*else if (FX_BOLA_SUELO == fx) {
		int channel = _audioBallSuelo->play(FX_BOLA_SUELO,0);

		while (_audioBallSuelo->isPlaying(channel) == true) {
#ifdef WIN32
			Sleep(0.1);
#else
			sleep(0.1);
#endif
		}
	} else if (FX_PALA_ITEM == fx) {
		 channel = _audioPaddleItem->play(FX_PALA_ITEM,0);
	}
	 */
}

GameSound&
GameSound::getSingleton (){
	assert(msSingleton);
	return *msSingleton;
}

GameSound*
GameSound::getSingletonPtr (){
	return msSingleton;
}


TrackPtr
GameSound::loadTrack(const string& fileTrack){
	return _pTrackManager->getSingletonPtr()->load(fileTrack);
}


