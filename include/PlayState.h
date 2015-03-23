#ifndef PlayState_H
#define PlayState_H

#include <Ogre.h>
#include <OIS/OIS.h>

#include "GameState.h"
#include "LevelOne.h"
#include "Ball.h"
#include "Camera.h"


class PlayState : public Ogre::Singleton<PlayState>, public GameState
{
 public:
  PlayState () {}

  void enter ();
  void exit ();
  void pause ();
  void resume ();

  void keyPressed (const OIS::KeyEvent &e);
  void keyReleased (const OIS::KeyEvent &e);

  void mouseMoved (const OIS::MouseEvent &e);
  void mousePressed (const OIS::MouseEvent &e, OIS::MouseButtonID id);
  void mouseReleased (const OIS::MouseEvent &e, OIS::MouseButtonID id);

  bool frameStarted (const Ogre::FrameEvent& evt);
  bool frameEnded (const Ogre::FrameEvent& evt);

  // Heredados de Ogre::Singleton.
  static PlayState& getSingleton ();
  static PlayState* getSingletonPtr ();

 private:
  Ogre::Root* _root;
  Ogre::RenderWindow* _win;
  Ogre::SceneManager* _sceneMgr;
  Ogre::Viewport* _viewport;


  bool _exitGame;

  int _currentLevelNumber;
  Level* _currentLevel;
  Ball* _ball;
  ::Camera* _camera;

  void createScene();
  void initializeParamsConf();
  void printConf();


  // Teclas pulsadas
  bool KEY_UP;
  bool KEY_DOWN;
  bool KEY_RIGHT;
  bool KEY_LEFT;

};

#endif
