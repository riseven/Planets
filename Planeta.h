#pragma once

#include <irrlicht.h>
using namespace irr;

class Dios;
class PlanetaNode;
class Disparo;

class Planeta
{
private:
	float poblacion; // 0..1
	float calor; // 0..1
	float agua; // 0..1
	PlanetaNode *nodo;
	Dios *diosAdorado;
	float devocion; // 0..1
	float masa;
	core::vector3df pos;


protected:
public:
	// Solo se distingue su comportamiento en que si el numero de devotos llega a 
	// cero, con AddDevotos el planeta se convierte en neutro, y con AddHerejes
	// se pasan al otro dios
	void CalcularCambioDevocion(float durezaAntigua, float durezaNueva, Dios *dios);
	void AddDevotos(float dev);
	void AddHerejes(float dev, Dios *dios);
	void ColorearAtmosfera();
	

public:
	Planeta(void);
	virtual ~Planeta(void);

	void DiluvioUniversal();
	void Armaggeddon();
	void CalentamientoGlobal();
	void Impacto(Disparo *d);
	void ImpactoCalor(float cant, Dios *dios);
	void ImpactoAgua(float cant, Dios *dios);
	void ImpactoMeteorito(float cant, Dios *dios);
	Dios *GetDiosAdorado()
	{
		return diosAdorado;
	}

	float GetPoblacion();
	float GetCalor();
	float GetAgua();
	float GetMasa();
	float GetRadio();

	core::vector3df GetPosicion();
	void SetPosicion(core::vector3df);

	void Update();	
};
