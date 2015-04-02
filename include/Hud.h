#ifndef __HUD_H__
#define __HUD_H__

#include <CEGUI.h>
#include "Contador.h"

class Hud {
public:
	Hud();
	~Hud();

	void update(float delta, float fps);
	void resetTime(float time);
	bool decreaseLive();
	void setLevel(int level);
	void setInfo(const string& msg);
	void addInfo(const string& msg);
	int getNumLives();
	float getCurrentTime();


private:

	CEGUI::Window* _sheet;
	CEGUI::Window* _hud;
	CEGUI::Window* _timeText;
	CEGUI::Window* _fpsText;

	Contador _contador;

	int _numLives;

	void initialize();

};
#endif
