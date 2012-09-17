#include "GUINode.h"

#include "Juego.h"

using namespace irr;

GUINode::GUINode(scene::ISceneNode* parent, scene::ISceneManager* mgr,s32 id) 
	: scene::ISceneNode(parent, mgr, id)
{
	int i,j;
	for(i=0;i<2;i++)
		for(j=0;j<3;j++)
			dios[i][j]=20;
}

GUINode::~GUINode(void)
{
}
void 
GUINode::UpdateValores(int god,float *poder)
{
	dios[god][0]=poder[0];
	dios[god][1]=poder[1];
	dios[god][2]=poder[2];
}
void 
GUINode::OnPreRender()
{
	if (IsVisible)
	{
		SceneManager->registerNodeForRendering(this);
	}
}
void 
GUINode::render()
{
	video::IVideoDriver* driver = SceneManager->getVideoDriver();
	//Creo las 3 barras
	core::position2d<s32> m(20,20);
	driver->draw2DRectangle(video::SColor(255,0,0,200),
				core::rect<s32>(m.X, m.Y, m.X+dios[0][0], m.Y+10));
	m.Y+=12;
	driver->draw2DRectangle(video::SColor(255,200,10,10),
				core::rect<s32>(m.X, m.Y, m.X+dios[0][1], m.Y+10));
	m.Y+=12;
	driver->draw2DRectangle(video::SColor(255,200,250,0),
				core::rect<s32>(m.X, m.Y, m.X+dios[0][2], m.Y+10));

	//Para los dos dioses
	m.X=700;
	m.Y=20;
	driver->draw2DRectangle(video::SColor(255,0,0,200),
				core::rect<s32>(m.X-dios[1][0], m.Y, m.X, m.Y+10));
	m.Y+=12;
	driver->draw2DRectangle(video::SColor(255,200,10,10),
				core::rect<s32>(m.X-dios[1][1], m.Y, m.X, m.Y+10));
	m.Y+=12;
	driver->draw2DRectangle(video::SColor(255,200,250,0),
				core::rect<s32>(m.X-dios[1][2], m.Y, m.X, m.Y+10));
}
