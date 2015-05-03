#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Ogre.h"
#include "Properties.h"

class Camera {

public:
	Camera(Ogre::SceneManager* sm);
	~Camera();
	Ogre::Camera* getOgreCamera();
	void updateCamera(Ogre::Vector3 ballPosition);
	void updateCameraFarView(Ogre::Vector3 ballPosition);

private:
	Ogre::Camera* _camera;

	float _distanceBallY;
	float _distanceBallZ;

	void initializeParamsConf();
	void printConf();
};
#endif
