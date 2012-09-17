#pragma once

#include "MarNode.h"
#include "AtmosferaNode.h"


#include <irrlicht.h>
using namespace irr;

class MarNode;
class AtmosferaNode;

class PlanetaNode :
	public irr::scene::ISceneNode
{
private:
	irr::core::aabbox3d<irr::f32> box;
	irr::video::S3DVertex *vertices;
	irr::video::SMaterial material;
	irr::u16 *indices ;

	static const int NUM_PARALELOS = 25;
	static const int NUM_MERIDIANOS = 50;

	MarNode *mar ;
	AtmosferaNode *atmosfera;

public:
	PlanetaNode(irr::scene::ISceneNode* parent, irr::scene::ISceneManager* mgr, irr::s32 id, irr::core::vector3df pos);
	virtual ~PlanetaNode(void);
	virtual void OnPreRender();
	virtual void render();

	virtual const irr::core::aabbox3d<irr::f32>& getBoundingBox() const
	{
		return box;
	}

	virtual irr::s32 getMaterialCount()
	{
		return 1;
	}

	virtual irr::video::SMaterial& getMaterial(irr::s32 i)
	{
		return material;
	}	

	void SetAlturaMar(float h)
	{
		mar->SetRadio( 0.9f + h*0.2f );
	}

	void SetColorAtmosfera(video::SColor c)
	{
		atmosfera->SetDesColor(c);
	}

	void SetColorTerreno(video::SColor c);
	
};
