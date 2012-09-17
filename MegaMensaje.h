#pragma once

#include <irrlicht.h>
using namespace irr;

class MegaMensaje
{
private:
	gui::IGUIImage *nodo;

public:
	MegaMensaje(c8* file);
	virtual ~MegaMensaje(void);

	void SetVisible(bool visible);
};
