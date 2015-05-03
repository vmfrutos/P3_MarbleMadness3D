#ifndef __LANZADERA_H__
#define __LANZADERA_H__

#ifndef M_PI_2
#define M_PI_2     1.57079632679489661923
#endif

#include "Ogre.h"
#include "PhysicWorld.h"
#include "PlayState.h"
#include "OgreBulletDynamicsRigidBody.h"
#include "BulletDynamics/ConstraintSolver/btSliderConstraint.h"
#include "BulletDynamics/ConstraintSolver/btHingeConstraint.h"
#include "BulletDynamics/ConstraintSolver/btPoint2PointConstraint.h"

using namespace Ogre;
using namespace std;

class Lanzadera : public PhysicWorld {

public:
	Lanzadera(const string& name,const Vector3& pos);
	~Lanzadera();

	void elevatorUp();
	void elevatorDown();
	void elevatorStop();
	void update(float delta);
	void rotateSoporteRight();
	void rotateSoporteLeft();
	void rotateSoporteStop();
	void rotateCanyonUp();
	void rotateCanyonDown();
	void rotateCanyonStop();

	Vector3 getCanyonDirection();
	SceneNode*  getCanyonNode(){return _canonNode;};
	//SceneNode* getPlaneShootTriggerNode(){return _planeShootTrigger;};
	void settingShootPower();
	void shoot();



private:
	SceneNode* _canonNode;
	SceneNode* _soporteNode;
	SceneNode* _elevatorNode;
	//SceneNode* _planeShootTrigger;

	OgreBulletDynamics::RigidBody* _elevatorBody;
	OgreBulletDynamics::RigidBody* _soporteBody;
	OgreBulletDynamics::RigidBody* _canonBody;

	string _soporteName;
	string _canonName;
	string _elevatorName;


	Vector3 _initPos;

	const btScalar maxMotorImpulse = 2.0f;
	const float precision = 0.0001;

	btScalar _soporteAngle;

	enum shootStates { SETTING_POWER_UP,SETTING_POWER_DOWN,STOP };
	shootStates _shootState;
	int _shootPower;
	float _timeToInc;


	btSliderConstraint* _constraintElevator;
	btHingeConstraint* _constraintSoporte;
	btHingeConstraint* _constraintCanyon;

	void createConstraintElevator();
	void createConstraintSoporte();
	void createConstraintCanyon();

	SceneNode* createSoporte();
	SceneNode* createCanyon();
	SceneNode* createElevator();

	bool fequal(float a, float b);

};
#endif
