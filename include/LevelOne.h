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


	// Funciones propias del nivel
	void addLava(const string& lavaMesh, const string& lavaName);
	bool colisionWithLava(SceneNode* node);
	bool isEndOfLive(SceneNode* ball);
	Vector3 getInitPositionBall(){return _initPositionBall;};
	float getTimeToComplete(){return _timeToComplete;};


	SceneNode* _lavaNode;
	Vector3 _initPositionBall;
	float _timeToComplete;

	void initializeParamsConf();
	void printConf();

};
#endif
