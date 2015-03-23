#ifndef __LEVEL_ONE_H__
#define __LEVEL_ONE_H__

#include "Level.h"

class LevelOne : public Level {

public:
	LevelOne(const string& groundMesh, const string& groundName);
	~LevelOne();

private:
	void initializeLevel(const string& groundMesh, const string& groundName);
	int getLevelNumber();



};
#endif
