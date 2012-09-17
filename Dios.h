#pragma once

#include <irrlicht.h>
using namespace irr;

class Partida;

class Dios
{
private:
	scene::IAnimatedMeshSceneNode *nodo;
	Partida *partida;
	bool diosIzquierdo;
	video::SColor color;
	video::SColor colorAtmosfera;
	float poder[3];

public:
	Dios(Partida *partida, float z, bool izquierda);
	Dios();
	virtual ~Dios(void);

	video::SColor GetColorAtmosfera()
	{
		return colorAtmosfera;
	}

	void Update();
	void AddPoder(float p);
	float* GetPoder();
	bool EsDiosIzquierdo()
	{
		return diosIzquierdo;
	}

	core::vector3df GetPosicion()
	{
		return nodo->getPosition();
	}

};
