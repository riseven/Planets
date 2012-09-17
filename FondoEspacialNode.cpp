#include "FondoEspacialNode.h"

#include "Juego.h"

using namespace irr;

FondoEspacialNode::FondoEspacialNode(scene::ISceneNode *parent, scene::ISceneManager *mgr, s32 id) 
	: scene::ISceneNode(parent, mgr, id)
	{
		this->setScale(core::vector3df(1000.0f,1000.0f,1000.0f));
		this->setRotation(core::vector3df(90.0f, 90.0f, 0.0f));

		material.AmbientColor = video::SColor::SColor(255,255,0,0);
		material.BackfaceCulling = false;
		material.DiffuseColor = video::SColor(255,255,0,0);
		material.GouraudShading = true;
		material.Lighting = true;
		material.Shininess = 0 ;
		material.Wireframe = false;
		material.ZBuffer = true;
		material.ZWriteEnable = true;
		material.EmissiveColor = video::SColor(255,96,0,96);
		
		//material.MaterialType = video::E_MATERIAL_TYPE::EMT;
		//material.MaterialType = video::EMT_TRANSPARENT_ALPHA_CHANNEL;

		//Juego::GetInstance()->GetVideoDriver()->setTextureCreationFlag(video::ETCF_ALWAYS_32_BIT, true);		
		//Juego::GetInstance()->GetVideoDriver()->setAmbientLight(video::SColorf(1,1,1,1));

		//material.Textures[0] = Juego::GetInstance()->GetVideoDriver()->getTexture("espacio2.jpg");
		material.Textures[0] = Juego::GetInstance()->GetVideoDriver()->getTexture("data/water.jpg");



		float PI = 3.141592f;
		float EPSILON = 0.001f;

		// Generamos los vértices
		NUM_VERTICES = (NUM_MERIDIANOS+1)*(NUM_PARALELOS+1);

		vertices = new video::S3DVertex[NUM_VERTICES];
		int nv = 0;
		int m=0,p=0;
		for (float theta = 0.0f ; theta < 2*PI + EPSILON ; theta += (2*PI) / NUM_MERIDIANOS )
		{
			p=0;
			for (float phi = -PI/2; phi < PI/2 + EPSILON; phi += (PI) / NUM_PARALELOS )
			{
				vertices[nv] = video::S3DVertex(cos(phi)*cos(theta), sin(phi), cos(phi)*sin(theta), cos(phi)*cos(theta), sin(phi), cos(phi)*sin(theta), video::SColor(0,255,255,255), theta/(2*PI) , phi/PI);
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
				indices[nTrig*3+1] = m*(NUM_PARALELOS+1) + ((p+1));
				indices[nTrig*3+2] = ((m+1))*(NUM_PARALELOS+1) + p ;
				
				
				nTrig++;

				indices[nTrig*3+0] = m*(NUM_PARALELOS+1) + ((p+1));
				indices[nTrig*3+1] = ((m+1))*(NUM_PARALELOS+1) + ((p+1)) ;
				indices[nTrig*3+2] = ((m+1))*(NUM_PARALELOS+1) + p ;
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
		for (s32 i=1; i<NUM_VERTICES; ++i)
		{
			box.addInternalPoint(vertices[i].Pos);
		}
	}

FondoEspacialNode::~FondoEspacialNode(void)
{
}

void 
FondoEspacialNode::OnPreRender()
{
	if (IsVisible)
	{
		SceneManager->registerNodeForRendering(this);
	}

	ISceneNode::OnPreRender();
}

void 
FondoEspacialNode::render()
{
	video::IVideoDriver* driver = SceneManager->getVideoDriver();
	driver->setMaterial(material);
	driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
	driver->drawIndexedTriangleList(&vertices[0], NUM_VERTICES, &indices[0], NUM_PARALELOS*NUM_MERIDIANOS*2);
}
