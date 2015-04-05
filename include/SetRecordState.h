#ifndef __SETRECORDSTATE_H__
#define __SETRECORDSTATE_H__

#include <Ogre.h>
#include <CEGUI.h>
#include "CeguiManager.h"
#include "GameState.h"
#include "LevelCompletedState.h"
#include "RecordsManager.h"
#include "Record.h"

class SetRecordState : public Ogre::Singleton<SetRecordState>, public GameState{
public:
	SetRecordState();
	~SetRecordState();


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
	static SetRecordState& getSingleton ();
	static SetRecordState* getSingletonPtr ();


private:

	void show();
	void hide();
	void setText(const std::string& text);
	void initialize();
	bool clickButton(const CEGUI::EventArgs &e);
	void gotoToIntroState();

	CEGUI::Window* _window;
	bool _exit;
	bool _initialized;

	int _maxLevel;
	int _time;

};
#endif
