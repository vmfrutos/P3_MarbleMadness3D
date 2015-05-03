#include "Lanzadera.h"

Lanzadera::Lanzadera(const string& name,const Vector3& pos){

	_soporteName = name + "soporte";
	_canonName = name + "canon";
	_elevatorName = name + "elevator";

	_initPos = pos;

	_soporteNode = createSoporte();
	_canonNode = createCanyon();
	_elevatorNode = createElevator();

	_shootState = STOP;
	_shootPower = 40;
	_timeToInc = 0.0;


	for (unsigned int i=0;i<_bodies.size();i++){
		OgreBulletDynamics::RigidBody * rb = _bodies[i];
		if (rb->getName() == _elevatorName){
			_elevatorBody = _bodies[i];
		} else if (rb->getName() == _soporteName){
			_soporteBody = _bodies[i];
		} else if (rb->getName() == _canonName){
			_canonBody = _bodies[i];
		}
	}

	createConstraintSoporte();
	createConstraintCanyon();
	createConstraintElevator();


}
Lanzadera::~Lanzadera(){

}


void
Lanzadera::elevatorUp(){
	//_elevatorState = ELEVATOR_UP;
	_constraintElevator->setTargetLinMotorVelocity(-1.0);
}

void
Lanzadera::elevatorDown(){
	//_elevatorState = ELEVATOR_DOWN;
	_constraintElevator->setTargetLinMotorVelocity(1.0);
}

void
Lanzadera::elevatorStop(){
	//_elevatorState = ELEVATOR_STOP;
	_constraintElevator->setTargetLinMotorVelocity(0.0);
}

void
Lanzadera::rotateSoporteRight(){
	_constraintSoporte->enableAngularMotor(true, -0.1, maxMotorImpulse);
}

void
Lanzadera::rotateSoporteLeft(){
	_constraintSoporte->enableAngularMotor(true, 0.1, maxMotorImpulse);
}

void
Lanzadera::rotateSoporteStop(){
	_constraintSoporte->enableAngularMotor(true, 0.0, maxMotorImpulse);
}

void
Lanzadera::rotateCanyonUp(){
	_constraintCanyon->enableAngularMotor(true, 0.1, maxMotorImpulse);
}
void
Lanzadera::rotateCanyonDown(){
	_constraintCanyon->enableAngularMotor(true, -0.1, maxMotorImpulse);
}

void
Lanzadera::rotateCanyonStop(){
	_constraintCanyon->enableAngularMotor(true, 0.0, maxMotorImpulse);
}


void
Lanzadera::settingShootPower(){
	_shootPower = 40;
	_timeToInc = 0.0;
	_shootState = SETTING_POWER_UP;
}

void
Lanzadera::shoot(){
	_shootState = STOP;

	Vector3 direction = getCanyonDirection();
	PlayState::getSingletonPtr()->getBall()->shoot(direction,_shootPower);
}

void
Lanzadera::update(float delta){
	_soporteBody->getBulletRigidBody()->activate(true);

	if (_shootState == SETTING_POWER_UP){

		_timeToInc += delta;
		if (_timeToInc >= 0.050 && _shootPower <=90){
			_shootPower++;
			_timeToInc = 0.0;
			PlayState::getSingletonPtr()->getHud()->setInfo(StringConverter::toString(_shootPower));
		}
		if (_shootPower >= 90) {
			_shootState = SETTING_POWER_DOWN;
			_timeToInc = 0.0;
		}
	} else if (_shootState == SETTING_POWER_DOWN){

		_timeToInc += delta;
		if (_timeToInc >= 0.050 && _shootPower >=40){
			_shootPower--;
			_timeToInc = 0.0;
			PlayState::getSingletonPtr()->getHud()->setInfo(StringConverter::toString(_shootPower));
		}
		if (_shootPower <= 40) {
			_shootState = SETTING_POWER_UP;
			_timeToInc = 0.0;
		}
	}

	float pos = _constraintElevator->getLinearPos();
	//PlayState::getSingletonPtr()->getHud()->setInfo(StringConverter::toString(pos));
	if (fequal(pos,-0.200001f)){ // Detenido abajo
		if (GameSound::getSingletonPtr()->isPlayingSoundFX(GameSound::FX_ELEVATOR)){
			GameSound::getSingletonPtr()->stopSoundFX(GameSound::FX_ELEVATOR);
		}
	} else if (fequal(pos,-0.-8.39999f)){ // Detenido arriba
		if (GameSound::getSingletonPtr()->isPlayingSoundFX(GameSound::FX_ELEVATOR)){
			GameSound::getSingletonPtr()->stopSoundFX(GameSound::FX_ELEVATOR);
		}
	} else if (pos < -0.200001f){ // En movimiento
		if (!GameSound::getSingletonPtr()->isPlayingSoundFX(GameSound::FX_ELEVATOR)){
			GameSound::getSingletonPtr()->playSoundFX(GameSound::FX_ELEVATOR);
		}
	}



}

void
Lanzadera::createConstraintElevator(){
	btTransform localA, localB;
	localA.setIdentity();
	localA.getBasis().setEulerZYX(0, 0, M_PI_2);
	localA.setOrigin(btVector3(0.0f, 0.0f, 0.0f));
	localB.setIdentity();
	localB.getBasis().setEulerZYX(0, 0, M_PI_2);
	localB.setOrigin(btVector3(7.5f, 0.0, 0.0));


	_constraintElevator = new btSliderConstraint(*_elevatorBody->getBulletRigidBody(), *_soporteBody->getBulletRigidBody(), localA, localB, true);

	_constraintElevator->setLowerLinLimit(-8.4f);
	_constraintElevator->setUpperLinLimit(-0.2f);
	_constraintElevator->setLowerAngLimit(0.0f);
	_constraintElevator->setUpperAngLimit(0.0f);



	_constraintElevator->setPoweredLinMotor(true);
	_constraintElevator->setMaxLinMotorForce(maxMotorImpulse);

	_constraintElevator->setDbgDrawSize(5.0f);
	_world->getBulletDynamicsWorld()->addConstraint(_constraintElevator, true);
}

void
Lanzadera::createConstraintSoporte() {
	const btVector3 pivotePositon(0.0f,0.0f,0.0f);
	btVector3 axiToPivote(0.0f,1.0f,0.0f);

	_constraintSoporte = new btHingeConstraint(*_soporteBody->getBulletRigidBody(), pivotePositon, axiToPivote);
	_world->getBulletDynamicsWorld()->addConstraint(_constraintSoporte);
	_constraintSoporte->setDbgDrawSize(btScalar(5.f));
}

void
Lanzadera::createConstraintCanyon() {
	const btVector3 pivotePositonA(0.0f,0.0f,0.0f); // Punto de pivotaje. Sobre el centro del cañon
	btVector3 axiToPivoteA(1.0f,0.0f,0.0f); // Eje sobre el que rota el cañon
	const btVector3 pivotePositonB(0.0f,5.0f,0.0f); // Punto de pivotaje. Sobre el centro del soporte
	btVector3 axiToPivoteB(0.0f,0.0f,0.0f); // Eje sobre el que rota el soporte (Ninguno)

	_constraintCanyon = new btHingeConstraint(*_canonBody->getBulletRigidBody(), *_soporteBody->getBulletRigidBody(),pivotePositonA, pivotePositonB,axiToPivoteA,axiToPivoteB);

	_constraintCanyon->enableAngularMotor(true, 0.0, maxMotorImpulse);

	_world->getBulletDynamicsWorld()->addConstraint(_constraintCanyon);
	_constraintCanyon->setDbgDrawSize(btScalar(5.f));
}

SceneNode*
Lanzadera::createSoporte(){

	OgreBulletCollisions::CompoundCollisionShape* soporteCompound = new OgreBulletCollisions::CompoundCollisionShape();

	// Se construye el Compound


	Vector3 size1(1.0,3.5,1.65);
	OgreBulletCollisions::BoxCollisionShape *sceneBoxShape1 = new OgreBulletCollisions::BoxCollisionShape(size1);
	Vector3 localPosition1(4.2,4.5,0.0);
	Quaternion quat1(1.0,0.0,0.0,0.);
	soporteCompound->addChildShape(sceneBoxShape1,localPosition1,quat1);

	Vector3 size3(0.7,3.5,1.65);
	OgreBulletCollisions::BoxCollisionShape *sceneBoxShape3 = new OgreBulletCollisions::BoxCollisionShape(size3);
	Vector3 localPosition3(-3.8,4.5,0.0);
	Quaternion quat3(1.0,0.0,0.0,0.);
	soporteCompound->addChildShape(sceneBoxShape3,localPosition3,quat3);

	Vector3 size4(1.9,0.2,1.65);
	OgreBulletCollisions::BoxCollisionShape *sceneBoxShape4 = new OgreBulletCollisions::BoxCollisionShape(size4);
	Vector3 localPosition4(3.3,8.2,0.0);
	Quaternion quat4(1.0,0.0,0.0,0.);
	soporteCompound->addChildShape(sceneBoxShape4,localPosition4,quat4);

	Vector3 size5(1.5,0.2,1.65);
	OgreBulletCollisions::BoxCollisionShape *sceneBoxShape5 = new OgreBulletCollisions::BoxCollisionShape(size5);
	Vector3 localPosition5(-3.0,8.2,0.0);
	Quaternion quat5(1.0,0.0,0.0,0.);
	soporteCompound->addChildShape(sceneBoxShape5,localPosition5,quat5);



	Vector3 size2(5.2,0.2,5.2);
	OgreBulletCollisions::CylinderCollisionShape *sceneCylinder = new OgreBulletCollisions::CylinderCollisionShape(size2,Vector3::UNIT_Y);
	Vector3 localPosition2(0.0,0.25,0.0);
	Quaternion quat2(1.0,0.0,0.0,0.0);
	soporteCompound->addChildShape(sceneCylinder,localPosition2,quat2);



	return addRigidBody(soporteCompound,"Soporte.mesh",_soporteName,_initPos,Quaternion::IDENTITY,0.0, 0.5, 290,_sceneManager->getRootSceneNode());
}

SceneNode*
Lanzadera::createCanyon(){

	OgreBulletCollisions::CompoundCollisionShape* canyonCompound = new OgreBulletCollisions::CompoundCollisionShape();

	// Se construye el Compound
	Vector3 size1(0.02,3.0,1.0);
	OgreBulletCollisions::BoxCollisionShape *sceneBoxShape1 = new OgreBulletCollisions::BoxCollisionShape(size1);
	Vector3 localPosition1(1.1,0.5,0.0);
	Quaternion quat1(1.0,0.0,0.0,0.);
	canyonCompound->addChildShape(sceneBoxShape1,localPosition1,quat1);

	Vector3 size2(1.0,3.0,0.02);
	OgreBulletCollisions::BoxCollisionShape *sceneBoxShape2 = new OgreBulletCollisions::BoxCollisionShape(size2);
	Vector3 localPosition2(0.0,0.5,1.1);
	Quaternion quat2(1.0,0.0,0.0,0.);
	canyonCompound->addChildShape(sceneBoxShape2,localPosition2,quat2);

	Vector3 size3(1.0,3.0,0.02);
	OgreBulletCollisions::BoxCollisionShape *sceneBoxShape3 = new OgreBulletCollisions::BoxCollisionShape(size3);
	Vector3 localPosition3(0.0,0.5,-1.1);
	Quaternion quat3(1.0,0.0,0.0,0.);
	canyonCompound->addChildShape(sceneBoxShape3,localPosition3,quat3);

	// Se construye el Compound
	Vector3 size4(0.02,3.0,1.0);
	OgreBulletCollisions::BoxCollisionShape *sceneBoxShape4 = new OgreBulletCollisions::BoxCollisionShape(size4);
	Vector3 localPosition4(-1.1,0.5,0.0);
	Quaternion quat4(1.0,0.0,0.0,0.);
	canyonCompound->addChildShape(sceneBoxShape4,localPosition4,quat4);

	// Se construye el Compound
	Vector3 size5(1.0,0.02,1.0);
	OgreBulletCollisions::BoxCollisionShape *sceneBoxShape5 = new OgreBulletCollisions::BoxCollisionShape(size5);
	Vector3 localPosition5(0.0,0.0,0.0);
	Quaternion quat5(1.0,0.0,0.0,0.);
	canyonCompound->addChildShape(sceneBoxShape5,localPosition5,quat5);


	return addRigidBody(canyonCompound,"Canon.mesh",_canonName,Vector3(_initPos.x,_initPos.y+5,_initPos.z),Quaternion::IDENTITY,0.0, 0.5, 50,_sceneManager->getRootSceneNode());
}

SceneNode*
Lanzadera::createElevator(){
	OgreBulletCollisions::CompoundCollisionShape* elevatorCompound = new OgreBulletCollisions::CompoundCollisionShape();
	Vector3 size(1.95,0.065,1.72);
	OgreBulletCollisions::BoxCollisionShape *sceneBoxShape = new OgreBulletCollisions::BoxCollisionShape(size);

	Vector3 localPosition(-0.2,0.0,0.0);
	Quaternion quat(1.0,0.0,0.0,0.);
	elevatorCompound->addChildShape(sceneBoxShape,localPosition,quat);


	return addRigidBody(elevatorCompound,"Elevator.mesh",_elevatorName,Vector3(_initPos.x+7.5,_initPos.y+0.2,_initPos.z),Quaternion::IDENTITY,0.0, 0.5, 20,_sceneManager->getRootSceneNode());
}

Vector3
Lanzadera::getCanyonDirection(){
	Vector3 direction = _canonNode->getOrientation() * Ogre::Vector3(1, 1, 1);
	return direction.normalisedCopy();
}

bool
Lanzadera::fequal(float a, float b)
{
	return fabs(a-b) < precision;
}


