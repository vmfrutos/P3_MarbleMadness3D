#ifndef GameSound_H
#define GameSound_H

#include "Ogre.h"
#include "SoundFXManager.h"
#include "GameManager.h"
#include <SDL/SDL_mixer.h>
#include <SDL/SDL.h>

using namespace std;

class GameSound : public Ogre::Singleton<GameSound> {
public:

	GameSound();
	~GameSound();

	// Heredados de Ogre::Singleton.
	static GameSound& getSingleton ();
	static GameSound* getSingletonPtr ();
	void playSoundFX(int fx);
	TrackPtr loadTrack(const string& fileTrack);

	static const int FX_NEW_LEVEL = 1;
	static const int FX_DEAD = 2;
	static const int FX_GAME_OVER = 3;

	void initialize();

private:

	// Sonido
	TrackManager*  _pTrackManager;
	SoundFXManager*  _pSoundFXManager;




	SoundFXPtr _audioNewLevel;
	SoundFXPtr _audioDead;
	SoundFXPtr _audioGameOver;




};
#endif
