#include "Pantalla.h"

#include "Juego.h"

Pantalla::Pantalla(void)
{
	nodo = Juego::GetInstance()->GetSceneManager()->addEmptySceneNode(
		Juego::GetInstance()->GetSceneManager()->getRootSceneNode());
}

Pantalla::~Pantalla(void)
{
}
