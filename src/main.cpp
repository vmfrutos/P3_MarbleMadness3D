#define UNUSED_VARIABLE(x) (void)x

#include "GameManager.h"

#include "PlayState.h"
#include "SelectLevelState.h"
#include "DeadState.h"
#include "GameOverState.h"
#include "LevelCompletedState.h"
#include "SetRecordState.h"
#include "IntroState.h"
#include "PauseState.h"
#include "RecordsState.h"
#include "RecordsManager.h"
#include "CreditsState.h"



#include <iostream>

using namespace std;

int main () {

	// Se inicializa la clase Properties que tiene los parámetros de configuración
	new Properties;
#ifdef LINUX
	if (!Properties::getSingletonPtr()->load("conf/config.properties")) {
		return false;
	}
#endif
#ifdef WIN32
	if (!Properties::getSingletonPtr()->load("conf\\config.properties")) {
		return false;
	}
#endif

	RecordsManager* recordsManager = new RecordsManager();
	GameManager* game = new GameManager();

	PlayState* playState = new PlayState();
	SelectLevelState* selectLevelState = new SelectLevelState();
	DeadState* deadState = new DeadState();
	GameOverState* gameOverState = new GameOverState();
	LevelCompletedState* levelCompletedState = new LevelCompletedState();
	SetRecordState* setRecordState = new SetRecordState();
	IntroState* introState = new IntroState();
	PauseState* pauseState = new PauseState();
	RecordsState* recordsState = new RecordsState();
	CreditsState* creditsState = new CreditsState();

	UNUSED_VARIABLE(playState);
	UNUSED_VARIABLE(selectLevelState);
	UNUSED_VARIABLE(deadState);
	UNUSED_VARIABLE(gameOverState);
	UNUSED_VARIABLE(levelCompletedState);
	UNUSED_VARIABLE(setRecordState);
	UNUSED_VARIABLE(introState);
	UNUSED_VARIABLE(pauseState);
	UNUSED_VARIABLE(recordsState);
	UNUSED_VARIABLE(creditsState);

	try
	{
		// Inicializa el juego y transición al primer estado.
		game->start(IntroState::getSingletonPtr());

	}
	catch (Ogre::Exception& e)
	{
		std::cerr << "Excepción detectada: " << e.getFullDescription();
	}

	if (game)
		delete game;
	if (recordsManager)
		delete recordsManager;
	return 0;
}
