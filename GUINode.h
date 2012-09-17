#pragma once
#include <irrlicht.h>
using namespace irr;
class GUINode :
	public irr::scene::ISceneNode
{
private:
	core::aabbox3d<irr::f32> box;
	float dios[2][3];

public:
	GUINode(scene::ISceneNode* parent, scene::ISceneManager* mgr,s32 id);
	virtual ~GUINode(void);
	virtual void OnPreRender();
	virtual void render();
	virtual const core::aabbox3d<irr::f32>& getBoundingBox() const
	{
		return box;
	}
	void UpdateValores(int god,float *poder);
};

