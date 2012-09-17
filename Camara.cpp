#include "Camara.h"

#include "Partida.h"
#include "Juego.h"

Camara::Camara(Partida *partida) : partida(partida)
{
	nodo = Juego::GetInstance()->GetSceneManager()->addCameraSceneNode(partida->GetNodo());
	dtarget = core::vector3df(0,0,0);
	dpos = core::vector3df(1,-40,0);

	nodo->setTarget(dtarget); 
	nodo->setPosition(dpos);

}

Camara::~Camara(void)
{
}

void
Camara::FocusOn(core::vector3df target, core::vector3df pos)
{
	dtarget = target;
	dpos = pos;

	//nodo->setTarget(dtarget);
}


void
Camara::Update()
{
	core::vector3df actualPos = nodo->getPosition();
	actualPos = actualPos.getInterpolated(dpos, 0.99f);
	nodo->setPosition(actualPos);

	core::vector3df actualTarget = nodo->getTarget();
	actualTarget = actualTarget.getInterpolated(dtarget, 0.90f);
	nodo->setTarget(actualTarget);

	nodo->setUpVector(core::vector3df(1,0,0));
}

