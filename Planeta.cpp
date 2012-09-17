#include "Planeta.h"

#include "Juego.h"
#include "PlanetaNode.h"
#include "Dios.h"
#include "Disparo.h"

Planeta::Planeta(void)
{
	diosAdorado = NULL;
	calor = 0.5f;
	agua = 0.45f;
	int radio=1;
	masa=100.0f;
	devocion = 0.0f ;
	poblacion = 0.0f ;

	nodo = new PlanetaNode(
		Juego::GetInstance()->GetSceneManager()->getRootSceneNode(), 
		Juego::GetInstance()->GetSceneManager(), 
		0, 
		core::vector3df::vector3d());

	nodo->setRotation(core::vector3df(30.0f, 0.0f, 90.0f));
	nodo->setScale(core::vector3df(2.0,2.0,2.0));
	nodo->SetAlturaMar(0.5f);
	//nodo->SetColorAtmosfera(video::SColor(0,96,96,0));
	//nodo->SetColorAtmosfera(video::SColor(0,192,0,0));

	scene::ISceneNodeAnimator* anim = 
		Juego::GetInstance()->GetSceneManager()->createRotationAnimator(core::vector3df(0.0f, -0.2f, 0.0f));

	nodo->addAnimator(anim);

	anim->drop();
}

Planeta::~Planeta(void)
{
}

void
Planeta::ColorearAtmosfera()
{
	if ( diosAdorado != NULL )
	{
		video::SColorf colorDios = diosAdorado->GetColorAtmosfera();
		//colorDios.r *= 0.5f+(devocion/2.0f);
		//colorDios.g *= 0.5f+(devocion/2.0f);
		//colorDios.b *= 0.5f+(devocion/2.0f);

		nodo->SetColorAtmosfera(colorDios.toSColor());
	}
	else
	{
		nodo->SetColorAtmosfera( video::SColor(255,0,0,0) );
	}
}

void
Planeta::AddDevotos(float dev)
{
	devocion += dev ;
	if ( devocion > 1.0f )
	{
		devocion = 1.0f ;
	}
	else if ( devocion < 0.0f )
	{
		devocion = 0.0f ;
		diosAdorado = NULL ;
	}
	ColorearAtmosfera();
}

void
Planeta::AddHerejes(float dev, Dios *dios)
{
	devocion -= dev;
	if ( devocion > 1.0f )
	{
		devocion = 1.0f ;
	}
	else if ( devocion < 0.0f )
	{
		devocion = -devocion ;
		diosAdorado = dios ;
	}
	ColorearAtmosfera();
}

void
Planeta::Impacto(Disparo *d)
{
	switch(d->GetTipo())
	{
	case 1:
		ImpactoCalor(d->GetEnergia()/100,d->GetDios());
		break;
	case 2:
		ImpactoAgua(d->GetEnergia()/100,d->GetDios());
		break;
	case 3:
		ImpactoMeteorito(d->GetEnergia()/100,d->GetDios());
		break;
	default:
		printf("Que coño es esto!\n");
		break;
	}
}

void
Planeta::DiluvioUniversal()
{
	this->ImpactoAgua(1.0f, NULL);

	diosAdorado = NULL;
	devocion = 0 ;
	poblacion = 0 ;

	ColorearAtmosfera();
}

void
Planeta::CalentamientoGlobal()
{
	this->ImpactoCalor(1.0f, NULL);

	diosAdorado = NULL;
	devocion = 0;
	poblacion = 0 ;

	ColorearAtmosfera();
}

void
Planeta::Armaggeddon()
{
	this->ImpactoMeteorito(1.0f, NULL);

	diosAdorado = NULL;
	devocion = 0 ;
	poblacion = 0 ;

	ColorearAtmosfera();
}

void
Planeta::CalcularCambioDevocion(float dureza, float ndureza, Dios *dios)
{
	if ( dios == NULL )
	{
		return;
	}

	if ( ndureza > dureza )
	{
		if ( dios == diosAdorado )
		{
			// No les gusta que su dios les castigue
			AddDevotos( -(ndureza-dureza) );
		}
	}
	else
	{
		if ( dios == diosAdorado )
		{
			// Viva nuestro dios
			AddDevotos( dureza-ndureza );
		}
		else
		{
			// Este otro dios tampoco está nada mal
			AddHerejes( dureza-ndureza, dios );
		}
	}
}

void
Planeta::ImpactoCalor(float cant, Dios *dios)
{
	// Guardamos el valor de dureza
	float dureza = fabs(calor - 0.5f);

	calor += cant ;
	if ( calor > 1.0f )
	{
		calor = 1.0f;
	}
	else if ( calor < 0.0f )
	{
		calor = 0.0f;
	}

	// Comprobamos si ha sido para bien o para mal
	float ndureza = fabs(calor - 0.5f);
	CalcularCambioDevocion(dureza, ndureza, dios);
}

void
Planeta::ImpactoAgua(float cant, Dios *dios)
{
	// Guardamos el valor de dureza
	float dureza = fabs(agua - 0.5f);

	agua += cant;
	if ( agua > 1.0f )
	{
		agua = 1.0f ;
	}
	else if ( agua < 0.0f )
	{
		agua = 0.0f ;
	}
	nodo->SetAlturaMar(agua);

	// Comprobamos si ha sido para bien o para mal
	float ndureza = fabs(agua - 0.5f);
	CalcularCambioDevocion(dureza, ndureza, dios);
}

void
Planeta::ImpactoMeteorito(float cant, Dios *dios)
{
	poblacion -= cant ;
	if ( poblacion < 0.0f )
	{
		poblacion = 0.0f ;
	}

	CalcularCambioDevocion(0, cant, dios);
}

float
Planeta::GetCalor()
{
	return calor;
}

float
Planeta::GetAgua()
{
	return agua;
}

float
Planeta::GetPoblacion()
{
	return poblacion;
}

float
Planeta::GetMasa()
{
	return masa;
}

float
Planeta::GetRadio()
{
	return 2.2f;
}

core::vector3df
Planeta::GetPosicion()
{
	return nodo->getPosition();
}

void
Planeta::SetPosicion(irr::core::vector3df posicion)
{
	pos=posicion;
	nodo->setPosition(posicion);
}

void
Planeta::Update()
{
	// Reducimos el nivel de agua de forma proporcional al calor
	this->ImpactoAgua(-calor*0.0001f, NULL);

	// Reducimos el calor de forma constante
	this->ImpactoCalor(-0.00005f, NULL);

	// Mostramos los cambios en el planeta
	nodo->SetAlturaMar(agua);
	// TODO: Cambio de calor
	video::SColor colorDesierto(255,255,128,0);
	video::SColor colorHierba(255,0,255,0);
	video::SColor colorNieve(255,128,128,255);

	video::SColor colorTerreno;
	if ( calor < 0.5f )
	{
		colorTerreno = colorHierba.getInterpolated(colorNieve, calor*2.0f);
	}
	else
	{
		colorTerreno = colorDesierto.getInterpolated(colorHierba, (calor-0.5f)*2.0f);
	}

	nodo->SetColorTerreno(colorTerreno);

	// Comprobamos los cambios de poblacion
	core::vector2df dureza( calor-0.5f, agua-0.5f );
	float dpob = 1.0f - dureza.getLength() ;

	if ( poblacion > dpob )
	{
		poblacion -= 0.01f;
	}
	else if ( poblacion < dpob )
	{
		poblacion += 0.01f;
	}
	if ( poblacion < 0.0f )
	{
		poblacion = 0.0f ;
	}
	else if ( poblacion > 1.0f )
	{
		poblacion = 1.0f ;
	}

	//Por ultimo le incrementamos la energia al dios adorado
	if(diosAdorado!=NULL)
		diosAdorado->AddPoder(devocion*poblacion*0.1f);
	

	// Giramos el planeta
	core::vector3df pos = nodo->getPosition();
	pos.rotateXZBy(0.01f, core::vector3df());
	nodo->setPosition(pos);
}
