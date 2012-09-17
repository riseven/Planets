#include "Dios.h"

#include "Partida.h"
#include "Juego.h"
#include "Teclado.h"

using namespace irr;

Dios::Dios(Partida *partida, float z, bool izquierda)
	: diosIzquierdo(izquierda),partida(partida)
{
	//nodo = Juego::GetInstance()->GetSceneManager()->addSphereSceneNode(1);
	video::SMaterial material;
	material.Texture1 = Juego::GetInstance()->GetVideoDriver()->getTexture("data/faerie2.bmp");
	material.Lighting = true;

	scene::IAnimatedMesh* faerie = Juego::GetInstance()->GetSceneManager()->getMesh("data/faerie.md2");

	nodo = Juego::GetInstance()->GetSceneManager()->addAnimatedMeshSceneNode(faerie);
	nodo->setPosition(core::vector3df(0, 0, z));
	float sc=0.15f;
	nodo->setScale(core::vector3df(sc, sc, sc));
	if(izquierda)
		nodo->setRotation(core::vector3df(0.0, -90.0f, -90.0));
	else
		nodo->setRotation(core::vector3df(0.0, 90.0f, -90.0));
	nodo->getMaterial(0) = material;
	//nodo->setMD2Animation(scene::EMAT_STAND);
	nodo->setFrameLoop(1, 300);
	nodo->setAnimationSpeed(80);

	if ( diosIzquierdo )
	{
		color = video::SColor(255,255,0,0);
		colorAtmosfera = video::SColor(255,255,0,0);
	}
	else
	{
		color = video::SColor(255,255,255,0);
		colorAtmosfera = video::SColor(255,255,0,255);
	}

	poder[0]=poder[1]=poder[2]=0.0f;
}

Dios::~Dios(void)
{
}

void
Dios::Update()
{
	Teclado *teclado = Juego::GetInstance()->GetTeclado();
	AddPoder(0.01f);

	core::vector3df pos = nodo->getPosition();

	if ( diosIzquierdo )
	{
		if ( teclado->KeyDown(irr::EKEY_CODE::KEY_KEY_Z) )
		{
			if(poder[0]>0)
			{
				this->partida->CrearDisparo(pos,poder[0],1,this);
				poder[0]=0;
				poder[1]=poder[1]/1.2;
				poder[2]=poder[2]/1.2;
			}
		}
		else if ( teclado->KeyDown(irr::EKEY_CODE::KEY_KEY_X) )
		{
			if(poder[0]>0)
			{
				this->partida->CrearDisparo(pos,poder[1],2,this);
				poder[1]=0;
				poder[0]=poder[0]/1.2;
				poder[2]=poder[2]/1.2;
			}
		}
		if ( teclado->KeyDown(irr::EKEY_CODE::KEY_KEY_C) )
		{
			if(poder[0]>0)
			{
				this->partida->CrearDisparo(pos,poder[2],3,this);
				poder[2]=0;
				poder[0]=poder[0]/1.2;
				poder[1]=poder[1]/1.2;
			}
		}

		if ( teclado->Key(irr::EKEY_CODE::KEY_KEY_Q) )
		{
			pos.X += 0.2f ;
		}
		else if ( teclado->Key(irr::EKEY_CODE::KEY_KEY_A) )
		{
			pos.X -= 0.2f ;
		}
	}
	else
	{
		if ( teclado->KeyDown(irr::EKEY_CODE::KEY_NUMPAD1) )
		{
			if(poder[0]>0)
			{
				this->partida->CrearDisparo(pos,poder[0],1,this);
				poder[0]=0;
				poder[1]=poder[1]/1.2;
				poder[2]=poder[2]/1.2;
			}
		}
		if ( teclado->KeyDown(irr::EKEY_CODE::KEY_NUMPAD2) )
		{
			if(poder[0]>0)
			{
				this->partida->CrearDisparo(pos,poder[1],2,this);
				poder[1]=0;
				poder[0]=poder[0]/1.2;
				poder[2]=poder[2]/1.2;
			}
		}
		if ( teclado->KeyDown(irr::EKEY_CODE::KEY_NUMPAD3) )
		{
			if(poder[0]>0)
			{
				this->partida->CrearDisparo(pos,poder[2],3,this);
				poder[2]=0;
				poder[0]=poder[0]/1.2;
				poder[1]=poder[1]/1.2;
			}
		}

		if ( teclado->Key(irr::EKEY_CODE::KEY_UP) )
		{
			pos.X += 0.2f ;
		}
		else if ( teclado->Key(irr::EKEY_CODE::KEY_DOWN) )
		{
			pos.X -= 0.2f ;
		}
	}

	// Comprobamos que no nos salimos de la pantalla
	if ( pos.X < -25.0f )
	{
		pos.X = -25.0f ;
	}
	else if ( pos.X > 25.0f )
	{
		pos.X = 25.0f ;
	}

	nodo->setPosition(pos);
}

void
Dios::AddPoder(float p)
{
	for (int i = 0 ; i < 3 ; i++ )
	{
		float ajuste ;
		ajuste = poder[i] > 10 ? poder[i]/10 : 1 ;
		poder[i] += p / ajuste ;
		if ( poder[i] > 100.0f )
		{
			poder[i] = 100.0f ;
		}
	}
}

float*
Dios::GetPoder()
{
	return poder;
}