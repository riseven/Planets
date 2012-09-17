#include "Partida.h"

#include "Juego.h"

#include "Planeta.h"
#include "SolNode.h"
#include "Dios.h"
#include "Sol.h"
#include "GUI.h"
#include "Camara.h"
#include "Teclado.h"
#include "MegaMensaje.h"

#include <stdlib.h>
using namespace irr;

Partida::Partida() : 
	Pantalla()
{
	enSecuencia = false ;

	Inicializar();
}

Partida::~Partida(void)
{
}

void
Partida::Inicializar()
{
	InicializarSistema();
	InicializarDioses();
	InicializarFondo();
	InicializarIluminacion();
	InicializarCamara();
	InicializarGUI();
	InicializarMegaMensajes();

	bool iz = true ;
	for ( list<Planeta *>::iterator i = planetas.begin() ; i != planetas.end() ; ++i )
	{
		(*i)->ImpactoAgua(0.01f, iz?diosIzq:diosDer);
		iz = !iz ;
	}
}

void
Partida::InicializarSistema()
{
	// Creamos el sol
	sol = new Sol(this, core::vector3df());

	// Creamos los planetas
	for ( int i = 0 ; i < 6 ; i++ )
	{
		float x, z, cerca;
		do
		{
			x = (float)(((rand()%2000)/1000.0f)-1.0)*20.0f;
			z = (float)(((rand()%2000)/1000.0f)-1.0)*20.0f;

			// Comprobamos que no esté muy cerca de algun planeta existente
			cerca = false ;
			for ( list<Planeta *>::iterator i = planetas.begin() ; i != planetas.end() ; ++i )
			{
				float px = (*i)->GetPosicion().X;
				float pz = (*i)->GetPosicion().Z;

				float d2 = (x-px)*(x-px) + (z-pz)*(z-pz) ;
				if ( d2 < 150 )
				{
					cerca = true;
					break;
				}
			}
			if ( x*x + z*z < 150 )
			{
				// Esta cerca del sol
				cerca = true ;
			}
		}while (cerca);

		Planeta *planeta = new Planeta();
		planeta->SetPosicion(core::vector3df(x,0,z));

		planetas.push_back(planeta);
	}
}
void
Partida::InicializarDioses()
{
	diosIzq = new Dios(this, -35, true);
	diosDer = new Dios(this, 35, false);
}

void
Partida::InicializarFondo()
{
	video::IVideoDriver *video=Juego::GetInstance()->GetVideoDriver();
	video->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, false);

	Juego::GetInstance()->GetSceneManager()->addSkyDomeSceneNode(
		video->getTexture("data/espacio3.jpg"),20,20,3,2);
	video->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, true);
}

void
Partida::InicializarIluminacion()
{
	Juego::GetInstance()->GetSceneManager()->addLightSceneNode(NULL, core::vector3df(0.0f, -50.0f, -50.0f));
	Juego::GetInstance()->GetSceneManager()->addLightSceneNode(NULL, core::vector3df(0.0f, -120.0f, 120.0f));
}

void
Partida::InicializarGUI()
{
	gui=new GUI(this);
}

void
Partida::InicializarCamara()
{
	camara = new Camara(this);
}

void
Partida::InicializarMegaMensajes()
{
	msgDiluvio = new MegaMensaje("data/diluvio1.png");
	msgCalentamiento = new MegaMensaje("data/calentamiento.png");
	msgArmaggeddon = new MegaMensaje("data/armagedon.png");

	msgEmpate = new MegaMensaje("data/empate.png");
	msgGanoRojo = new MegaMensaje("data/ganarojo.png");
	msgGanoAzul = new MegaMensaje("data/ganaazul.png");
}

void
Partida::CrearDisparo(core::vector3df pos,float valor,int tipo,Dios *dios)
{

	Disparo *disparo = new Disparo(this,pos,tipo,valor,dios);

	//Disparos
	disparos.push_back(disparo);
}

void
Partida::Activar()
{
	//Juego::GetInstance()->GetSceneManager()->setActiveCamera(...)
}

void
Partida::Desactivar()
{
}

void
Partida::Update()
{

	// Planetas
	for ( list<Planeta *>::iterator p = planetas.begin() ; p != planetas.end() ; ++p )
	{
		(*p)->Update();
	}

	// Dioses
	diosIzq->Update();
	diosDer->Update();
	if(gui!=NULL)
		gui->Update();

	// Disparos
	ActualizarDisparos();


	if ( enSecuencia )
	{
		// Comprobamos la desactivacion de la secuncia
		ticksSecuencia--;
		if ( ticksSecuencia < 1 )
		{
			camara->FocusOn(core::vector3df(), core::vector3df(1,-40,0));
			enSecuencia = false ;
		}
		else if ( ticksSecuencia < 500 )
		{
			msgDiluvio->SetVisible(false);
		}
	}
	else
	{
		// Comprobamos si entramos en secuencia
		if ( Juego::GetInstance()->GetTeclado()->Key(irr::KEY_SPACE) )
		{
			this->PreColisionPlaneta( planetas.front(), 1) ;
		}
	}

	// Camara
	camara->Update();

	// Comprobamos si ha acabado la partida
	bool izqMuerto=true;
	bool derMuerto=true;
	for ( list<Planeta *>::iterator i = planetas.begin() ; i != planetas.end() ; ++i )
	{
		if ( (*i)->GetDiosAdorado() == diosIzq )
		{
			izqMuerto = false ;
		}
		else if ( (*i)->GetDiosAdorado() == diosDer )
		{
			derMuerto = false ;
		}
	}

	if ( izqMuerto & derMuerto )
	{
		msgEmpate->SetVisible(true);
		enSecuencia = true ;
		ticksSecuencia = 10000000 ;

		camara->FocusOn(core::vector3df(), - core::vector3df(0,5,0));
	}
	else if ( izqMuerto )
	{
		msgGanoAzul->SetVisible(true);
		enSecuencia = true ;
		ticksSecuencia = 10000000 ;

		camara->FocusOn(diosDer->GetPosicion(), diosDer->GetPosicion() - core::vector3df(0,5,0));
	}
	else if ( derMuerto )
	{
		msgGanoRojo->SetVisible(true);
		enSecuencia = true ;
		ticksSecuencia = 10000000 ;

		camara->FocusOn(diosIzq->GetPosicion(), diosIzq->GetPosicion() - core::vector3df(0,5,0));
	}


}

void 
Partida::ActualizarDisparos()
{
	
	//Primero compruebo si chocan entre ellos
	list<Disparo *> tmp;
	for ( list<Disparo *>::iterator d1 = disparos.begin() ; d1 != disparos.end() ; ++d1 )
	{
		if((*d1)==NULL)
			continue;

		bool borrado=false;
		for ( list<Disparo *>::iterator d2 = disparos.begin() ; d2 != disparos.end() ; ++d2 )
		{
			if((*d2)==NULL || d1==d2)
				continue;
			if(CalcularColision((*d1)->GetPosicion(),(*d2)->GetPosicion(),2))
			{
				delete (*d1);
				(*d1)=NULL;
				delete (*d2);
				(*d2)=NULL;
				borrado=true;
				break;
			}
		}
		if(!borrado)
		{
			tmp.push_back((*d1));
		}
	}
	disparos.clear();
	disparos=tmp;


	tmp.clear();
	for ( list<Disparo *>::iterator d = disparos.begin() ; d != disparos.end() ; ++d )
	{
		//Eso para cuando tengo que volver a recorrer la lista cuando borro

		core::vector3df inf(0,0,0);
		//Primero compruebo si se salio de la pantalla
		core::vector3df pos=(*d)->GetPosicion();
		if ( pos.getLength() > 100 )
		{
			delete (*d);
			continue;
		}

		//Luego actualizo las fuerzas que le afectan y calculo si colisiona con alguien
		inf+=CalcularInfluencia(sol,(*d));
		if(CalcularColision((*d)->GetPosicion(),core::vector3df(0,0,0),3.2f))
		{
			delete (*d);
			continue;
		}

		bool choca=false;
		for ( list<Planeta *>::iterator p = planetas.begin() ; p != planetas.end() ; ++p )
		{
			inf+=CalcularInfluencia((*p),(*d));
			if(CalcularColision((*d)->GetPosicion(),(*p)->GetPosicion(),(*p)->GetRadio()))
			{
				bool retrasarImpacto = false ;
				if ( (*d)->GetEnergia() > 99.9f )
				{
					// Es un mega disparo
					if ( !enSecuencia )
					{
						// Y no estamos mostrando otro mega disparo
						PreColisionPlaneta(*p, (*d)->GetTipo() );
						retrasarImpacto = true ;
						tipoMegaImpacto = (*d)->GetTipo() ;
						planetaMegaImpacto = (*p) ;
					}
				}

				if (!retrasarImpacto)
				{
					(*p)->Impacto(*d);
				}

				delete (*d);
				choca=true;

				break;
			}
		}
		if(!choca)
		{
			(*d)->SetVelocidad((*d)->GetVelocidad()+inf);
			(*d)->Update();
			tmp.push_back((*d));
			*d=NULL;
		}
	}
	disparos.clear();
	disparos=tmp;

	if ( enSecuencia )
	{
		// Comprobamos la desactivacion de la secuncia
		ticksSecuencia--;
		if ( ticksSecuencia < 1 )
		{
			camara->FocusOn(core::vector3df(), core::vector3df(1,-40,0));
			enSecuencia = false ;
		}
		else if ( ticksSecuencia < 500 )
		{
			msgDiluvio->SetVisible(false);
			msgCalentamiento->SetVisible(false);
			msgArmaggeddon->SetVisible(false);
			this->MegaColisionPlaneta(planetaMegaImpacto, tipoMegaImpacto);
		}
	}

	// Camara
	camara->Update();
}

core::vector3df
Partida::CalcularInfluencia(Sol *s,Disparo *d)
{
	core::vector3df pos_s(0,0,0);
	core::vector3df pos_d = d->GetPosicion();

	// Primero se calcula el vector posicion del disparo respecto del sol
	core::vector3df inf;
	inf = pos_s - pos_d  ;
	inf.normalize();

	// Calculamos la distancia
	float dist = (float)pos_d.getDistanceFrom(pos_s);

	// Ahora se calcula el valor absoluto de la aceleracion
	float a = 0.000001f * (s->GetMasa() / dist*dist );

	// La influencia la multiplicamos por el valor absoluto
	inf *= a ;

	return inf;
}


core::vector3df
Partida::CalcularInfluencia(Planeta *s,Disparo *d)
{
	core::vector3df pos_s = s->GetPosicion();
	core::vector3df pos_d = d->GetPosicion();

	// Primero se calcula el vector posicion del disparo respecto del sol
	core::vector3df inf;
	inf = pos_s - pos_d  ;
	inf.normalize();

	// Calculamos la distancia
	float dist = pos_d.getDistanceFrom(pos_s);

	// Ahora se calcula el valor absoluto de la aceleracion
	float a = 0.000001f * (s->GetMasa() / dist*dist );

	// La influencia la multiplicamos por el valor absoluto
	inf *= a ;

	return inf;
}

bool
Partida::CalcularColision(core::vector3df a,core::vector3df b, float min_dist)
{
	f64 d=b.getDistanceFrom(a);
	
	if(d<min_dist)
		return true;
	return false;
}

void
Partida::PreColisionPlaneta(Planeta *planeta, int tipo)
{
	if ( !enSecuencia )
	{
		enSecuencia = true ;
		ticksSecuencia = 1000 ;

		camara->FocusOn(planeta->GetPosicion(), planeta->GetPosicion() - core::vector3df(0,5,0));

		switch (tipo)
		{
		case 1:
			msgCalentamiento->SetVisible(true);
			break;
		case 2:
			msgDiluvio->SetVisible(true);
			break;
		case 3:
			msgArmaggeddon->SetVisible(true);
			break;
		}
	}
}

Dios*
Partida::GetDios(int d)
{
	if(d==1)
		return diosIzq;
	else
		return diosDer;
}

void
Partida::MegaColisionPlaneta(Planeta *planeta, int tipo)
{
	switch (tipo)
	{
	case 1:
		planeta->CalentamientoGlobal();
		break;
	case 2:
		planeta->DiluvioUniversal();
		break;
	case 3:
		planeta->Armaggeddon();
		break;
	}
}

