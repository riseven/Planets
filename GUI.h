#pragma once

#include <irrlicht.h>
using namespace irr;
#include "GUINode.h"
class GUINode;
class GUI
{
private:
	GUINode *nodo;
	Dios *d1,*d2;

public:
	GUI(Partida *partida)
	{
		nodo=new GUINode(partida->GetNodo(), 
			Juego::GetInstance()->GetSceneManager(),3);
		d1=partida->GetDios(1);
		d2=partida->GetDios(2);
	};
	~GUI(void){};

	void Update()
	{
		this->nodo->UpdateValores(0,d1->GetPoder());
		this->nodo->UpdateValores(1,d2->GetPoder());
	};
};
