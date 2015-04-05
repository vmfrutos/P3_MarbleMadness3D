#ifndef PauseState_H
#define PauseState_H

#include <Ogre.h>
#include <OIS/OIS.h>
#include "ModalWindow.h"

#include "GameState.h"

class PauseState : public Ogre::Singleton<PauseState>, public GameState
{
 public:
  PauseState();
  virtual ~PauseState();

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
  static PauseState& getSingleton ();
  static PauseState* getSingletonPtr ();

 private:
  Modalwindow* _modalWindow;

};

#endif
