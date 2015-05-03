#ifndef __BALL_H__
#define __BALL_H__

#include "PhysicWorld.h"
#include "GameSound.h"

class Ball : public PhysicWorld {
public:
	Ball(const string& ballMesh, const string& ballName, Vector3 initPos);
	virtual ~Ball();
	void applyImpulse(Vector3 direction, float delta);
	const Vector3& getPosition();
	SceneNode* getSceneNode();
	void resetBall(Vector3 pos);

	void shoot(Vector3 direcction,int power);
	//void setShootMode(bool value){_shootMode = value;};
	//bool getShootMode(){return _shootMode;};

private:

	SceneNode* _ballNode;
	Entity* _ballEnt;
	OgreBulletDynamics::RigidBody *_rigidBall;
	OgreBulletCollisions::SphereCollisionShape * _ballShape;

	// Parametros configurables
	float _restitution;
	float _friction;
	float _mass;
	float _diameter;
	float _impulseForce;



	void initializeParamsConf();
	void printConf();
	void initializeBall(const string& ballMesh, const string& ballName, Vector3 initPos);






};
#endif
