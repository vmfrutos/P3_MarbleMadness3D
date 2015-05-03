#ifndef __LEVEL_ONE_H__
#define __LEVEL_ONE_H__


#include "Level.h"
#include "Enemy.h"
#include "Lanzadera.h"

class Enemy;
class Lanzadera;
class LevelOne : public Level {

public:
	LevelOne(const string& groundMesh, const string& groundName);
	~LevelOne();
	void update(float delta);
	void keyPressed(enum OIS::KeyCode key);
	void keyReleased(enum OIS::KeyCode key);



private:
	// Funciones virtuales de Level
	void initializeLevel(const string& groundMesh, const string& groundName);
	int getLevelNumber();
	void setLight();
	void checkTriggers();


	// Funciones virtuales implementadas en el nivel
	bool isEndOfLive(SceneNode* ball);
	bool isLevelCompleted(SceneNode* ball);
	Vector3 getInitPositionBall();
	float getTimeToComplete();

	const int numLavaNodes = 5;
	std::vector<SceneNode*> _lavaNodes;
	SceneNode* _groundNode;
	SceneNode* _goalNode;

	float timeCurrentZone;
	SceneNode* _zoneOneLimit;
	SceneNode* _zoneTwoLimit;
	SceneNode* _zoneThreeLimit;
	SceneNode* _zoneFourLimit;

	Vector3 _initPositionBall;
	Vector3 _zoneTwoPositionBall;
	Vector3 _zoneThreePositionBall;
	Vector3 _zoneFourPositionBall;
	Vector3 _zoneFivePositionBall;
	float _timeToComplete;

	std::vector<Enemy*> _enemyList;

	Lanzadera* _lanzadera;

	void initializeParamsConf();
	void printConf();

	bool _launcherMode;
	bool _shootMode;

	enum zones { ZONE1,ZONE2,ZONE3,ZONE4,ZONE5};
	zones _zone;


};
#endif
