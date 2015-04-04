#ifndef LevelCompletedState_H
#define LevelCompletedState_H

#include <Ogre.h>
#include <OIS/OIS.h>

#include "GameState.h"
#include "SelectLevelState.h"




class LevelCompletedState : public Ogre::Singleton<LevelCompletedState>, public GameState
{
public:
	LevelCompletedState();
	virtual ~LevelCompletedState();

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

	// Heredados de Ogre::Singleton.
	static LevelCompletedState& getSingleton ();
	static LevelCompletedState* getSingletonPtr ();

	int getLevelComplete(){return _levelCompleted;};
	void setLevelComplete(int levelCompleted){ _levelCompleted = levelCompleted;};

	int getTime(){return _time;};
	void setTime(float time){ _time = time;};



private:
	int _levelCompleted;
	float _time;
	Modalwindow* _modalWindow;

	void goToSelectLevelState();

};

#endif
