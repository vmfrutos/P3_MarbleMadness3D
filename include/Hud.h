#ifndef __HUD_H__
#define __HUD_H__

#include <CEGUI.h>
#include "Contador.h"

class Hud {
public:
	Hud(float time);
	~Hud();

	void update(float delta, float fps);
	bool decreaseLive();
	void setLevel(int level);
	void setInfo(const string& msg);
	int getNumLives();


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
