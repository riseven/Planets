
#include <irrlicht.h>
#include "PlanetaNode.h"
#include "Partida.h"
#include <math.h>
#include <time.h>
#include <iostream>

using namespace irr;

#pragma comment(lib, "Irrlicht.lib")



/*
Here comes the most sophisticated part of this tutorial: 
The class of our very own custom scene node. To keep it simple,
our scene node will not be an indoor portal renderer nor a terrain
scene node, but a simple tetraeder, a 3d object consiting of 4
connected vertices, which only draws itself and does nothing more.

To let our scene node be able to be inserted into the Irrlicht 
Engine scene, the class we create needs only be derived from the
ISceneNode class and has to override some methods.
*/


#include "Juego.h"

/*
That's it. The Scene node is done. Now we simply have to start
the engine, create the scene node and a camera, and look at the result.
*/
int main()
{
	Juego::GetInstance()->Run();
	return 0;
}

