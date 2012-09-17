#include "SolNode.h"

#include "Juego.h"

using namespace irr;

SolNode::SolNode(scene::ISceneNode *parent, scene::ISceneManager *mgr, s32 id, float radio) 
		: scene::ISceneNode(parent, mgr, id), radio(radio), d_radio(radio)
	{
		this->setScale( core::vector3df(radio,radio,radio));

		material.AmbientColor = video::SColor::SColor(255,255,255,255);
		material.BackfaceCulling = true;
		material.DiffuseColor = video::SColor(255,255,255,255);
		material.GouraudShading = true;
		material.Lighting = true;
		material.Shininess = 0 ;
		material.Wireframe = false;
		material.ZBuffer = true;
		material.ZWriteEnable = true;

		/*
		material.EmissiveColor = video::SColor(255,255,0,0);

		material.MaterialType = video::E_MATERIAL_TYPE::EMT_SOLID;
		material.Texture1 = Juego::GetInstance()->GetVideoDriver()->getTexture("data/lava02.jpg");
		*/
		material.EmissiveColor = video::SColor(255,192,128,0);

		material.MaterialType = video::E_MATERIAL_TYPE::EMT_SOLID;
		material.Texture1 = Juego::GetInstance()->GetVideoDriver()->getTexture("data/lava01.jpg");

		this->setRotation( core::vector3df(0,0,90));

		scene::ISceneNode *s1 = Juego::GetInstance()->GetSceneManager()->addSphereSceneNode(1.2f, 16, this, -1);
		s1->getMaterial(0) = material;
		s1->getMaterial(0).MaterialType = video::E_MATERIAL_TYPE::EMT_TRANSPARENT_VERTEX_ALPHA;
		//s1->getMaterial(0).Texture1 = Juego::GetInstance()->GetVideoDriver()->getTexture("data/lava01.jpg");
		//s1->getMaterial(0).MaterialType = video::E_MATERIAL_TYPE::EMT_TRANSPARENT_VERTEX_ALPHA;
	
		scene::ISceneNodeAnimator* anim = 
			Juego::GetInstance()->GetSceneManager()->createRotationAnimator(core::vector3df(0.1f, -0.2f, 0.0f));
		s1->addAnimator(anim);
		anim->drop();


		scene::ISceneNode *s2 = Juego::GetInstance()->GetSceneManager()->addSphereSceneNode(1.3f, 16, this, -1);
		s2->getMaterial(0) = material;
		s2->getMaterial(0).MaterialType = video::E_MATERIAL_TYPE::EMT_TRANSPARENT_VERTEX_ALPHA;
		//s2->getMaterial(0).Texture1 = Juego::GetInstance()->GetVideoDriver()->getTexture("data/lava01.jpg");
		//s2->getMaterial(0).MaterialType = video::E_MATERIAL_TYPE::EMT_TRANSPARENT_VERTEX_ALPHA;
		
		scene::ISceneNodeAnimator* anim2 = 
			Juego::GetInstance()->GetSceneManager()->createRotationAnimator(core::vector3df(0.3f, -0.2f, 0.2f));
		s2->addAnimator(anim2);
		anim2->drop();

		float PI = 3.141592f;
		float EPSILON = 0.001f;

		// Generamos los vértices
		vertices = new video::S3DVertex[NUM_MERIDIANOS*(NUM_PARALELOS+1)];
		int nv = 0;
		int m=0,p=0;
		for (float theta = 0.0f ; theta < 2*PI - EPSILON ; theta += (2*PI) / NUM_MERIDIANOS )
		{
			p=0;
			for (float phi = -PI/2; phi < PI/2 + EPSILON; phi += (PI) / NUM_PARALELOS )
			{
				//vertices[nv] = video::S3DVertex(altura*cos(phi)*cos(theta), altura*sin(phi), altura*cos(phi)*sin(theta), cos(phi)*cos(theta), sin(phi), cos(phi)*sin(theta), video::SColor(255,(int)(255-altura*10),(int)(altura*10),0), theta , phi);
				vertices[nv] = video::S3DVertex(cos(phi)*cos(theta), sin(phi), cos(phi)*sin(theta), cos(phi)*cos(theta), sin(phi), cos(phi)*sin(theta), video::SColor(255,255,255,255), theta , phi);
				nv++;
				p++;
			}
			m++;
		}

		// Generamos los triangulos
		indices = new u16[NUM_PARALELOS*NUM_MERIDIANOS*2*3];
		int nTrig = 0 ;
		for ( int p = 0 ; p < NUM_PARALELOS ; p++ )
		{
			for ( int m = 0 ; m < NUM_MERIDIANOS ; m++ )
			{
				indices[nTrig*3+0] = m*(NUM_PARALELOS+1) + p ;
				indices[nTrig*3+1] = m*(NUM_PARALELOS+1) + ((p+1)%(NUM_PARALELOS+1));
				indices[nTrig*3+2] = ((m+1)%NUM_MERIDIANOS)*(NUM_PARALELOS+1) + p ;
				
				nTrig++;

				indices[nTrig*3+0] = m*(NUM_PARALELOS+1) + ((p+1)%(NUM_PARALELOS+1));
				indices[nTrig*3+1] = ((m+1)%NUM_MERIDIANOS)*(NUM_PARALELOS+1) + ((p+1)%(NUM_PARALELOS+1)) ;
				indices[nTrig*3+2] = ((m+1)%NUM_MERIDIANOS)*(NUM_PARALELOS+1) + p ;
				nTrig++;
			}
		}

		/*
		// Para cada triangulo
		for ( int trig = 0 ; trig < nTrig ; trig++ )
		{
			core::triangle3df t = core::triangle3df();
			t.set(vertices[ indices[trig*3+0] ].Pos,
				vertices[ indices[trig*3+1] ].Pos,
				vertices[ indices[trig*3+2] ].Pos);

			// Obtenemos la normal
			core::vector3df normal = t.getNormal();

			// Sumamos la normal a cada vertice
			vertices[ indices[trig*3+0] ].Normal += normal ;
			vertices[ indices[trig*3+1] ].Normal += normal ;
			vertices[ indices[trig*3+2] ].Normal += normal ;
		}

		// Normalizamos las normales
		for ( int i = 0 ; i < NUM_MERIDIANOS*(NUM_PARALELOS+1) ; i++ )
		{
			vertices[i].Normal.normalize();
		}
		*/

		// Calculamos el bounding box
		box.reset(vertices[0].Pos);
		for (s32 i=1; i<NUM_MERIDIANOS*(NUM_PARALELOS+1); ++i)
		{
			box.addInternalPoint(vertices[i].Pos);
		}
	}

SolNode::~SolNode(void)
{
}

void 
SolNode::OnPreRender()
{
	if (IsVisible)
	{
		SceneManager->registerNodeForRendering(this);
	}

	if ( radio < d_radio )
	{
		radio += 0.0001f ;
		if ( radio > d_radio )
		{
			radio = d_radio;
		}
	}
	else if ( radio > d_radio )
	{
		radio -= 0.0001f ;
		if ( radio < d_radio )
		{
			radio = d_radio;
		}
	}
	this->setScale(core::vector3df(radio,radio,radio));

	ISceneNode::OnPreRender();
}

void 
SolNode::render()
{
	video::IVideoDriver* driver = SceneManager->getVideoDriver();
	driver->setMaterial(material);
	driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
	driver->drawIndexedTriangleList(&vertices[0], NUM_MERIDIANOS*(NUM_PARALELOS+1), &indices[0], NUM_PARALELOS*NUM_MERIDIANOS*2);
}
