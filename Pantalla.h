#pragma once

#include <irrlicht.h>
using namespace irr;

class Pantalla
{
protected:
	scene::ISceneNode *nodo;

public:
	Pantalla(void);
	virtual ~Pantalla(void);

	scene::ISceneNode * GetNodo()
	{
		return nodo;
	}

	virtual void Activar()=0;
	virtual void Desactivar()=0;
	virtual void Update()=0;
};
