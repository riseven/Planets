#pragma once
#include <irrlicht.h>
using namespace irr;
class Partida;
class DisparoNode;
class Dios;

class Disparo
{
private:
	core::vector3df pos;
	Partida * partida ;
	DisparoNode * nodo;
	int tipo;
	float energia;
	core::vector3df velocidad;
	Dios *dios;

public:
	Disparo(Partida *partida,core::vector3df pos,int tipo,float energia,Dios *dios);
	Disparo(Partida *partida);
	virtual ~Disparo(void);

	core::vector3df GetPosicion();
	void SetPosicion(core::vector3df);
	Dios * GetDios();

	int GetTipo();
	void SetTipo(int tipo);

	float GetEnergia();
	void SetEnergia(float energia);
	void SetVelocidad(core::vector3df);
	core::vector3df GetVelocidad();

	void Update();
};
