#include "Sol.h"

#include "Partida.h"
#include "SolNode.h"
#include "Juego.h"

Sol::Sol(Partida *partida, core::vector3df pos) : pos(pos)
{
	nodo = new SolNode(
		partida->GetNodo(),
		Juego::GetInstance()->GetSceneManager(),
		-1,
		3.0f);
	masa=1000.0f;
}

Sol::~Sol(void)
{
}

float
Sol::GetCalorEmitido(irr::core::vector3df pos)
{
	// Calculamos la distancia
	//pos.getDistanceFrom(pos);
	return 0.0f;
}

float
Sol::GetMasa()
{
	return masa;
}