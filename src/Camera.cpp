#include "Camera.h"

Camera::Camera(Ogre::SceneManager* sm){

	_camera = sm->createCamera("PlayCamera");
	_camera->setFOVy (Ogre::Degree(50));
	_camera->setNearClipDistance(1);
	_camera->setFarClipDistance(300);

	initializeParamsConf();
	printConf();
}
Camera::~Camera(){

}

Ogre::Camera*
Camera::getOgreCamera(){
	return _camera;
}

void
Camera::updateCamera(Ogre::Vector3 ballPosition){
	_camera->setPosition(ballPosition.x,(ballPosition.y + _distanceBallY),ballPosition.z-_distanceBallZ);
	_camera->lookAt(ballPosition);
}

void
Camera::initializeParamsConf() {
	_distanceBallY = Properties::getSingletonPtr()->getPropertyFloat("camera.distanceBall.y");
	_distanceBallZ = Properties::getSingletonPtr()->getPropertyFloat("camera.distanceBall.z");

}

void
Camera::printConf() {
	Ogre::LogManager::getSingletonPtr()->logMessage("************* Camera *****************");
	Ogre::LogManager::getSingletonPtr()->logMessage("camera.distanceBall.y: " + Ogre::StringConverter::toString(_distanceBallY));
	Ogre::LogManager::getSingletonPtr()->logMessage("camera.distanceBall.z: " + Ogre::StringConverter::toString(_distanceBallZ));
	Ogre::LogManager::getSingletonPtr()->logMessage("***************************************");
}
