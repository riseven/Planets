#pragma once

#include <irrlicht.h>
using namespace irr;

class Teclado : public IEventReceiver
{
private:
	bool *keyState;
	bool *keyDown;

public:
	Teclado(void);
	virtual ~Teclado(void);
	virtual bool OnEvent(SEvent event);
	bool Key(irr::EKEY_CODE code);
	bool KeyDown(irr::EKEY_CODE code);
	void Update();
};
