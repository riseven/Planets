#include "AtmosferaNode.h"

#include "Juego.h"

using namespace irr;

AtmosferaNode::AtmosferaNode(scene::ISceneNode *parent, scene::ISceneManager *mgr, s32 id) 
	: scene::ISceneNode(parent, mgr, id)
	{
		this->setScale(core::vector3df(1.3f,1.3f,1.3f));

		color = video::SColor(0,0,0,0);
		dcolor = color;

		material.AmbientColor = video::SColor::SColor(255,255,0,0);
		material.BackfaceCulling = true;
		material.DiffuseColor = video::SColor(255,255,0,0);
		material.GouraudShading = true;
		material.Lighting = true;
		material.Shininess = 0 ;
		material.Wireframe = false;
		material.ZBuffer = true;
		material.ZWriteEnable = false;
		material.EmissiveColor = video::SColor(255,128,0,128);
		
		material.MaterialType = video::EMT_TRANSPARENT_VERTEX_ALPHA;
		//material.MaterialType = video::E_MATERIAL_TYPE::EMT_SOLID;
		//material.MaterialType = video::EMT_TRANSPARENT_ALPHA_CHANNEL;

		//Juego::GetInstance()->GetVideoDriver()->setTextureCreationFlag(video::ETCF_ALWAYS_32_BIT, true);		
		//Juego::GetInstance()->GetVideoDriver()->setAmbientLight(video::SColorf(1,1,1,1));

		material.Textures[0] = Juego::GetInstance()->GetVideoDriver()->getTexture("data/aire.jpg");
		//material.Textures[0] = Juego::GetInstance()->GetVideoDriver()->getTexture("water.jpg");

		NUM_VERTICES = (NUM_MERIDIANOS+1)*(NUM_PARALELOS+1);
		NUM_INDICES = NUM_MERIDIANOS*NUM_PARALELOS*2*3;



		float PI = 3.141592f;
		float EPSILON = 0.001f;

		// Generamos los vértices
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
		indices = new u16[NUM_INDICES];
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

AtmosferaNode::~AtmosferaNode(void)
{
}

void 
AtmosferaNode::OnPreRender()
{
	if (IsVisible)
	{
		SceneManager->registerNodeForRendering(this);
	}

	int inc = 1;
	if ( dcolor.getBlue() != color.getBlue() )
	{
		u32 dc = dcolor.getBlue();
		u32 c = color.getBlue();

		if (abs((int)(dc-c)) < inc )
		{
			c = dc ;
		}
		else
		{
			c += dc > c ? inc : -inc ;
		}
		color.setBlue(c);
	}

	if ( dcolor.getRed() != color.getRed() )
	{
		u32 dc = dcolor.getRed();
		u32 c = color.getRed();

		if (abs((int)(dc-c)) < inc )
		{
			c = dc ;
		}
		else
		{
			c += dc > c ? inc : -inc ;
		}
		color.setRed(c);
	}

	if ( dcolor.getGreen() != color.getGreen() )
	{
		u32 dc = dcolor.getGreen();
		u32 c = color.getGreen();

		if (abs((int)(dc-c)) < inc )
		{
			c = dc ;
		}
		else
		{
			c += dc > c ? inc : -inc ;
		}
		color.setGreen(c);
	}

	material.EmissiveColor = color ;

	ISceneNode::OnPreRender();
}

void 
AtmosferaNode::render()
{
	video::IVideoDriver* driver = SceneManager->getVideoDriver();
	driver->setMaterial(material);
	driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
	driver->drawIndexedTriangleList(&vertices[0], NUM_VERTICES, &indices[0], NUM_INDICES/3);
}
