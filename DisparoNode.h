#pragma once
#include <irrlicht.h>
using namespace irr;
class DisparoNode :
	public scene::ISceneNode
{
private:
	core::aabbox3d<irr::f32> box;
	scene::ISceneNode *bill,*luz;
	scene::IParticleSystemSceneNode* ps;
	float radio;
	int tipo;
public:
	DisparoNode(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id, float radio,core::vector3df pos,int tipo);
	virtual ~DisparoNode(void);

	virtual void render();

	virtual const core::aabbox3d<irr::f32>& getBoundingBox() const
	{
		return box;
	}
	void SetPosicion(core::vector3df pos)
	{
		luz->setPosition(pos);
	}
	void Destruir(bool mega);
};
