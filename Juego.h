#pragma once

#include <irrlicht.h>
using namespace irr;

class Teclado;
class Pantalla;

class Juego
{
private:
	static Juego * singleton;
	irr::IrrlichtDevice * device;
	Teclado *teclado;
	Pantalla *pantallaActual;
	gui::IGUIEnvironment* gui;

protected:
	Juego(void);
	void Init();
public:
	static Juego * GetInstance();
	virtual ~Juego(void);
	void Run();
	irr::IrrlichtDevice * GetDevice();
	scene::ISceneManager * GetSceneManager();
	video::IVideoDriver * GetVideoDriver();
	gui::IGUIEnvironment * GetGui();
	void SetPantalla(Pantalla *pantalla);
	//Raton * GetRaton();
	Teclado * GetTeclado();
	//GestorMusica * GetGestorMusica();
	//GestorSonidos * GetGestorSonidos();
};
