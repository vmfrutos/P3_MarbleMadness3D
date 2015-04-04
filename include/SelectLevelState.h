#ifndef SelectLevelState_H
#define SelectLevelState_H

#include <Ogre.h>
#include <OIS/OIS.h>
#include "ModalWindow.h"
#include "GameState.h"
#include "PlayState.h"
#include "Contador.h"
#include "Properties.h"

class SelectLevelState : public Ogre::Singleton<SelectLevelState>, public GameState
{
public:
	SelectLevelState();
	virtual ~SelectLevelState();

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

	//void initialice();
	void setLevel(int level) {_nextLevelNumber = level;};

	// Heredados de Ogre::Singleton.
	static SelectLevelState& getSingleton ();
	static SelectLevelState* getSingletonPtr ();

protected:

	int _nextLevelNumber;
	int _numberOfLevels;

	Contador _contador;
	Modalwindow* _modalWindow;

private:
	void gotoToPlayState();
};

#endif
