#pragma once

#include <irrlicht.h>
using namespace irr;

class Partida;
class SolNode;

class Sol
{
private:
	core::vector3df pos;
	Partida * partida ;
	SolNode * nodo;
	float masa;

public:
	Sol(Partida *partida, core::vector3df pos);
	virtual ~Sol(void);

	float GetCalorEmitido(core::vector3df pos);
	float GetMasa();
};
