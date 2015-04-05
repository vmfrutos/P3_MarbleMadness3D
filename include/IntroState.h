#ifndef IntroState_H
#define IntroState_H

#include <Ogre.h>
#include <OIS/OIS.h>

#include "GameState.h"

class IntroState : public Ogre::Singleton<IntroState>, public GameState
{
public:
	IntroState();
	virtual ~IntroState();

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
	static IntroState& getSingleton ();
	static IntroState* getSingletonPtr ();

protected:
	Ogre::Root* _root;
	Ogre::SceneManager* _sceneMgr;
	Ogre::Viewport* _viewport;
	Ogre::Camera* _camera;

	bool _exitGame;
	CEGUI::Window* _window;
	bool _initialized;

private:
	void initialize();
	bool clickPlay(const CEGUI::EventArgs &e);
	bool clickRecords(const CEGUI::EventArgs &e);
	bool clickCredits(const CEGUI::EventArgs &e);
	bool clickExit(const CEGUI::EventArgs &e);
};

#endif
