#ifndef PlayState_H
#define PlayState_H

#include <Ogre.h>
#include <OIS/OIS.h>

#include "GameState.h"
#include "DeadState.h"
#include "GameOverState.h"
#include "LevelCompletedState.h"
#include "PauseState.h"
#include "SetRecordState.h"
#include "LevelOne.h"
#include "LevelTwo.h"
#include "Ball.h"
#include "Camera.h"
#include "Hud.h"
#include "Enemy.h"
#include "Lanzadera.h"


class PlayState : public Ogre::Singleton<PlayState>, public GameState
{
public:
	PlayState();
	virtual ~PlayState();

	void enter ();
	void exit ();
	void pause ();
	void resume ();
	string getName ();

	void keyPressed (const OIS::KeyEvent &e);
	void keyReleased (const OIS::KeyEvent &e);

	void mouseMoved (const OIS::MouseEvent &e);
	void mousePressed (const OIS::MouseEvent &e, OIS::MouseButtonID id);
	void mouseReleased (const OIS::MouseEvent &e, OIS::MouseButtonID id);

	bool frameStarted (const Ogre::FrameEvent& evt);
	bool frameEnded (const Ogre::FrameEvent& evt);

	void setLevel(int level) {_currentLevelNumber = level;};
	Ball* getBall() {return _ball;};
	Hud* getHud() {return _hud;};
	Level* getCurrentLevel(){return _currentLevel;};
	::Camera* getCamera(){return _camera;};

	// Heredados de Ogre::Singleton.
	static PlayState& getSingleton ();
	static PlayState* getSingletonPtr ();

	void setNumLives(int numLives);

	void setCameraFarView(bool value);
	bool getCameraFarView(){return _cameraFarView;};


private:
	Ogre::Root* _root;
	Ogre::RenderWindow* _win;
	Ogre::SceneManager* _sceneMgr;
	Ogre::Viewport* _viewport;


	bool _exitGame;

	int _currentLevelNumber;
	Level* _currentLevel;
	static int _numLives;
	Ball* _ball;
	::Camera* _camera;
	Hud* _hud;
	PhysicWorld* _physicWorld;


	void createScene();
	void initializeParamsConf();
	void printConf();
	void startGame();
	void dead();
	void levelCompleted();




	// Teclas pulsadas
	bool KEY_UP;
	bool KEY_DOWN;
	bool KEY_RIGHT;
	bool KEY_LEFT;

	// Modo de vision de la camara
	bool _cameraFarView;

	bool _infitiLives;

	// Sonido
	TrackPtr _lava;

};

#endif
