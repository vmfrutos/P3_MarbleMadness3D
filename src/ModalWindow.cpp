#include "ModalWindow.h"

Modalwindow::Modalwindow(){

	initialize();

}
Modalwindow::~Modalwindow(){
	if (_window) {
		_window->destroy();
		_window = 0;

	}
}



void Modalwindow::initialize(){

	CEGUI::Window* _sheet = CeguiManager::getSheet();

	//Se crea el layout
	_window  = CEGUI::WindowManager::getSingleton().loadWindowLayout("modalWindow.layout");

	// Se crean los ImageSet
	CEGUI::ImagesetManager::getSingleton().createFromImageFile("ModalWindowBackGroud", "WindowBackGround.png");



	// Se establecen imagenes a los widgets
	_window->getChild("ModalWindow/Fondo")->setProperty("Image", "set:ModalWindowBackGroud image:full_image");



	_sheet->addChildWindow(_window);

	_window->hide();

}

void Modalwindow::show(){
	_window->show();
}

void Modalwindow::hide(){
	_window->hide();
}

void Modalwindow::setText(const std::string& text){
	_window->getChild("ModalWindow/Fondo")->getChild("Text")->setText(text);

}





