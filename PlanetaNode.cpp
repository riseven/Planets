#include "PlanetaNode.h"

#include "MarNode.h"
#include "AtmosferaNode.h"
#include "Juego.h"

#include <stdlib.h>
#include <list>
using namespace std;
using namespace irr;

PlanetaNode::PlanetaNode(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id, core::vector3df pos) : 
	scene::ISceneNode(parent, mgr, id)
{
	setPosition(pos);

	// Creamos el mar
	mar = new MarNode(this, mgr,-1,1);
	atmosfera = new AtmosferaNode(this, mgr, -1);

	material.AmbientColor = video::SColor::SColor(255,255,255,255);
	material.BackfaceCulling = true;
	material.DiffuseColor = video::SColor(255,0,192,0);
	material.GouraudShading = true;
	material.Lighting = true;
	material.Wireframe = false;
	material.ZBuffer = true;
	material.ZWriteEnable = true;
	material.Shininess = 0;

	float PI = 3.141592f;
	float EPSILON = 0.001f;

	// Generamos el mapa de alturas
	float **alturas = new float *[NUM_MERIDIANOS];
	for ( int i = 0 ; i < NUM_MERIDIANOS ; ++i )
	{
		alturas[i] = new float[NUM_PARALELOS+1];
	}
	for ( int m = 0 ; m < NUM_MERIDIANOS ; ++m )
	{
		for ( int p = 0 ; p < NUM_PARALELOS+1 ; ++p )
		{
			alturas[m][p] = 10.0f ;
			/*
			if ( p == 0 || p == NUM_PARALELOS+1 )
			{
				alturas[m][p] = 10.0f ;
			}
			else
			{
				alturas[m][p] = 8.0f + (rand()%400)/100.0f ;
			}
			*/
		}
	}

	// Generamos los puntos fijos de la orografia
	typedef pair<core::vector3df, float> PuntoFijo ;
	list< PuntoFijo > puntosFijos;
	for (int i = 0 ; i < 50 ; i++)
	{
		// Calculamos la altura al azar
		float h = 10.0f+((((rand()%400)/100.0f)-2.0f)*1.0f);

		// Calculamos las coordeandas cilindricas al azar
		// TODO: Tener en cuenta que la probabilidad en los polos debe ser menor
		float theta = (rand()%((int)(2*PI*1000)))/1000.0f ;
		float phi = (rand()%((int)(PI*1000)))/1000.0f ;
		//float phi = pow((rand()%1000)/1000.0f, 2.0f)*2*PI ;

		// Calculamos las coordenadas cartesianas asociadas
		float x = cos(theta)*sin(phi) ;
		float y = cos(phi);
		float z = sin(theta)*sin(phi) ;

		// Guardamos el punto fijo
		puntosFijos.push_back(PuntoFijo(core::vector3df(x, y, z), h));
	}

	// Generamos la orografia
	for (int m = 0 ; m < NUM_MERIDIANOS ; m++ )
	{
		for (int p = 0 ; p < NUM_PARALELOS+1 ; p++ )
		{
			// Calculamos las coordenadas esféricas de este punto
			float theta = 2*PI*m/NUM_MERIDIANOS ;
			float phi = -PI/2 + PI*p/NUM_PARALELOS ;

			// Calculamos las cooredanadas cartesianas de este punto
			float x = cos(theta)*sin(phi);
			float y = cos(phi);
			float z = sin(theta)*sin(phi) ;

			// Inicializamos su altura a 0
			float h = 0.0f ;

			// Calculamos la distancia cuadrática a cada punto fijo, 
			// y la altura del mismo
			list<core::vector2df> relacionPuntosFijos ;

			// Y guardamos la suma de distancias para normalizar
			float suma = 0.0f ;
			for ( list<PuntoFijo>::iterator i = puntosFijos.begin() ; i != puntosFijos.end() ; ++i )
			{
				// Obtenemos las coordenadas del punto fijo y su altura
				float fx = i->first.X;
				float fy = i->first.Y;
				float fz = i->first.Z;
				float fh = i->second;

				// Calculamos la distancia cuadrática euclidea al punto fijo
				float d2 = (x-fx)*(x-fx) + (y-fy)*(y-fy) + (z-fz)*(z-fz) ;

				// Lo guardamos todo en la lista de relacion
				relacionPuntosFijos.push_back(core::vector2df(1.0/d2,fh));

				// Añadimos la distancia a la suma
				suma += 1.0f/d2 ;
			}
			
			// Normalizamos el vector con norma euclidea (lo mas normal sería utilizar
			// norma del valor absoluto, ya que normalizando con norma euclidea ocurren
			// cosas raras, como que la altura de un punto cercano a dos puntos fijos sea
			// máxima en el punto equidistante a los dos puntos fijos, formando una especie
			// de montaña redondeada... espera, eso me gusta... por eso utilizo norma
			// euclidea)
			//suma = sqrt(suma);
			for ( list<core::vector2df>::iterator i = relacionPuntosFijos.begin(); i != relacionPuntosFijos.end() ; ++i )
			{
				//i->X = sqrt(i->X)/suma ;
				//float f = i->X / suma ;
				i->X /= suma;

				// Y vamos aprovechando para calcular la altura
				h += i->Y * i->X ;
			}

			alturas[m][p] = h ;
		}
	}

	/*
	// Generamos la orografía
	for (int i = 0 ; i < 1000 ; i++ )
	{
		// Centro de la montaña
		int cm = rand()%NUM_MERIDIANOS ;
		int cp = (rand()%(NUM_PARALELOS-1))+1 ;

		// Fuerza 
		float fz = (((rand()%200)/100.0f)-1.0f)*0.1f ;

		// Según la resolución, el radio de influencia, y el decaimiento varian
		int radio = NUM_MERIDIANOS / 3 ;

		// Recorremos cada celda aplicando la fuerza
		for ( int ip = -radio ; ip <= radio ; ip++ )
		{
			for ( int im = -radio ; im <= radio ; im++ )
			{
				// Calculamos la distancia euclídea (cuidado, el espacio es anisotropo)
				// La calculamos al cuadrado, nos evitamos la raiz, ya que como el
				// decaimiento es cuadrático, es dist^2 lo que necesitamos
				float dist2 = (float)(im*im/(radio*radio) + ip*ip/(radio*radio)) ;

				// Calculamos la fuerza para este punto
				float lfz = dist2==0 ? fz*3/2 : fz / dist2 ;

				// Calculamos las coordeandas del cambio
				int m = (cm + im);
				int p = (cp + ip);
				if ( p < 0 )
				{
					p = -p ;
					m += NUM_MERIDIANOS/2 ;
				}
				else if ( p >= NUM_PARALELOS+1 )
				{
					p = (2*(NUM_PARALELOS+1))-p;
				}
				m = m%NUM_MERIDIANOS ;
				if ( m < 0 )
					m += NUM_MERIDIANOS ;

				if ( p < 0 )
					p += NUM_PARALELOS;

				if ( p == 0 || p == NUM_PARALELOS-1 )
				{
					// Si estamos en un polo, aplicamos el cambio sobre todos los 
					// vertices del polo (lo se, debí de utilizar sólo un vertice)
					for ( int j = 0 ; j < NUM_MERIDIANOS ; j++ )
					{
						alturas[j][p] += lfz ;
					}

					// Pasamos al siguiente paralelo
					break;
				}
				else
				{
					// No es un polo, aplicamos el cambio sobre el punto concreto
					// y se acabó.
					alturas[m][p] += lfz ;
				}
			}
		}

	}
*/

	// Generamos los vértices
	vertices = new video::S3DVertex[NUM_MERIDIANOS*(NUM_PARALELOS+1)];
	int nv = 0;
	int m=0,p=0;
	for (float theta = 0.0f ; theta < 2*PI - EPSILON ; theta += (2*PI) / NUM_MERIDIANOS )
	{
		p=0;
		for (float phi = -PI/2; phi < PI/2 + EPSILON; phi += (PI) / NUM_PARALELOS )
		{
			float altura = alturas[m][p]/10.0f;
			//vertices[nv] = video::S3DVertex(altura*cos(phi)*cos(theta), altura*sin(phi), altura*cos(phi)*sin(theta), cos(phi)*cos(theta), sin(phi), cos(phi)*sin(theta), video::SColor(255,(int)(255-altura*10),(int)(altura*10),0), theta , phi);
			vertices[nv] = video::S3DVertex(altura*cos(phi)*cos(theta), altura*sin(phi), altura*cos(phi)*sin(theta), 0, 0, 0, video::SColor(255,255,255,255), theta , phi);
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

	// Calculamos el bounding box
	box.reset(vertices[0].Pos);
	for (s32 i=1; i<NUM_MERIDIANOS*(NUM_PARALELOS+1); ++i)
	{
		box.addInternalPoint(vertices[i].Pos);
	}
}

PlanetaNode::~PlanetaNode(void)
{
}

void 
PlanetaNode::OnPreRender()
{
	if (IsVisible)
	{
		SceneManager->registerNodeForRendering(this);
	}

	ISceneNode::OnPreRender();
}

void 
PlanetaNode::render()
{
	video::IVideoDriver* driver = SceneManager->getVideoDriver();
	driver->setMaterial(material);
	driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
	driver->drawIndexedTriangleList(&vertices[0], NUM_MERIDIANOS*(NUM_PARALELOS+1), &indices[0], NUM_PARALELOS*NUM_MERIDIANOS*2);
}

void
PlanetaNode::SetColorTerreno(irr::video::SColor c)
{
	for (s32 i=1; i<NUM_MERIDIANOS*(NUM_PARALELOS+1); ++i)
	{
		vertices[i].Color = c;
	}
}