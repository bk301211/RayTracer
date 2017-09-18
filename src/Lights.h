#ifndef _LIGHTS_H
#define _LIGHTS_H

#include <math.h>
#include <cstdlib>
#include "Vect.h"
#include "RayTracer.h"
#include "Scene.h"
#include "Globals.h"

class Scene;


struct LightContribution{
	float diffuse;
	float specular;
	float occlusion;
	
	LightContribution()
	: diffuse(0), specular(0), occlusion(0)
	{
		
	}
	
	LightContribution(const float d, const float s)
	: diffuse(d), specular(s), occlusion(0)
	{
		
	}
	
	LightContribution(const float d, const float s, float o)
	: diffuse(d), specular(s), occlusion(o)
	{
		
	}
	
	const LightContribution& operator +=(const LightContribution &lc)
	{
		diffuse += lc.diffuse;
		specular += lc.specular;
		occlusion += lc.occlusion;
		return *this;
	}
};

class Light{
	public:
	Vect pos;
	Vect dir;
	COLOR color;
	float theta;
	float intensity;
	float width;
	float height;
	Vect p0,n0,n1;
	
	int samples;
	
	virtual LightContribution GetLighting(Scene *scene, Vect npe, Vect pH, Vect nH) = 0;
	
};


class pointLight : public Light{
	public:
	pointLight();
	
	pointLight(Vect p, COLOR c);
	
	LightContribution GetLighting(Scene *scene, Vect npe, Vect pH, Vect nH);
	
	
};

class dirLight : public Light{
	public:
		
	dirLight();
	
	dirLight(Vect d, COLOR c);
	
	LightContribution GetLighting(Scene *scene, Vect npe, Vect pH, Vect nH);
	
	
	
};


class spotLight : public Light{
	public:
	
	spotLight();
	
	spotLight(Vect p, Vect d, COLOR c, float ang);
	
	LightContribution GetLighting(Scene *scene, Vect npe, Vect pH, Vect nH);
	
};

class areaLight : public Light{
	public:
	
	areaLight();
	
	areaLight(Vect p, Vect d, COLOR c, float w, float h);
	
	LightContribution GetLighting(Scene *scene, Vect npe, Vect pH, Vect nH);
	
};

#endif