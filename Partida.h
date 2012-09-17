#pragma once

#include "Pantalla.h"
#include "PlanetaNode.h"
#include "Disparo.h"

#include <irrlicht.h>
#include <list>
using namespace std;

class SolNode;
class Sol;
class DisparoNode;
class Disparo;
class Planeta;
class Dios;
class GUI;
class FondoEspacialNode;
class Camara;
class MegaMensaje;

class Partida : public Pantalla
{
private:
	// Sol
	Sol* sol;
	GUI* gui;

	// Planetas
	list<Planeta *> planetas ;

	//Disparos
	list<Disparo *> disparos ;

	// Dioses
	Dios *diosIzq;
	Dios *diosDer;

	// Fondo espacial
	FondoEspacialNode *fondo;

	// Camara
	Camara *camara;

	// Mega mensajes
	MegaMensaje *msgDiluvio;
	MegaMensaje *msgArmaggeddon;
	MegaMensaje *msgCalentamiento;

	// Mensajes de final de partida
	MegaMensaje *msgEmpate;
	MegaMensaje *msgGanoRojo;
	MegaMensaje *msgGanoAzul;

	bool enSecuencia;
	int ticksSecuencia;
	int tipoMegaImpacto;
	Planeta *planetaMegaImpacto;



protected:
	void Inicializar();
	void InicializarSistema();
	void InicializarDioses();
	void InicializarFondo();
	void InicializarIluminacion();
	void InicializarGUI();
	void InicializarCamara();
	void InicializarMegaMensajes();
	void ActualizarDisparos();
	// ...

public:
	Partida();
	virtual ~Partida(void);
	virtual void Activar();
	virtual void Desactivar();
	virtual void Update();
	
	Dios* GetDios(int d);
	void CrearDisparo(core::vector3df pos,float valor,int tipo,Dios *dios);
	core::vector3df CalcularInfluencia(Sol *s,Disparo *d);
	core::vector3df CalcularInfluencia(Planeta *p,Disparo *d);
	bool CalcularColision(core::vector3df pos_p,core::vector3df pos_d, float radio);
	void PreColisionPlaneta(Planeta *planeta, int tipo);
	void MegaColisionPlaneta(Planeta *planeta, int tipo);

};
