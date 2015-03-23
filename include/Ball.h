#ifndef __BALL_H__
#define __BALL_H__

#include "PhysicWorld.h"

class Ball : public PhysicWorld {
public:
	Ball(const string& ballMesh, const string& ballName, Vector3 initPos);
	~Ball();
	void applyImpulse(Vector3 direction, float delta);
	const Vector3& getPosition();

private:

	SceneNode* _ballNode;
	Entity* _ballEnt;
	OgreBulletDynamics::RigidBody *_rigidBall;

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
