#ifndef __LEVEL_H__
#define __LEVEL_H__

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
	virtual bool isLevelCompleted(SceneNode* ball) = 0;
	virtual Vector3 getInitPositionBall() = 0;
	virtual float getTimeToComplete() = 0;




protected:

	bool colisionNodes(SceneNode* node1, SceneNode* node2);
	SceneNode* addTriangleMeshCollisionShape(
				const string& mesh,
				const string& name,
				const Vector3& pos,
				const Quaternion& orientation,
				const float restitution,
				const float friction,
				const float mass);

	// Parametros configurables
	float _restitution;
	float _friction;
	float _mass;



private:
	void initializeParamsConf();
	void printConf();
};
#endif
