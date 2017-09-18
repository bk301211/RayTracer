#ifndef _RAYTRACER_H
#define _RAYTRACER_H

#include <iostream>
#include <math.h>
#include "Vect.h"
//#include "Material.h"
#include "Scene.h"
#include "Intersection.h"
#include "Objects.h"
#include <stdio.h>
#include <limits.h>


class RayTracer{
	
	public:
	static Intersection trace(Scene *scene, Vect rayOrigin, Vect rayDirection, int depth);
	
	static bool fastTrace(Scene *scene, Vect rayOrigin, Vect rayDirection, float rangeSquared);
	
};

#endif