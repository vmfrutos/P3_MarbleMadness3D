#ifndef DeadState_H
#define DeadState_H

#include <Ogre.h>
#include <OIS/OIS.h>

#include "GameState.h"
#include "PlayState.h"

#include "Ball.h"
#include "Level.h"
#include "Hud.h"

class DeadState : public Ogre::Singleton<DeadState>, public GameState
{
public:
	DeadState();
	virtual ~DeadState();

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
	static DeadState& getSingleton ();
	static DeadState* getSingletonPtr ();

private:
	Modalwindow* _modalWindow;
};

#endif
