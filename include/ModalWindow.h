#ifndef __MODALWINDOW_H__
#define __MODALWINDOW_H__

#include <Ogre.h>
#include <CEGUI.h>
#include "CeguiManager.h"
class Modalwindow{
public:
	Modalwindow();
	~Modalwindow();


	void show();
	void hide();
	void setText(const std::string& text);


private:

	void initialize();

	CEGUI::Window* _window;
	//CEGUI::Window* _sheet;



};
#endif
