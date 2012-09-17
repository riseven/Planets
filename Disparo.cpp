#include "Disparo.h"

#include "Partida.h"
#include "DisparoNode.h"
#include "Juego.h"
#include "Dios.h"
Disparo::Disparo(Partida *partida)
{
	nodo = new DisparoNode(
		Juego::GetInstance()->GetSceneManager()->getRootSceneNode(),
		Juego::GetInstance()->GetSceneManager(),
		-1,
		3,core::vector3df(),0);
}

Disparo::Disparo(Partida *partida,core::vector3df pos,int tipo,float energia,Dios *dios) 
		: pos(pos),tipo(tipo),energia(energia),dios(dios)
{
	if ( energia < 10.0f )
	{
		energia = 10.0f ;
	}

	if ( energia < 99.9f )
	{
		energia *= 0.5f ;
	}
	else
	{
		energia = 100.0f;
	}


	nodo = new DisparoNode(
		Juego::GetInstance()->GetSceneManager()->getRootSceneNode(),
		Juego::GetInstance()->GetSceneManager(),
		-1,
		energia,pos,tipo);
	velocidad.Z=0.15f;
	if ( !dios->EsDiosIzquierdo() )
	{
		velocidad = -velocidad;
	}
}

Disparo::~Disparo(void)
{
	if(energia>=99.9f)
		nodo->Destruir(true);
	else
		nodo->Destruir(false);
	//printf("PUTA\n");
}

void
Disparo::SetPosicion(core::vector3df pos)
{
	this->pos=pos;
	nodo->setPosition(pos);

}

Dios*
Disparo::GetDios()
{
	return dios;
}

void
Disparo::SetEnergia(float energia)
{
	this->energia=energia;
}

void
Disparo::SetTipo(int tipo)
{
	this->tipo=tipo;
}

int
Disparo::GetTipo()
{
	return tipo;
}
core::vector3df
Disparo::GetPosicion()
{
	return pos;
}
float
Disparo::GetEnergia()
{
	return energia;
}

core::vector3df
Disparo::GetVelocidad()
{
	return velocidad;
}

void
Disparo::SetVelocidad(core::vector3df v)
{
	float max=0.4f;
	if(v.X>max)
		v.X=max;
	else if(v.X<-max)
		v.X=-max;
	if(v.Z>max)
		v.Z=max;
	else if(v.Z<-max)
		v.Z=-max;
	velocidad=v;

}

void
Disparo::Update()
{
	pos+=velocidad;
	nodo->SetPosicion(pos);
}
