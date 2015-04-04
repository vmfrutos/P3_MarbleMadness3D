#ifndef __LEVEL_ONE_H__
#define __LEVEL_ONE_H__

#include "Level.h"

class LevelOne : public Level {

public:
	LevelOne(const string& groundMesh, const string& groundName);
	~LevelOne();

private:
	// Funciones virtuales de Level
	void initializeLevel(const string& groundMesh, const string& groundName);
	int getLevelNumber();
	void setLight();


	// Funciones virtuales implementadas en el nivel
	bool isEndOfLive(SceneNode* ball);
	bool isLevelCompleted(SceneNode* ball);
	Vector3 getInitPositionBall(){return _initPositionBall;};
	float getTimeToComplete(){return _timeToComplete;};


	SceneNode* _lavaNode;
	SceneNode* _groundNode;
	SceneNode* _goalNode;


	Vector3 _initPositionBall;
	float _timeToComplete;

	void initializeParamsConf();
	void printConf();

};
#endif
