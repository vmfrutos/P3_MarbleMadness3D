#ifndef __LEVEL_H__
#define _LEVEL_H__

#include "PhysicWorld.h"

using namespace Ogre;

class Level : public PhysicWorld{

public:
	Level();
	virtual ~Level();

	virtual void initializeLevel(const string& groundMesh, const string& groundName) = 0;
	virtual void setLight() = 0;
	virtual int getLevelNumber() = 0;
	virtual bool isEndOfLive(SceneNode* ball) = 0;
	virtual Vector3 getInitPositionBall() = 0;
	virtual float getTimeToComplete() = 0;



protected:

	void addGround(const string& groundMesh, const string& groundName);


	// Parametros configurables
	float _restitution;
	float _friction;
	float _mass;



private:
	void initializeParamsConf();
	void printConf();
};
#endif
