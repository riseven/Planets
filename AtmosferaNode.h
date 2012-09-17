#pragma once
#include <irrlicht.h>

using namespace irr;

class AtmosferaNode :
	public irr::scene::ISceneNode
{
private:
	irr::core::aabbox3d<irr::f32> box;
	irr::video::S3DVertex *vertices;
	irr::video::SMaterial material;
	irr::u16 *indices ;
	irr::video::SColor color;
	irr::video::SColor dcolor;

	static const int NUM_PARALELOS = 15;
	static const int NUM_MERIDIANOS = 30;
	int NUM_VERTICES;
	int NUM_INDICES;

public:
	AtmosferaNode(irr::scene::ISceneNode* parent, irr::scene::ISceneManager* mgr, irr::s32 id);
	virtual ~AtmosferaNode(void);

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

	video::SColor GetDesColor()
	{
		return dcolor;
	}

	video::SColor GetColor()
	{
		return color;
	}

	void SetColor(video::SColor c)
	{
		color = c ;
	}

	void SetDesColor(video::SColor c)
	{
		dcolor = c;
	}
};

