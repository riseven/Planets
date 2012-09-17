#include "MegaMensaje.h"

#include "Juego.h"

MegaMensaje::MegaMensaje(c8 *file)
{
	video::ITexture * textura = Juego::GetInstance()->GetVideoDriver()->getTexture(file);

	nodo = 	Juego::GetInstance()->GetGui()->addImage(
		textura,
		core::position2d<s32>(0,0),
		true,
		Juego::GetInstance()->GetGui()->getRootGUIElement(),
		-1);

	int w = Juego::GetInstance()->GetVideoDriver()->getScreenSize().Width;
	int h = Juego::GetInstance()->GetVideoDriver()->getScreenSize().Height;
	
	int iw = textura->getSize().Width;
	int ih = textura->getSize().Height;
	
	core::rect<s32> rect( (w-iw)/2, (h-ih)/2 , (w-iw)/2 + iw , (h-ih)/2 + ih );
	nodo->setRelativePosition( rect );

	nodo->setVisible(false);
}

MegaMensaje::~MegaMensaje(void)
{
}

void
MegaMensaje::SetVisible(bool visible)
{
	nodo->setVisible(visible);
}
