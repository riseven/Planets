#include "DisparoNode.h"

#include "Juego.h"

using namespace irr;

DisparoNode::DisparoNode(scene::ISceneNode *parent, scene::ISceneManager *mgr, s32 id, float radio,core::vector3df pos,int tipo) 
		: scene::ISceneNode(parent, mgr, id), radio(radio),tipo(tipo)
{
	if(tipo==3)
	{
		irr::video::IVideoDriver *video=Juego::GetInstance()->GetVideoDriver();
		luz=mgr->addSphereSceneNode(radio/30,10,this);
		luz->setMaterialTexture(0, video->getTexture("data/roca.bmp"));
		luz->setMaterialFlag(video::EMF_LIGHTING, false);
		scene::ISceneNodeAnimator* anim = 
			Juego::GetInstance()->GetSceneManager()->createRotationAnimator(core::vector3df(0.1f, -0.5f, 0.4f));
		luz->addAnimator(anim);
		//luz->setMaterialType(irr::video::E_MATERIAL_TYPE::EMT_PARALLAX_MAP_SOLID);
		anim->drop();
	}
	else
		luz = mgr->addLightSceneNode(0, core::vector3df(0,0,0), 
			video::SColorf(1.0f, 0.2f, 0.2f, 0.0f), 10.0f);

	if(tipo!=3)
	{
		bill = mgr->addBillboardSceneNode(luz, core::dimension2d<f32>(radio/2, radio/2));
		bill->setMaterialFlag(video::EMF_LIGHTING, false);
		bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
		if(tipo==1)
			bill->setMaterialTexture(0, Juego::GetInstance()->GetVideoDriver()->getTexture("data/particlewhite.bmp"));
		else if(tipo==2)
			bill->setMaterialTexture(0, Juego::GetInstance()->GetVideoDriver()->getTexture("data/particleblue.bmp"));
	}
		// add particle system
		ps = 
			mgr->addParticleSystemSceneNode(false, luz);

		if(tipo!=3)
			ps->setParticleSize(core::dimension2d<f32>(radio/3, radio/3));
		else
			ps->setParticleSize(core::dimension2d<f32>(radio/5, radio/5));

		// create and set emitter
		scene::IParticleEmitter* em;
			em = ps->createBoxEmitter(
				core::aabbox3d<f32>(-1, 0.1f,0.1f, 1.1f, 0, 0),		//3 cord de origen, 3 de tamaño
				core::vector3df(0.0f,0.0f,0.0f),					//Cord direccion
				10,40,												//Min y max particulas segundo
				video::SColor(0,255,255,255), video::SColor(0,255,255,255),
				400,700);
		ps->setEmitter(em);
		em->drop();

		// create and set affector
		scene::IParticleAffector* paf = ps->createFadeOutParticleAffector();
		ps->addAffector(paf);
		paf->drop();

		// adjust some material settings
		ps->setMaterialFlag(video::EMF_LIGHTING, false);
		if(tipo==1)
			ps->setMaterialTexture(0, Juego::GetInstance()->GetVideoDriver()->getTexture("data/fireball.bmp"));
		else if(tipo==2)
			ps->setMaterialTexture(0, Juego::GetInstance()->GetVideoDriver()->getTexture("data/waterball.bmp"));
		else if(tipo==3)
			ps->setMaterialTexture(0, Juego::GetInstance()->GetVideoDriver()->getTexture("data/meteor.bmp"));
		ps->setMaterialType(video::EMT_TRANSPARENT_VERTEX_ALPHA);

	core::vector3df v;
	v.Z=-pos.Z;

	luz->setPosition(v);


	scene::ISceneNodeAnimator* anim = 
		Juego::GetInstance()->GetSceneManager()->createFlyStraightAnimator(pos,v,2000);
//Juego::GetInstance()->GetSceneManager()->createFlyCircleAnimator(core::vector3df(0,0,0),10);

	scene::ISceneNodeAnimator* anim2 = 
		Juego::GetInstance()->GetSceneManager()->createDeleteAnimator(2000);

	//luz->addAnimator(anim);
	//luz->addAnimator(anim2);
	anim->drop();
	anim2->drop();
}

DisparoNode::~DisparoNode(void)
{
}
void 
DisparoNode::Destruir(bool mega)
{
	if(!mega)
	{
		scene::ISceneNodeAnimator* anim2 = 
			Juego::GetInstance()->GetSceneManager()->createDeleteAnimator(1000);
		luz->addAnimator(anim2);
		anim2->drop();
	}
	else
	{
		ps->setParticleSize(core::dimension2d<f32>(radio/1.5, radio/1.5));
		//luz->setScale(core::vector3df(sc,sc,sc));
		scene::ISceneNodeAnimator* anim2 = 
			Juego::GetInstance()->GetSceneManager()->createDeleteAnimator(2500);
		luz->addAnimator(anim2);
		anim2->drop();
	}
}

void 
DisparoNode::render()
{
	video::IVideoDriver* driver = SceneManager->getVideoDriver();
	driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
}
