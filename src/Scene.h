#ifndef _SCENE_H
#define _SCENE_H

#include "Objects.h"
#include "Lights.h"
#include <vector> 

class Object;
class Light;

class Scene{
	public:
	
	vector<Object*> objects;
	vector<Light*> lights;
	
	Scene(){}
};

#endif