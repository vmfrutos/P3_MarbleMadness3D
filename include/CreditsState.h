#ifndef CreditsState_H
#define CreditsState_H

#include <Ogre.h>
#include <OIS/OIS.h>

#include "GameState.h"
#include "RecordsManager.h"
#include "Record.h"

class CreditsState : public Ogre::Singleton<CreditsState>, public GameState
{
public:
	CreditsState();
	virtual ~CreditsState();

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
	static CreditsState& getSingleton ();
	static CreditsState* getSingletonPtr ();

protected:

	CEGUI::Window* _window;
	bool _exitGame;

private:
	void initialize();
	void finalize();
	bool clickBack(const CEGUI::EventArgs &e);

	bool mouseOutButton(const CEGUI::EventArgs &e);
	bool mouseInButton(const CEGUI::EventArgs &e);
};

#endif
