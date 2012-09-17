#include "Juego.h"

#include "Partida.h"
#include "Teclado.h"
#include "Pantalla.h"

#include <time.h>
#include <math.h>
#include <iostream>
#include <irrlicht.h>

using namespace irr;

Juego * Juego::singleton = NULL;

Juego *
Juego::GetInstance()
{
	if ( singleton == NULL )
	{
		singleton = new Juego();
		singleton->Init();
	}
	return singleton;
}

Juego::Juego(void)
{
	pantallaActual = NULL;
}

Juego::~Juego(void)
{
}

void
Juego::Init()
{
	srand((unsigned int)time(NULL));

	video::E_DRIVER_TYPE driverType = video::EDT_DIRECT3D9;

	teclado = new Teclado();

	device = createDevice(
		driverType, 
		core::dimension2d<s32>(800, 600), 
		32, 
		true, false, false, 
		teclado );

	if ( device )
	{
		device->setWindowCaption(L"Planets");
	}

	gui = device->getGUIEnvironment();

	Partida *partida = new Partida();
	//Le paso al gui un puntero a los dioses para que puedea acceder a las barras
	SetPantalla(partida);
}

void
Juego::Run()
{
	if (!device)
	{
		return;
	}

	while(device->run())
	{
		// Actualizamos
		pantallaActual->Update();
		teclado->Update();

		// Dibujamos
		GetVideoDriver()->beginScene(true, true, video::SColor(0,0,0,0));
		GetSceneManager()->drawAll();
		GetGui()->drawAll();
		GetVideoDriver()->endScene();


	}
}

irr::IrrlichtDevice * 
Juego::GetDevice()
{
	return device;
}

scene::ISceneManager *
Juego::GetSceneManager()
{
	return device->getSceneManager();
}

video::IVideoDriver *
Juego::GetVideoDriver()
{
	return device->getVideoDriver();
}

gui::IGUIEnvironment *
Juego::GetGui()
{
	return gui;
}

void
Juego::SetPantalla(Pantalla *pantalla)
{
	if ( pantallaActual )
	{
		pantallaActual->Desactivar();
	}
	pantallaActual = pantalla ;
	pantallaActual->Activar();
}

Teclado *
Juego::GetTeclado()
{
	return teclado;
}
