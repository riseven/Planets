#pragma once

#include <irrlicht.h>
using namespace irr;

class Partida;

class Camara
{
private:
	scene::ICameraSceneNode *nodo;
	Partida *partida;

	core::vector3df dtarget;
	core::vector3df dpos;

public:
	Camara(Partida *partida);
	virtual ~Camara(void);

	void FocusOn(core::vector3df target, core::vector3df pos);
	void Update();
};
