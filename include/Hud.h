#ifndef __HUD_H__
#define __HUD_H__

#include "Contador.h"
#include "Properties.h"
#include "CeguiManager.h"
#include <CEGUI.h>

class Hud {
public:
	Hud();
	virtual ~Hud();

	void update(float delta, float fps);
	void resetTime(float time);
	bool decreaseLive();
	void setLevel(int level);
	void setNumLives(int lives);
	void setInfo(const string& msg);
	void addInfo(const string& msg);
	int getNumLives();
	float getCurrentTime();
	int getElapsedTime();



private:

	CEGUI::Window* _hud;
	CEGUI::Window* _timeText;
	CEGUI::Window* _fpsText;

	Contador _contador;

	static int _numLives;
	int _startAlertTime;

	void initialize();

};
#endif
