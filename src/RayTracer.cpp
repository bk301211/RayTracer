#include "RayTracer.h"
#include "Globals.h"


Intersection RayTracer::trace(Scene *scene, Vect rayOrigin, Vect rayDirection, int depth){
	
	Intersection minimumIntersection = Intersection();
	float tMin = INT_MAX;
	float ti = 0;
	
	for(int i = 0; i < scene->objects.size(); i++){
		
		Object *o = scene->objects[i];
		
		Intersection intersection = o->intersect(rayOrigin, rayDirection);
		intersection.object = o;
		
		//Intersection intersection =  scene->objects[i]->intersect(rayOrigin, rayDirection);
		
		ti = intersection.ti;
		
		if(  ti > 0 && ti < tMin){
			tMin = ti;
			minimumIntersection = intersection;
		}
	}
	
	return minimumIntersection;
}

bool RayTracer::fastTrace(Scene *scene, Vect rayOrigin, Vect rayDirection, float rangeSquared){
	
	Intersection minimumIntersection = Intersection();
	float tMin = INT_MAX;
	float ti = 0;
	
	for(int i = 0; i < scene->objects.size(); i++){
		
		Object *o = scene->objects[i];
		
		Intersection intersection = o->intersect(rayOrigin, rayDirection);
		intersection.object = o;
		
		ti = intersection.ti;
		
		if(ti > 0 && (ti * ti) < rangeSquared)
			return true;
	}
	
	return false;
}