#ifndef _MATERIAL_H
#define _MATERIAL_H

#include "math.h"
#include "Color.h"
#include "Vect.h"
#include "Vect2D.h"
#include "Lights.h"
#include "Scene.h"
#include "Globals.h"
#include "Utility.h"
#include "Intersection.h"
#include <iostream>
#include <stdint.h>
#include "EasyBMP/EasyBMP.h"
//#include "tinyOBJ/tiny_obj_loader.h"


const float glass  = 1.5;
const float water = 1.3;

class Scene;
class Light;


//plane
class Material{
	
	public:
	
	COLOR diffuse;
	float specular;
	float reflection;
	float transparency;
	float ior;
	float bump;
	BMP diffuseMap;
	BMP specularMap;
	BMP normalMap;
	BMP reflectionMap;
	BMP transpancyMap;

	Material();
	
	Material(COLOR diffuse, float specular);
	
	Material( const char* diffuse, const char* specular, const char* normal, const char* reflection, const char* transparency);
	
	COLOR sampleTexture(BMP *texture, Vect2d uv);
	
	void SetDiffuseMap(const char* diffuse);
	
	
	COLOR shade(Scene *scene, Intersection *intersection, Vect np, Vect npe, int depth);
};


#endif