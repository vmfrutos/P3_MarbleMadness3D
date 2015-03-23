#include "LevelOne.h"

LevelOne::LevelOne(const string& groundMesh, const string& groundName): Level(){
	initializeLevel(groundMesh,groundName);
}

LevelOne::~LevelOne(){

}

void
LevelOne::initializeLevel(const string& groundMesh, const string& groundName){

	// Se crea el suelo
	addGround(groundMesh, groundName);
}

int
LevelOne::getLevelNumber() {
	return 1;
}
