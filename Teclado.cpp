#include "Teclado.h"

Teclado::Teclado(void)
{
	keyState = new bool[ KEY_KEY_CODES_COUNT ];
	keyDown = new bool[ KEY_KEY_CODES_COUNT ];
	for ( int i = 0 ; i < KEY_KEY_CODES_COUNT ; i++ )
	{
		keyState[i] = false ;
		keyDown[i] = false ;
	}
}

Teclado::~Teclado(void)
{
	if ( keyState )
	{
		delete keyState;
		delete keyDown;
		keyState = NULL ;
		keyDown = NULL;
	}
}

bool 
Teclado::OnEvent(SEvent event)
{
	if (event.EventType == irr::EET_KEY_INPUT_EVENT)
	{
		if ( event.KeyInput.PressedDown )
		{
			if ( !keyState[ event.KeyInput.Key ] )
			{
				keyDown[ event.KeyInput.Key ] = true;
				keyState[ event.KeyInput.Key ] = true ;
			}
		}
		else
		{
			keyState[ event.KeyInput.Key ] = false ;
		}
	}

	return false;
}

bool
Teclado::Key(irr::EKEY_CODE code)
{
	return keyState[code];
}

bool
Teclado::KeyDown(irr::EKEY_CODE code)
{
	return keyDown[code];
}

void
Teclado::Update()
{
	for ( int i = 0 ; i < irr::KEY_KEY_CODES_COUNT ; i++ )
	{
		keyDown[i] = false ;
	}
}
